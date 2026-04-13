#include "data_structs/graph.h"
#include "data_structs/queue.h"
#include <stdlib.h>
#include <stdio.h>

#define INITIAL_CAPACITY 4

// CONCEPT: Graph creation with adjacency lists (Day 28)
Graph* graph_create(int num_vertices) {
    Graph *g = (Graph*)malloc(sizeof(Graph));
    if (g == NULL) {
        perror("Failed to allocate graph");
        return NULL;
    }
    
    g->num_vertices = num_vertices;
    
    // CONCEPT: Arrays of pointers for adjacency list representation
    g->adj_list = (int**)malloc(num_vertices * sizeof(int*));
    g->weights = (double**)malloc(num_vertices * sizeof(double*));
    g->num_edges = (int*)calloc(num_vertices, sizeof(int));
    g->capacity = (int*)malloc(num_vertices * sizeof(int));
    
    if (!g->adj_list || !g->weights || !g->num_edges || !g->capacity) {
        perror("Failed to allocate graph arrays");
        graph_free(g);
        return NULL;
    }
    
    for (int i = 0; i < num_vertices; i++) {
        g->adj_list[i] = (int*)malloc(INITIAL_CAPACITY * sizeof(int));
        g->weights[i] = (double*)malloc(INITIAL_CAPACITY * sizeof(double));
        g->capacity[i] = INITIAL_CAPACITY;
        
        if (!g->adj_list[i] || !g->weights[i]) {
            perror("Failed to allocate adjacency list");
            graph_free(g);
            return NULL;
        }
    }
    
    return g;
}

// CONCEPT: Dynamic array growth for adjacency lists
void graph_add_edge(Graph *g, int src, int dest, double weight) {
    if (g == NULL || src < 0 || src >= g->num_vertices || 
        dest < 0 || dest >= g->num_vertices) {
        return;
    }
    
    // Grow capacity if needed
    if (g->num_edges[src] >= g->capacity[src]) {
        g->capacity[src] *= 2;
        g->adj_list[src] = (int*)realloc(g->adj_list[src], 
                                          g->capacity[src] * sizeof(int));
        g->weights[src] = (double*)realloc(g->weights[src], 
                                            g->capacity[src] * sizeof(double));
    }
    
    g->adj_list[src][g->num_edges[src]] = dest;
    g->weights[src][g->num_edges[src]] = weight;
    g->num_edges[src]++;
}

void graph_add_edge_undirected(Graph *g, int v1, int v2, double weight) {
    graph_add_edge(g, v1, v2, weight);
    graph_add_edge(g, v2, v1, weight);
}

bool graph_has_edge(Graph *g, int src, int dest) {
    if (g == NULL || src < 0 || src >= g->num_vertices) {
        return false;
    }
    
    for (int i = 0; i < g->num_edges[src]; i++) {
        if (g->adj_list[src][i] == dest) {
            return true;
        }
    }
    return false;
}

void graph_print(Graph *g) {
    if (g == NULL) return;
    
    printf("Graph with %d vertices:\n", g->num_vertices);
    for (int v = 0; v < g->num_vertices; v++) {
        printf("  %d: ", v);
        for (int i = 0; i < g->num_edges[v]; i++) {
            printf("%d(%.1f) ", g->adj_list[v][i], g->weights[v][i]);
        }
        printf("\n");
    }
}

// CONCEPT: BFS using queue (Day 26/28)
void graph_bfs(Graph *g, int start, void (*callback)(int)) {
    if (g == NULL || start < 0 || start >= g->num_vertices) return;
    
    bool *visited = (bool*)calloc(g->num_vertices, sizeof(bool));
    Queue *q = queue_create();
    
    if (!visited || !q) {
        free(visited);
        queue_free(q);
        return;
    }
    
    visited[start] = true;
    queue_enqueue(q, start);
    
    while (!queue_is_empty(q)) {
        int v = (int)queue_dequeue(q);
        callback(v);
        
        for (int i = 0; i < g->num_edges[v]; i++) {
            int neighbor = g->adj_list[v][i];
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                queue_enqueue(q, neighbor);
            }
        }
    }
    
    free(visited);
    queue_free(q);
}

// CONCEPT: Recursive DFS (Day 28)
static void dfs_helper(Graph *g, int v, bool *visited, void (*callback)(int)) {
    visited[v] = true;
    callback(v);
    
    for (int i = 0; i < g->num_edges[v]; i++) {
        int neighbor = g->adj_list[v][i];
        if (!visited[neighbor]) {
            dfs_helper(g, neighbor, visited, callback);
        }
    }
}

void graph_dfs(Graph *g, int start, void (*callback)(int)) {
    if (g == NULL || start < 0 || start >= g->num_vertices) return;
    
    bool *visited = (bool*)calloc(g->num_vertices, sizeof(bool));
    if (!visited) return;
    
    dfs_helper(g, start, visited, callback);
    free(visited);
}

// CONCEPT: Proper cleanup of all dynamically allocated memory
void graph_free(Graph *g) {
    if (g == NULL) return;
    
    if (g->adj_list) {
        for (int i = 0; i < g->num_vertices; i++) {
            free(g->adj_list[i]);
        }
        free(g->adj_list);
    }
    
    if (g->weights) {
        for (int i = 0; i < g->num_vertices; i++) {
            free(g->weights[i]);
        }
        free(g->weights);
    }
    
    free(g->num_edges);
    free(g->capacity);
    free(g);
}

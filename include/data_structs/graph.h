#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

// CONCEPT: Graph using adjacency list (Day 28)
// Triple pointer: array of pointers to arrays of neighbors

typedef struct {
    int num_vertices;
    int *num_edges;      // Number of edges per vertex
    int *capacity;       // Capacity of each adjacency list
    int **adj_list;      // Adjacency list: adj_list[v] is array of neighbors
    double **weights;    // Optional weights for weighted graphs
} Graph;

Graph* graph_create(int num_vertices);
void graph_add_edge(Graph *g, int src, int dest, double weight);
void graph_add_edge_undirected(Graph *g, int v1, int v2, double weight);
bool graph_has_edge(Graph *g, int src, int dest);
void graph_print(Graph *g);
void graph_bfs(Graph *g, int start, void (*callback)(int));
void graph_dfs(Graph *g, int start, void (*callback)(int));
void graph_free(Graph *g);

#endif // GRAPH_H

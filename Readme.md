# Advanced CLI Calculator - 30 Day C Programming Mastery

[![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)](https://github.com/yourusername/Commandline_Calculator)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![C Standard](https://img.shields.io/badge/C%20Standard-C99-orange.svg)](https://en.wikipedia.org/wiki/C99)

## 🎯 Project Overview

A **production-grade CLI calculator** built over **30 days** that demonstrates **every major C programming concept** from beginner to advanced system programming. Each module teaches specific C concepts through practical implementation.

**Key Goals:**

- ✅ **Functional calculator** with 12 feature categories (basic → financial → graphing)
- ✅ **Comprehensive C education** - 100+ concepts with inline comments
- ✅ **Production quality** - Zero memory leaks, signal handling, modular design
- ✅ **Industrial build system** - Makefile, valgrind clean, gdb ready

## 🚀 Features (12 Categories)

| Category        | Commands                          | C Concepts Demonstrated  |
| --------------- | --------------------------------- | ------------------------ |
| **Basic Ops**   | `basic add 5 3`                   | Operators, functions     |
| **Scientific**  | `scientific sin 30 deg`           | Recursion, trig math     |
| **Statistical** | `statistical mean 1 2 3`          | Arrays, dynamic memory   |
| **Graphical**   | `graphical plot sin(x)`           | 2D arrays, ASCII art     |
| **Solvers**     | `solver matrix_det 1 2 3 4`       | Recursion, pointers      |
| **Calculus**    | `calculus integral sin(x) 0 3.14` | Numerical methods        |
| **Memory**      | `memory store 42`                 | Linked lists, BST        |
| **Programming** | `programming script myscript`     | Function pointers        |
| **Converters**  | `converter length 100 cm m`       | Tables, bit ops          |
| **Complex**     | `complex add 1+2i 3+4i`           | Structs, double pointers |
| **Financial**   | `financial npv -1000 500 600`     | Loops, precision         |
| **Extra**       | `extra save data.txt`             | File I/O, signals        |

## 🏗️ Project Structure

Commandline_Calculator/

├── Makefile # Industrial build system  
├── README.md # 📄 This file  
├── common.h # Macros, structs, enums  
├── main.c # CLI entry point  
├── command_handler.[hc] # Command dispatch  
├── evaluation.[hc] # Expression parsing  
├── initialization.[hc] # Memory setup  
├── cleanup.[hc] # Memory cleanup  
│  
├── ops/ # 12 Feature Categories  
│ ├── basic_ops.[hc] # Day 4: add/sub/mul/div  
│ ├── scientific_ops.[hc] # Day 8: sin/cos/factorial  
│ └── ... (10 more)  
│  
├── data_structs/ # Advanced Data Structures  
│ ├── linked_list.[hc] # Day 11: Pointers  
│ ├── stack.[hc] # Day 26: LIFO  
│ ├── bst.[hc] # Day 27: Trees  
│ └── graph.[hc] # Day 28: Graphs  
│  
└── utils/ # Utilities  
 ├── utils.[hc] # Logging, formatting  
 └── signals.[hc] # Ctrl+C handling

## 📈 30-Day Detailed Roadmap

| Day    | Focus                 | Concepts Covered                                 | Files Created/Updated                 |
| ------ | --------------------- | ------------------------------------------------ | ------------------------------------- |
| **1**  | CLI Foundation        | Preprocessor, I/O, main(), strings, control flow | `Makefile`, `common.h`, `main.c`      |
| **2**  | Basic Syntax          | Data types, variables, constants, scope          | `common.h` (enhanced)                 |
| **3**  | Input Mastery         | printf/scanf formats, fgets, escape sequences    | `utils/utils.[hc]`                    |
| **4**  | Operators             | Arithmetic, relational, precedence, assignment   | `ops/basic_ops.[hc]`                  |
| **5**  | Control Flow          | if/switch, loops (for/while/do), break/continue  | `command_handler.[hc]`                |
| **6**  | Functions             | Declaration, parameters, return types            | `evaluation.[hc]`                     |
| **7**  | Arrays/Strings        | 1D arrays, string.h, strtok/sscanf               | `evaluation.c` (complete)             |
| **8**  | Recursion             | Recursive functions, factorial                   | `ops/scientific_ops.[hc]`             |
| **9**  | Arrays Advanced       | 2D arrays, initialization, multi-dim             | `ops/statistical_ops.[hc]`            |
| **10** | Strings Complete      | char\* vs arrays, strlen/strcpy                  | `utils/utils.c` (enhanced)            |
| **11** | Pointer Basics        | &/\* operators, dereference, basics              | `data_structs/linked_list.[hc]`       |
| **12** | Pointer Arithmetic    | ptr++, sizeof, array-pointer decay               | `linked_list.c` (ops)                 |
| **13** | Dynamic Memory        | malloc/calloc/free basics                        | `initialization.[hc]`, `cleanup.[hc]` |
| **14** | Memory Management     | Memory leaks prevention, cleanup                 | `ops/memory_ops.[hc]`                 |
| **15** | Structures            | struct definition, access (.->)                  | `common.h` (Complex struct)           |
| **16** | Nested Structs        | typedef, nested structures                       | `data_structs/stack.[hc]`             |
| **17** | Unions/Storage        | union, static/auto/extern/register               | `common.h` (DataUnion)                |
| **18** | File Basics           | fopen/fclose, fprintf/fscanf                     | `utils/utils.c` (logging)             |
| **19** | Binary Files          | fread/fwrite, binary mode                        | `ops/extra_ops.[hc]`                  |
| **20** | Dynamic Arrays        | realloc, capacity vs size                        | `statistical_ops.c` (dynamic)         |
| **21** | File Error Handling   | ferror/feof, robust I/O                          | `extra_ops.c` (complete)              |
| **22** | Double Pointers       | \*\*Node, pointer to pointer                     | `data_structs/bst.[hc]`               |
| **23** | Function Pointers     | typedef (\*Func), dispatch tables                | `command_handler.c` (table)           |
| **24** | Bit Manipulation      | & \| ^ ~ << >>, flags/masks                      | `ops/converter_ops.[hc]`              |
| **25** | Preprocessor Advanced | #ifdef/#pragma, variadic macros                  | `common.h` (complete)                 |
| **26** | Stacks/Queues         | LIFO/FIFO, array+linked impl                     | `data_structs/queue.[hc]`             |
| **27** | Trees/BST             | Recursion, inorder traversal                     | `bst.c` (complete), `memory_ops.c`    |
| **28** | Graphs Intro          | Adjacency lists, \*\*\*adj                       | `data_structs/graph.[hc]`             |
| **29** | Multifile/Makefiles   | extern, .o dependencies, linking                 | `Makefile` (advanced)                 |
| **30** | Integration/Debug     | valgrind, gdb, signals, full test                | `utils/signals.[hc]`, all ops/        |

## 🛠️ Setup & Build

```

Clone & enter project
git clone <repo> Commandline_Calculator
cd Commandline_Calculator

Build (zero warnings expected)
make

Run calculator
./calculator

Memory debugging
make valgrind

Clean build files
make clean

```

**Requirements:**

- GCC/Clang (C99 support)
- Linux/Mac (Windows: MinGW + adjustments)
- `make`, `valgrind` (optional but recommended)

## 📖 User Manual - Key Commands

basic add 5 3 → 8.00
scientific sin 30 deg → 0.50
statistical mean 1 2 3 → 2.00
memory store 42 → Stored
memory recall → 42.00
extra save_data history.txt → Saved
help → Full command list
quit → Exit

## 🎓 C Concepts Coverage (100+ Total)

| Level            | Concepts                                                             | Files Implemented                |
| ---------------- | -------------------------------------------------------------------- | -------------------------------- |
| **Beginner**     | Syntax, I/O, operators, control flow, functions, arrays              | `main.c`, `basic_ops.c`          |
| **Intermediate** | Pointers, dynamic memory, structs, file I/O                          | `data_structs/*`, `utils/*`      |
| **Advanced**     | Double pointers, function pointers, bit manipulation, trees, signals | `bst.c`, `signals.c`, `common.h` |

Every file contains inline comments like:

// CONCEPT: Pointer arithmetic - ptr++

## 🧪 Testing & Quality

```

Check memory leaks with valgrind
make valgrind

Debug build with symbols
make DEBUG=1

Debug with gdb
gdb ./calculator

Format code consistently
make format

```

Quality metrics:

- ✅ Zero compiler warnings (`-Wall -Wextra -Wpedantic`)
- ✅ Zero memory leaks (valgrind clean)
- ✅ Signals handled gracefully (Ctrl+C)
- ✅ Professional CLI with colored output, history, error handling

## 🤝 Contributing

1. Follow daily roadmap sequence.
2. Add concept comments: `// CONCEPT: Dynamic allocation - malloc()`.
3. Run `make valgrind` to ensure no memory leaks.
4. Test new commands match README examples.

## 📄 License

MIT License — Free to use, modify, and distribute.

---

**Built with ❤️ for C programming mastery**  
_Start with Day 1 and master C through practical calculator development!_

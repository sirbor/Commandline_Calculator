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

## 📚 30-Day Learning Roadmap

## 30-Day Learning Roadmap

- **Week 1: Foundations**  
  → CLI + basic arithmetic

- **Week 2: Intermediate**  
  → Pointers + data structures

- **Week 3: Core Features**  
  → Files + dynamic arrays

- **Week 4: Advanced**  
  → Trees + system programming

- **Days 29-30: Integration**  
  → Full production calculator

Each day maps files → C concepts → testable milestones.

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

## 🛠️ Setup & Build

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

Check memory leaks with valgrind
make valgrind

Debug build with symbols
make DEBUG=1

Debug with gdb
gdb ./calculator

Format code consistently
make format

Quality metrics:

- ✅ Zero compiler warnings (`-Wall -Wextra -Wpedantic`)
- ✅ Zero memory leaks (valgrind clean)
- ✅ Signals handled gracefully (Ctrl+C)
- ✅ Professional CLI with colored output, history, error handling

## 📈 Progress Tracking

| Day | Milestone         | Files Added                      | Concepts                       |
| --- | ----------------- | -------------------------------- | ------------------------------ |
| 1   | CLI Foundation    | `main.c`, `common.h`, `Makefile` | 25+ beginner concepts          |
| 7   | Basic Arithmetic  | `basic_ops.[hc]`                 | Operators complete             |
| 14  | Data Structures   | `linked_list.[hc]`               | Pointers + dynamic memory      |
| 21  | File I/O Complete | `extra_ops.[hc]`                 | Binary/text files              |
| 30  | FULL PRODUCTION   | All ~40 files                    | **All C concepts implemented** |

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

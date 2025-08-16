# Mark-and-Sweep Garbage Collector in C

A complete implementation of a mark-and-sweep garbage collector written in C, designed for a Python-like programming language called "Snek" 🐍.

## What is this?

This project implements one of the most fundamental algorithms in computer science: **automatic memory management**. The garbage collector automatically frees memory that's no longer being used by your program, preventing memory leaks and making programming safer.

### How it works

The **mark-and-sweep** algorithm works in three phases:

1. **Mark**: Starting from "root" objects (variables currently in scope), mark all reachable objects
2. **Trace**: Follow references between objects to mark everything that's still accessible
3. **Sweep**: Free all unmarked objects and clean up the memory

## Features

- ✅ **Complete mark-and-sweep implementation**
- ✅ **Handles complex object references** (vectors, arrays, strings, integers)
- ✅ **Stack frame management** for tracking variable scope
- ✅ **Automatic memory cleanup**
- ✅ **Comprehensive test suite**

## Supported Object Types

The garbage collector manages these "Snek" language objects:

- **Integers** and **Floats**
- **Strings** with dynamic allocation
- **Vector3** objects (with x, y, z components)
- **Arrays** of arbitrary objects

## Building and Running

Clone the repository:

```bash
git clone https://github.com/juandrzej/mark-and-sweep-gc.git
cd mark-and-sweep-gc
```

Build the project:

```bash
make
```

Run the tests:

```bash
./gc_test
```

### Requirements

- GCC or Clang compiler
- Make (optional, you can compile manually)

### Manual compilation

```bash
gcc -Wall -Wextra -std=c99 \*.c -o gc_test
./gc_test
```

## Example Output

```bash
=== Garbage Collector Tests ===

Running test_simple...
Created string object, VM has 1 objects
After GC (with frame): VM has 1 objects
After GC (frame freed): VM has 0 objects
test_simple PASSED

Running test_full...
Created 7 objects, VM has 7 objects
After freeing f3: VM has 6 objects
After freeing all frames: VM has 0 objects
test_full PASSED

All tests completed successfully!
Your garbage collector is working! 🎉
```

## Project Structure

├── vm.c # Virtual machine and GC implementation
├── vm.h # VM header file
├── snekobject.c # Object system implementation
├── snekobject.h # Object type definitions
├── sneknew.c # Object creation functions
├── sneknew.h # Object creation headers
├── stack.c # Dynamic stack implementation
├── stack.h # Stack header
├── main.c # Test suite
├── Makefile # Build configuration
└── README.md # This file

## Learning Journey

This project was built as part of the **Boot.dev Computer Science curriculum**, specifically the course on memory management and garbage collection. It demonstrates:

- **Low-level memory management** in C
- **Graph traversal algorithms** (for the trace phase)
- **Data structure design** (objects, stacks, references)
- **Systems programming** concepts

## Why This Matters

Garbage collection is used in most modern programming languages:

- **Python** uses reference counting + cycle detection
- **Java** and **C#** use generational garbage collectors
- **JavaScript** engines use mark-and-sweep variants
- **Go** uses a concurrent mark-and-sweep collector

Understanding how GC works makes you a better programmer in any language!

## Contributing

Feel free to:

- Add more object types
- Implement optimizations (generational GC, incremental collection)
- Add more comprehensive tests
- Improve the documentation

## License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE](LICENSE) file for details.

---

_Built with ❤️ and lots of debugging at [Boot.dev](https://boot.dev)_

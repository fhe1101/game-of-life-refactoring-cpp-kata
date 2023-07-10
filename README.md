# Bootstrap for C++ katas

[![CI](https://github.com/Coding-Cuddles/game-of-life-refactoring-cpp-kata/actions/workflows/main.yml/badge.svg)](https://github.com/Coding-Cuddles/game-of-life-refactoring-cpp-kata/actions/workflows/main.yml)
[![Replit](https://replit.com/badge?caption=Try%20with%20Replit&variant=small)](https://replit.com/new/github/Coding-Cuddles/game-of-life-refactoring-cpp-kata)

## Overview

This kata complements [Clean Code: SOLID, Ep. 11 - Liskov Substitution Principle](https://cleancoders.com/episode/clean-code-episode-11-p1).

This repository contains two exercises designed to improve your skills in
code refactoring, with a focus on the Liskov Substitution Principle (LSP).

## Instructions

### Exercise 1

The Game of Life is a cellular automaton devised by the British mathematician
John Horton Conway in 1970. The game is a zero-player game, meaning that its
evolution is determined by its initial state, requiring no further input.

You have a code base that simulates the Game of Life, but it does not adhere to
the LSP. Your task is to refactor the code to align with the LSP. This means,
among other things, that you should be able to replace any instance of a parent
class with an instance of one of its child classes without altering the
correctness of the program.

**Instructions:**

1. Review the current code base and identify parts that violate the LSP.
2. Refactor the violating code to align with the LSP.
3. Make sure all the tests still pass after your refactoring.

Be sure to run the tests before and after your refactoring to make sure you
haven't changed the game's behavior.

### Exercise 2

For those who complete the refactoring in the first part of the class, a second
exercise is available. Your task is to extend the original code with new types
of cells.

Here are the new cell types to implement:

1. **Immortal Cell**: This cell type never dies. Once born, it stays alive
   through all the subsequent generations.
2. **Reproductive Cell**: This cell type reproduces faster than a normal cell.
   It can make a new cell in the neighborhood with only two neighbors instead of
   three.
3. **Lazy Cell**: This cell type requires more neighbors to survive. It stays
   alive only if it has exactly three neighbors.

## Usage

You can import this project into [Replit](https://replit.com), and it will
handle all dependencies automatically.

### Prerequisites

* [CMake 3.19+](https://cmake.org)
* [Ninja](https://ninja-build.org)
* [GTest](https://github.com/google/googletest)

### Build

```console
make build
```

### Run main

```console
make run
```

### Run tests

```console
make test
```

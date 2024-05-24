# L

[![Tests](https://github.com/juliojimenez/L/actions/workflows/tests.yml/badge.svg)](https://github.com/juliojimenez/L/actions/workflows/tests.yml) [![Build](https://github.com/juliojimenez/L/actions/workflows/release.yml/badge.svg)](https://github.com/juliojimenez/L/actions/workflows/release.yml) ![GitHub Release](https://img.shields.io/github/v/release/juliojimenez/L)

The L programing language is a simple Lisp-like language. It is a work in progress.

- [Features](#features)
- [Installation](#installation)
  - [macOS](#macos)
  - [Linux](#linux)
- [REPL](#repl)
- [Syntax](#syntax)
  - [Arithmetic](#arithmetic)
    - [Addition](#addition)
    - [Subtraction](#subtraction)
    - [Multiplication](#multiplication)
    - [Division](#division)
    - [Modulus](#modulus)
  - [Predicates](#predicates)
    - [Equal](#equal)
  - [Branching](#branching)
    - [if](#if)
  - [Variables](#variables)
    - [define](#define)
  - [Lists](#lists)
    - [cons](#cons)
    - [car](#car)
    - [cdr](#cdr)
    - [quote](#quote)
    - [list](#list)

## Features

L aims to closely follow the Revised^7 Report on the Algorithmic Language Scheme (R7RS).

## Installation

### macOS

```bash
wget https://github.com/juliojimenez/L/releases/download/0.0.15/llang-0.0.15-darwin-arm64
mv llang-0.0.15-darwin-arm64 llang
```

### Linux

```bash
wget https://github.com/juliojimenez/L/releases/download/0.0.15/llang-0.0.15-linux-amd64
mv llang-0.0.15-linux-amd64 llang
```

## REPL

```bash
./llang
L v0.0.15

>
```

## Syntax

### Arithmetic

#### Addition

```lisp
> (+ 1 (+ 2 3))
6
```

#### Subtraction

```lisp
> (- 3 -3)
6
```

#### Multiplication

```lisp
> (* 3 3)
9
```

#### Division

```lisp
> (/ 12 6)
2
```

#### Modulus

```lisp
> (% 12 7)
5
```

### Predicates

#### Equal

```lisp
> (= 1 2)
#f
> (= 1 1)
#t
> (= (+ 1 1) 2)
#t
```

### Branching

#### if

```lisp
> (if #t (+ 1 2) (+ 2 3))
3
> (if #f (+ 1 2) (+ 2 3))
5
> (if (= 1 2) (+ 1 2) (+ 2 3))
5
```

### Variables

#### define

```lisp
> (define a 10)
done
> (define b a)
done
> a
10
> b
10
> (define x (+ 1 2))
done
> x
3
```

### Lists

#### cons

```lisp
> (cons 1 2)
(1 . 2)
```

#### car

```lisp
> (car (cons 1 2))
1
```

#### cdr

```lisp
> (cdr (cons 1 2))
2
```

#### quote

```lisp
> (quote (cons 12 10))
(cons 12 10)
> (quote (cons #t 3))
(cons #t 3)
```

#### list

```lisp
> (list 1 2 3)
(1 2 3)
```

# L

[![Tests](https://github.com/juliojimenez/L/actions/workflows/tests.yml/badge.svg)](https://github.com/juliojimenez/L/actions/workflows/tests.yml) [![Build](https://github.com/juliojimenez/L/actions/workflows/release.yml/badge.svg)](https://github.com/juliojimenez/L/actions/workflows/release.yml) ![GitHub Release](https://img.shields.io/github/v/release/juliojimenez/L)

[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=juliojimenez_L&metric=alert_status)](https://sonarcloud.io/summary/new_code?id=juliojimenez_L) [![Lines of Code](https://sonarcloud.io/api/project_badges/measure?project=juliojimenez_L&metric=ncloc)](https://sonarcloud.io/summary/new_code?id=juliojimenez_L) [![Reliability Rating](https://sonarcloud.io/api/project_badges/measure?project=juliojimenez_L&metric=reliability_rating)](https://sonarcloud.io/summary/new_code?id=juliojimenez_L) [![Security Rating](https://sonarcloud.io/api/project_badges/measure?project=juliojimenez_L&metric=security_rating)](https://sonarcloud.io/summary/new_code?id=juliojimenez_L) [![Maintainability Rating](https://sonarcloud.io/api/project_badges/measure?project=juliojimenez_L&metric=sqale_rating)](https://sonarcloud.io/summary/new_code?id=juliojimenez_L) [![Vulnerabilities](https://sonarcloud.io/api/project_badges/measure?project=juliojimenez_L&metric=vulnerabilities)](https://sonarcloud.io/summary/new_code?id=juliojimenez_L)

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
  - [Procedures](#procedures)
    - [lambda](#lambda)

## Features

L aims to closely follow the Revised^7 Report on the Algorithmic Language Scheme (R7RS).

## Installation

### macOS

```bash
wget https://github.com/juliojimenez/L/releases/download/0.0.17/llang-0.0.17-darwin-arm64
mv llang-0.0.17-darwin-arm64 llang
```

### Linux

```bash
wget https://github.com/juliojimenez/L/releases/download/0.0.17/llang-0.0.17-linux-amd64
mv llang-0.0.17-linux-amd64 llang
```

## REPL

```bash
./llang
L v0.0.17

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

The apostrophe or single-quote `'` is a shorthand for `quote`.

```lisp
> '(cons 12 10)
(cons 12 10)
```

#### list

```lisp
> (list 1 2 3)
(1 2 3)
```

### Procedures

#### lambda

```lisp
> (lambda () (+ 1 2))
<#lambda>
> ((lambda () (+ 1 2)))
3
> ((lambda (a b) (+ a b)) 2 2)
4
```

The L mascot is a lemming named Lemmy.

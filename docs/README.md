# L

[![Tests](https://github.com/juliojimenez/L/actions/workflows/tests.yml/badge.svg)](https://github.com/juliojimenez/L/actions/workflows/tests.yml) [![Build](https://github.com/juliojimenez/L/actions/workflows/release.yml/badge.svg)](https://github.com/juliojimenez/L/actions/workflows/release.yml) ![GitHub Release](https://img.shields.io/github/v/release/juliojimenez/L)

The L programing language is a simple Lisp-like language. It is a work in progress.

## Features

L aims to closely follow the Revised^7 Report on the Algorithmic Language Scheme (R7RS).

## Installation

### macOS

```bash
wget https://github.com/juliojimenez/L/releases/download/0.0.8/llang-0.0.8-darwin-arm64
mv llang-0.0.8-darwin-arm64 llang
```

### Linux

```bash
wget https://github.com/juliojimenez/L/releases/download/0.0.8/llang-0.0.8-linux-amd64
mv llang-0.0.8-linux-amd64 llang
```

## REPL

```bash
./llang
L v0.0.8

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

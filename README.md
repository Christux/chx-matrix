[![Build and Test chx_matrix on multiple OS and architectures](https://github.com/Christux/chx-matrix/actions/workflows/build-test.yml/badge.svg?branch=main)](https://github.com/Christux/chx-matrix/actions/workflows/build-test.yml)

# Matrix
A light matrix manipulation and calculation module

## Installation & build

### Create virtual environmeent
```
python3.12 -m venv .venv
```

### Activate
```
source .venv/bin/activate
```

### Install dependencies
```
pip install -r requirements.txt
```

### Backup env
```
pip freeze > requirements.txt
```

### Build module
```
make build
```

## Matrix features

### Import module


```python
from chx_matrix import Matrix
```

### Instanciate new Matrix


```python
m = Matrix(3, 4)
m
```




    [
      [0.00, 0.00, 0.00, 0.00],
      [0.00, 0.00, 0.00, 0.00],
      [0.00, 0.00, 0.00, 0.00],
    ]



### Set values


```python
m.set_all(4)
m.set(1, 0, 6)
m.set(1, 1, 7)
m
```




    [
      [4.00, 4.00, 4.00, 4.00],
      [6.00, 7.00, 4.00, 4.00],
      [4.00, 4.00, 4.00, 4.00],
    ]




```python
n = m.transpose()
n
```




    [
      [4.00, 6.00, 4.00],
      [4.00, 7.00, 4.00],
      [4.00, 4.00, 4.00],
      [4.00, 4.00, 4.00],
    ]




```python
c = m.copy()

m.set_all(42)

c
```




    [
      [4.00, 4.00, 4.00, 4.00],
      [6.00, 7.00, 4.00, 4.00],
      [4.00, 4.00, 4.00, 4.00],
    ]




```python
s = c.get_sub_matrix(1, 2, 0, 1)
s
```




    [
      [6.00, 7.00],
      [4.00, 4.00],
    ]




```python
s.set_all(6)
s
```




    [
      [6.00, 6.00],
      [6.00, 6.00],
    ]




```python
c
```




    [
      [4.00, 4.00, 4.00, 4.00],
      [6.00, 6.00, 4.00, 4.00],
      [6.00, 6.00, 4.00, 4.00],
    ]




```python
m = Matrix(3, 2)
m.set_all(5.)

s = m[1, :]

s.set_all(2)

m
```




    [
      [5.00, 5.00],
      [2.00, 2.00],
      [5.00, 5.00],
    ]




```python
m.get_row(1)
```




    [
      [2.00, 2.00],
    ]




```python
m.get_column(1)
```




    [
      [5.00],
      [2.00],
      [5.00],
    ]




```python
m.get_column(1).transpose().set(2, 3.)
```




    [
      [5.00, 2.00, 3.00],
    ]



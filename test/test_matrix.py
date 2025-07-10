import gc
from chx_matrix import Matrix, Row, Column


def test_init_matrix():
    m = Matrix(2, 3)
    assert m is not None
    assert isinstance(m, Matrix)
    assert m.shape == (2, 3)

def test_set_get():

    m = Matrix(rows=3, cols=4)

    for i in range(3):
        for j in range(4):
            assert m.get(i=i, j=j) == 0.0

    for i in range(3):
        m.set(i=i, j=2, value=i)

    assert m[2, 2] == 2.

    for j in range(4):
        m[1, j] = j

    assert m[1, 3] == 3

    m.set_all(2.)

    for i in range(3):
        for j in range(4):
            assert m.get(i=i, j=j) == 2.0

def test_transpose():

    m = Matrix(3, 2)
    m.set_all(4)
    m.set(1, 0, 6)
    m.set(1, 1, 7)

    assert m[0, 0] == m[0, 1] == m[2, 0] == m[2, 1] == 4.
    assert m[1, 0] == 6.
    assert m[1, 1] == 7.

    t = m.transpose()

    assert t[0, 0] == t[1, 0] == t[0, 2] == t[1, 2] == 4.
    assert t[0, 1] == 6.
    assert t[1, 1] == 7.


def test_data_sharing():
    m = Matrix(3, 2)
    m.set_all(1.)

    t = m.transpose()

    del m
    gc.collect()

    for i in range(2):
        for j in range(3):
            assert t.get(i=i, j=j) == 1.

def test_matrix_copy():

    m = Matrix(3, 2)
    m.set_all(5.)

    c = m.copy()

    m.set_all(9.)

    for i in range(3):
        for j in range(2):
            assert c.get(i=i, j=j) == 5.

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

def test_get_sub_matrix():

    m = Matrix(3, 2)
    m.set_all(5.)

    s = m.get_sub_matrix(1, 2, 0, 1)

    assert s.shape == (2, 2)

    s.set_all(2)

    assert m[0, 0] == 5.
    assert m[0, 1] == 5.
    assert m[1, 0] == 2.
    assert m[1, 1] == 2.
    assert m[2, 0] == 2.
    assert m[2, 1] == 2.

def test_get_sub_matrix_slice():

    m = Matrix(3, 2)
    m.set_all(5.)

    s = m[1:3, 0:2]

    assert s.shape == (2, 2)

    s.set_all(2)

    assert m[0, 0] == 5.
    assert m[0, 1] == 5.
    assert m[1, 0] == 2.
    assert m[1, 1] == 2.
    assert m[2, 0] == 2.
    assert m[2, 1] == 2.

def test_get_sub_matrix_slice_2():

    m = Matrix(3, 2)
    m.set_all(5.)

    s = m[1:3, :]

    assert s.shape == (2, 2)

    s.set_all(2)

    assert m[0, 0] == 5.
    assert m[0, 1] == 5.
    assert m[1, 0] == 2.
    assert m[1, 1] == 2.
    assert m[2, 0] == 2.
    assert m[2, 1] == 2.

def test_get_sub_matrix_slice_number():

    m = Matrix(3, 2)
    m.set_all(5.)
    m.set(2, 1, 2.)

    s = m[2:3, 1:2]

    assert isinstance(s, float)

    assert s == 2

def test_get_sub_matrix_row():

    m = Matrix(3, 2)
    m.set_all(5.)

    s = m.get_sub_matrix(1, 1, 0, 1)

    assert isinstance(s, Row)
    assert s.shape == (1, 2)

    s.set_all(2)

    assert m[0, 0] == 5.
    assert m[0, 1] == 5.
    assert m[1, 0] == 2.
    assert m[1, 1] == 2.
    assert m[2, 0] == 5.
    assert m[2, 1] == 5.

def test_get_sub_matrix_slice_row():

    m = Matrix(3, 2)
    m.set_all(5.)

    s = m[1, :]

    assert isinstance(s, Row)
    assert s.shape == (1, 2)

    s.set_all(2)

    assert m[0, 0] == 5.
    assert m[0, 1] == 5.
    assert m[1, 0] == 2.
    assert m[1, 1] == 2.
    assert m[2, 0] == 5.
    assert m[2, 1] == 5.

def test_get_sub_matrix_col():

    m = Matrix(3, 2)
    m.set_all(5.)

    s = m.get_sub_matrix(0, 2, 0, 0)

    assert isinstance(s, Column)
    assert s.shape == (3, 1)

    s.set_all(2)

    assert m[0, 0] == 2.
    assert m[0, 1] == 5.
    assert m[1, 0] == 2.
    assert m[1, 1] == 5.
    assert m[2, 0] == 2.
    assert m[2, 1] == 5.

def test_get_sub_matrix_col_slice():

    m = Matrix(3, 2)
    m.set_all(5.)

    s = m[:, 0]

    assert isinstance(s, Column)

    s.set_all(2)

    assert m[0, 0] == 2.
    assert m[0, 1] == 5.
    assert m[1, 0] == 2.
    assert m[1, 1] == 5.
    assert m[2, 0] == 2.
    assert m[2, 1] == 5.

def test_row():
    r = Row(4)
    r.set_all(3)

    assert isinstance(r, Row)
    assert r[2] == 3

def test_get_row_from_matrix():

    m = Matrix(3, 2)
    m.set_all(5.)

    r = m.get_row(1)

    assert isinstance(r, Row)

    r.set_all(2)

    r[0] = 0

    assert m[0, 0] == 5.
    assert m[0, 1] == 5.
    assert m[1, 0] == 0.
    assert m[1, 1] == 2.
    assert m[2, 0] == 5.
    assert m[2, 1] == 5.

def test_column():
    c = Column(8)
    c.set_all(5.)

    assert isinstance(c, Column)
    assert c.shape == (8, 1)
    assert c[3] == 5.

def test_column_get_set():
    c = Column(8)
    c.set_all(5.)

    assert c.get(2) == 5.

    c.set(4, 6.)

    assert c.get(4) == 6.


def test_get_column_from_matrix():

    m = Matrix(3, 2)
    m.set_all(5.)

    c = m.get_column(1)

    assert isinstance(c, Column)

    c.set_all(2)

    c[0] = 0

    assert m[0, 0] == 5.
    assert m[0, 1] == 0.
    assert m[1, 0] == 5.
    assert m[1, 1] == 2.
    assert m[2, 0] == 5.
    assert m[2, 1] == 2.

def test_column_transpose():

    c = Column(8).set_all(5.)

    assert isinstance(c, Column)

    r = c.transpose()

    assert r.shape == (1, 8)
    assert isinstance(r, Row)

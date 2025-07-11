from chx_matrix import Matrix, Row, Column

def test_column():
    c = Column(8)
    c.set_all(5.)

    assert isinstance(c, Column)
    assert c.shape == (8, 1)
    assert c[3] == 5.

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

def test_column_get_set():
    c = Column(8)

    c.set(1, 5.)

    c[2] = 6.

    assert c.get(0) == 0.
    assert c.get(1) == 5.
    assert c[2] == 6.
    assert c[3] == 0.


def test_column_transpose():

    c = Column(8).set_all(5.)

    assert isinstance(c, Column)

    r = c.transpose()

    assert r.shape == (1, 8)
    assert isinstance(r, Row)

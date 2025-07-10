from chx_matrix import Matrix, Row, Column

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

def test_row_getter_setter():

    r = Row(4)

    r.set(1, 5.)

    r[2] = 6.

    assert r.get(0) == 0.
    assert r.get(1) == 5.
    assert r[2] == 6.
    assert r[3] == 0.

def test_row_transpose():

    c = Row(8).set_all(5.)

    assert isinstance(c, Row)

    r = c.transpose()

    assert r.shape == (8, 1)
    assert isinstance(r, Column)
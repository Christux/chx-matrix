from chx_matrix import Matrix, Row, Column

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

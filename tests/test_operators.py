from chx_matrix import Matrix, Row, Column


def test_apply():

    m = Matrix(2, 3).apply(lambda val, i, j: i * 10 + j + 2)

    assert m[0, 0] == 2
    assert m[0, 1] == 3
    assert m[1, 0] == 12
    assert m[1, 2] == 14

def test_scale():

    m = Matrix(2, 3).set_all(4.).scale(2.)

    assert m[1, 1] == 8.

def test_add():

    m1 = Matrix(2, 3).set_all(2.)
    m2 = Matrix(2, 3).set_all(1.)

    m1.add(m2)

    assert m1[1, 1] == 3.

def test_add_wrong_size():

    m1 = Matrix(2, 3).set_all(2.)
    m2 = Matrix(2, 4).set_all(1.)

    m1.add(m2)

def test_substract():

    m1 = Matrix(2, 3).set_all(2.)
    m2 = Matrix(2, 3).set_all(1.)

    m1.substract(m2)

    assert m1[1, 1] == 1.

def test_substract_wrong_size():

    m1 = Matrix(2, 3).set_all(2.)
    m2 = Matrix(2, 4).set_all(1.)

    m1.substract(m2)

def test_multiply():

    m1 = Matrix(3,2)
    m2 = Matrix(2,3)
    m3 = Matrix(3,3)

    m1.set_all(1.0)
    m1.set(0,1,2.0)
    m1.set(1,1,4.0)

    m2.set_all(5.0)
    m2.set(0,1,-2.0)
    m2.set(1,1,6.0)

    # M3 = M1 * M2
    m3.multiply(m1, m2)

    assert m3.get(0,2) == 15
    assert m3.get(1,1) == 22
    assert m3.get(0,1) == 10
    assert m3.get(2,1) == 4
    assert m3.get(1,2) == 25

def test_multiply_wrong_size():

    m1 = Matrix(3,2)
    m2 = Matrix(2,3)
    m3 = Matrix(3,3)

    m3.multiply(m1, m2)


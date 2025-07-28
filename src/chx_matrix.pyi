from typing import Callable, Iterator, Self


class Matrix:
    """
    Light and fast Matrix manipulation class
    """

    def __init__(self, rows: int, cols: int) -> None:
        """Initializes the matrix

        Args:
            rows (int): number of rows
            cols (int): number of columns
        """

    @property
    def shape(self) -> tuple[int, int]:
        """Gets the shape of the matrix

        Returns:
            tuple[int, int]: the shape of the matrix
        """

    def get(self, i: int, j: int) -> float:
        """Gets a value of the matrix

        Args:
            i (int): row index
            j (int): column index

        Returns:
            float: value
        """

    def set(self, i: int, j: int, value: float) -> None:
        """Sets a value of the matrix

        Args:
            i (int): row index
            j (int): column index
            value (float): value
        """

    def __getitem__(self, index):
        """Gets value

        Args:
            index (_type_): _description_
        """

    def __setitem__(self, index, value) -> None:
        """Sets value

        Args:
            index (_type_): _description_
            value (_type_): _description_
        """

    def set_all(self, value: float) -> 'Matrix':
        """Sets all values of the matrix

        Args:
            value (float): value

        Returns:
            Matrix: the matrix itself
        """

    def transpose(self) -> 'Matrix':
        """Transposes the matrix

        Returns:
            Matrix: the transposed matrix
        """

    def copy(self) -> 'Matrix':
        """Copies the matrix

        Returns:
            Matrix: the duplicated matrix
        """

    def get_sub_matrix(self, row_start: int, row_end: int, col_start: int, col_end: int) -> 'Matrix':
        """Gets a part of the matrix

        Args:
            row_start (_type_): start row index
            row_end (_type_): end row index
            col_start (_type_): start column index
            col_end (_type_): end column index

        Returns:
            Matrix: the part of the matrix
        """

    def get_row(self, row_idx: int) -> 'Row':
        """Gets a row of the matrix

        Args:
            row_idx (int): row index

        Returns:
            Row: the row
        """

    def get_column(self, col_idx: int) -> 'Column':
        """Gets a column of the matrix

        Args:
            col_idx (int): column index

        Returns:
            Column: the column
        """

    def iter_rows(self) -> Iterator['Row']:
        """Iterates on the rows of the matrix
        """

    def iter_colums(self) -> Iterator['Column']:
        """Iterates on the columns of the matrix
        """

    def apply(self, func: Callable[[float, int, int], float]) -> Self:
        """Applies a function to each value of the matrix: func(value, i, j)

        Args:
            func (Callable[[float, int, int], None]): the function to apply on each value
        """

    def scale(self, factor: float) -> Self:
        """Scales the values of the matrix

        Args:
            factor (float): the scale factor

        Returns:
            Self: the matrix itself
        """

    def sum(self) -> float:
        """Sums all the values of the matrix

        Returns:
            float: the sum
        """

    def add(self, other: 'Matrix') -> Self:
        """Adds matrix by an other one
        Matrix = matrix + other

        Args:
            other (Matrix): the other matrix
        """

    def substract(self, other: 'Matrix') -> Self:
        """Substracts matrix by an other one
        Matrix = matrix - other

        Args:
            other (Matrix): the other matrix
        """

    def multiply(self, m1: 'Matrix', m2: 'Matrix') -> Self:
        """Multiplies matrixes
        Matrix = M1 * M2

        Args:
            M1 (Matrix): the first matrix
            M2 (Matrix): the second matrix
        """


class Row(Matrix):
    """_summary_

    Args:
        Matrix (_type_): _description_
    """

    def __init__(self, length: int) -> None:
        """_summary_

        Args:
            length (int): _description_
        """

    def get(self, i: int) -> float: # type: ignore
        """Gets a value of the row

        Args:
            i (int): index

        Returns:
            float: value
        """

    def set(self, i: int, value: float) -> None: # type: ignore
        """Sets a value of the row

        Args:
            i (int): index
            value (float): value
        """


class Column(Matrix):
    """_summary_

    Args:
        Matrix (_type_): _description_
    """

    def __init__(self, length: int) -> None:
        """_summary_

        Args:
            length (int): _description_
        """

    def get(self, i: int) -> float: # type: ignore
        """Gets a value of the column

        Args:
            i (int): index

        Returns:
            float: value
        """

    def set(self, i: int, value: float) -> None: # type: ignore
        """Sets a value of the column

        Args:
            i (int): index
            value (float): value
        """

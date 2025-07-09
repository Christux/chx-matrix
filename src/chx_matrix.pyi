class Matrix:
    """
    Light and fast Matrix manipulation class
    """

    def __init__(self, rows: int, cols: int) -> None:
        """_summary_

        Args:
            rows (int): _description_
            cols (int): _description_
        """

    @property
    def shape(self) -> tuple[int, int]:
        """_summary_

        Args:
            self (_type_): _description_
            int (_type_): _description_
        """

    def get(self, i: int, j: int) -> float:
        """_summary_

        Args:
            i (int): _description_
            j (int): _description_

        Returns:
            float: _description_
        """

    def set(self, i: int, j: int, value: float) -> None:
        """_summary_

        Args:
            i (int): _description_
            j (int): _description_
            value (float): _description_
        """

    def __getitem__(self, index):
        """_summary_

        Args:
            index (_type_): _description_
        """

    def __setitem__(self, index, value) -> None:
        """_summary_

        Args:
            index (_type_): _description_
            value (_type_): _description_
        """

    def set_all(self, value: float) -> 'Matrix':
        """_summary_

        Args:
            value (float): _description_

        Returns:
            Matrix: _description_
        """

    def transpose(self) -> 'Matrix':
        """_summary_

        Returns:
            Matrix: _description_
        """

    def copy(self) -> 'Matrix':
        """_summary_

        Returns:
            Matrix: _description_
        """

    def get_sub_matrix(self, row_start: int, row_end: int, col_start: int, col_end: int) -> 'Matrix':
        """_summary_

        Args:
            row_start (_type_): _description_
            row_end (_type_): _description_
            col_start (_type_): _description_
            col_end (_type_): _description_

        Returns:
            Matrix: _description_
        """

    def get_row(self, row_idx:int) -> 'Row':
        """_summary_

        Args:
            row_idx (int): _description_

        Returns:
            Row: _description_
        """

    def get_column(self, col_idx: int) -> 'Column':
        """_summary_

        Args:
            col_idx (int): _description_

        Returns:
            Column: _description_
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
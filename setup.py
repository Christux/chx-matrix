from setuptools import setup, Extension

matrix = Extension(
    "chx_matrix",
    sources=[
        "src/matrix.c",
        "src/matrix_row.c",
        "src/matrix_column.c",
        "src/matrix_object.c",
        "src/matrix_data.c",
        "src/matrix_methods.c",
        "src/matrix_iterators.c",
        "src/matrix_maths.c",
        "src/utils.c"
    ],
    include_dirs=["src"],
)

setup(
    name="chx_matrix",
    version="0.1.0",
    ext_modules=[matrix],
    packages=["chx_matrix"],
    package_dir={"chx_matrix": "src"},
    package_data={
        'chx_matrix': ['chx_matrix.pyi', '*.h'],
    },
)

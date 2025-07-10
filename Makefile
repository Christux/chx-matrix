.PHONY: all build clean install test

MODULE_NAME = chx_matrix

all: build

build:
	python setup.py build_ext --inplace

clean:
	rm -rf build dist *.egg-info

install:
	python -m pip install .

test:
	python -m pytest -v test

readme:
	python -m jupyter nbconvert --to markdown Readme.ipynb

.PHONY: all build clean install test

MODULE_NAME = chx_matrix

all: build

build:
	python setup.py build_ext --inplace

clean:
	rm -rf build dist *.egg-info
	#find . -path '*.venv' -prune -o -name '*.so' -type f -delete
	#find . -path '*.venv' -prune -o -name '*.pyc' -type f -delete
	#find . -path '*.venv' -prune -o -name '__pycache__' -type d -exec rm -r {} +

install:
	python -m pip install .

test:
	python -m pytest -v test
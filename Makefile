
test:	numeric
	rm -f ./tests/test
	./tools/make_tests
	./tests/test

numeric:
	rm -f core/Numeric/libNumeric.a
	./tools/make_numeric

sandbox:
	python3 -u tools/sandbox.py --create --name $(name) --lang $(lang)

experiment:
	python3 -u tools/sandbox.py --build --name $(name) --lang $(lang)

te2:
	python3 -u tools/type_expansion_2d.py

install:
	./tools/install



test:	numeric
	./tools/make_tests
	./tests/test

rtest:	numeric cleantest test

sandbox:
	python3 -u tools/sandbox.py --create --name $(name) --lang $(lang)

experiment:
	python3 -u tools/sandbox.py --build --name $(name) --lang $(lang)

numeric:
	./tools/make_numeric

cleantest:
	rm -f ./tests/test

te2:
	python3 -u tools/type_expansion_2d.py

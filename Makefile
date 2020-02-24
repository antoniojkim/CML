

test:	numeric
	./tools/make_tests
	./tests/test

rtest:	numeric
	rm ./tests/test
	./tools/make_tests
	./tests/test

sandbox:
	python3 -u tools/sandbox.py --create --name $(name) --lang $(lang)

experiment:
	python3 -u tools/sandbox.py --build --name $(name) --lang $(lang)

numeric:
	./tools/make_numeric

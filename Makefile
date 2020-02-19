
sandbox:
	python3 -u tools/sandbox.py --create --name $(name) --lang $(lang)

experiment:
	python3 -u tools/sandbox.py --build --name $(name) --lang $(lang)


numeric:
	./tools/make_numeric

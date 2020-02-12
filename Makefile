

sandbox:
	python3 -u tools/sandbox.py --create $(name)

experiment:
	python3 -u tools/sandbox.py --build $(name)

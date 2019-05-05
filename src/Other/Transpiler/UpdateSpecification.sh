#!/bin/bash

cd LR1\ Parser
python -u parseLR1.py

cd ../Scanner
python -u generateScanner.py

cd ../CodeGenerator
python -u generateCG.py

cd ../SemanticAnalyser
python -u generateSA.py

cd ../
python -u generateMarkdown.py

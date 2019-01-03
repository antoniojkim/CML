import sys
sys.path.append("../")

from parseLR1 import parseLR1

parseLR1("./wlp4.yml", "./new_wlp4.lr1", verbose=True)
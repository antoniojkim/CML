
import os
import sys

import argparse
import subprocess
from shutil import copyfile, move

from datetime import datetime

sandbox_templates = {
"c++": """
#include <iostream>

using namespace std;

int main(){

}
""",
"python": """
import torch
import numpy as np

def main():
    pass


if __name__ == "__main__":
    main()
"""
}

sandbox_extensions = {
    "c++": "cc",
    "python": "py"
}

def main(args):
    if args.lang is None:
        args.lang = "c++"

    curr_dir = os.getcwd()
    sandbox_dir = os.path.join(curr_dir, ".sandbox")
    sandbox_file = os.path.join(sandbox_dir, f"sandbox.{sandbox_extensions[args.lang]}")
    if args.create:        
        if os.path.isfile(sandbox_file):
            name = args.name
            if name is None:
                name = f"sandbox__{datetime.now().strftime('%Y-%m-%d__%H-%M-%S')}"

            if os.path.isdir(os.path.join(sandbox_dir, name)):
                name = f"{name}__{datetime.now().strftime('%Y-%m-%d__%H-%M-%S')}"

            old_sandbox_dir = os.path.join(sandbox_dir, name)
            os.mkdir(old_sandbox_dir)

            move(sandbox_file, old_sandbox_dir)
            
            if args.lang == "c++":
                copyfile(os.path.join(sandbox_dir, "Makefile"),
                         os.path.join(old_sandbox_dir, "Makefile"))

        with open(sandbox_file, "w") as file:
            file.write(sandbox_templates[args.lang])

    elif args.build:
        os.chdir(sandbox_dir)
        if args.lang == "c++":
            make = subprocess.Popen("make", shell=True)
            make.communicate()
            run = subprocess.Popen("./sandbox", shell=True)
            run.communicate()
        
        elif args.lang == "python":
            run = subprocess.Popen(f"python -u {sandbox_file}", shell=True)
            run.communicate()
  
        os.chdir(curr_dir)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--name",
                        nargs="?",
                        default=None,
                        help="name of sandbox")
    parser.add_argument('--lang',
                        default='c++',
                        nargs='?',
                        choices=['c++', 'python'],
                        help='sandbox language (default: %(default)s)')
    group = parser.add_mutually_exclusive_group()
    group.add_argument("--create", action="store_true")
    group.add_argument("--build", action="store_true")

    main(parser.parse_args())


import os
import sys

import argparse
import subprocess
from shutil import copyfile, move

from datetime import datetime


def main(args):
    if args.lang is None:
        args.lang = "c++"

    curr_dir = os.getcwd()
    sandbox_dir = os.path.join(curr_dir, ".sandbox")
    if args.create:
        if args.name is None:
            raise Exception("Name required to create new sandbox")

        name = args.name
        new_sandbox_dir = os.path.join(sandbox_dir, name)
        if os.path.isfile(new_sandbox_dir):
            name = f"{args.name}__{datetime.now().strftime('%Y-%m-%d__%H-%M-%S')}"
            new_sandbox_dir = os.path.join(sandbox_dir, name)
            
        os.mkdir(new_sandbox_dir)

        for template in os.listdir(os.path.join(sandbox_dir, ".templates")):
            copyfile(os.path.join(sandbox_dir, ".templates", template),
                     os.path.join(new_sandbox_dir, template))

        with open(os.path.join(sandbox_dir, ".info"), "w") as file:
            file.write(name)


    elif args.build:
        
        with open(os.path.join(sandbox_dir, ".info")) as file:
            sandbox = "".join(file)
            recent_sandbox_dir = os.path.join(sandbox_dir, sandbox)

        os.chdir(recent_sandbox_dir)
        if args.lang == "c++":
            make = subprocess.Popen("make", shell=True)
            make.communicate()
            if make.returncode == 0:
                run = subprocess.Popen("./sandbox", shell=True)
                run.communicate()
        
        elif args.lang == "python":
            run = subprocess.Popen(f"python -u sandbox.py", shell=True)
            run.communicate()
  
        os.chdir(curr_dir)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--name",
                        default=None,
                        nargs='?',
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

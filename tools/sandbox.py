
import os
import sys

import argparse
import subprocess

from datetime import datetime

sandbox_template = """
#include <iostream>

using namespace std;

int main(){

}
"""

def main(args):
    curr_dir = os.getcwd()
    sandbox_dir = os.path.join(curr_dir, ".sandbox")
    sandbox_file = os.path.join(sandbox_dir, "sandbox.cc")
    if args.create:        
        if os.path.isfile(sandbox_file):
            name = args.name
            if name is None:
                name = f"sandbox__{datetime.now().strftime('%Y-%m-%d__%H-%M-%S')}.cc"

            if not name.startswith("sandbox"):
                name = "sandbox__" + name

            old_sandbox_file = os.path.join(sandbox_dir, name)
            if os.path.isfile(old_sandbox_file):
                raise Exception(f"The sandbox file {old_sandbox_file} already exists")

            os.rename(sandbox_file, old_sandbox_file)

        with open(sandbox_file, "w") as file:
            file.write(sandbox_template)

    elif args.build:
        os.chdir(sandbox_dir)
        make = subprocess.Popen("make", shell=True)
        make.communicate()
        run = subprocess.Popen("./sandbox", shell=True)
        run.communicate()
        os.chdir(curr_dir)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("name", nargs="?",
                                default=None,
                                help="name of sandbox")
    group = parser.add_mutually_exclusive_group()
    group.add_argument("--create", action="store_true")
    group.add_argument("--build", action="store_true")
    main(parser.parse_args())

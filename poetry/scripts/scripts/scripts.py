import subprocess
import os
import sys
def main():
    
    dir_path = os.path.dirname(os.path.realpath(__file__))
    dir_path = os.path.dirname(os.path.dirname(dir_path))
    
    peano_path = os.path.join(dir_path, "peano4")
    dastgen_path = os.path.join(dir_path, "dastgen2")
    my_env = os.environ.copy()
    my_env["PYTHONPATH"] = f'{peano_path}:{dastgen_path}'
    tmp = ["pvpython", os.path.join(peano_path, "peano4/visualisation/render.py")]+sys.argv[1:]
    
    subprocess.run(tmp, env=my_env)
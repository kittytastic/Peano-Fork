from typing import List
import pandas as pd
import os
from pathlib import Path

speedup_pairs = {
    "Euler 3D": ({"Euler3D 2: Compiled", "Euler 3D: default"}, "Euler 3D: default"),
    "SWE": ({"SWE 2: Compiled", "SWE 1: Default SWE"}, "SWE 1: Default SWE"),
    "Euler 2D": ({"Kernel 2: Basic Inline", "Kernel 3: Compiled", "Kernel 1: Base Euler"}, "Kernel 1: Base Euler"),
}


BASE_DIR = os.path.dirname(os.path.realpath(__file__)) 

def process_file(path: str):
    df = pd.read_csv(path)
    df = df.rename(columns=lambda x: x.strip())
    
    df["trials_norm"] = df["num_trials"]/df["total_time"]
    df["run_time"] = df["total_time"]/1e9
    df= df.round({"run_time":0})
    df["run_time"] = df["run_time"].astype(int)
    #df["sys"] = os.path.dirname(path)
    #df["sys"] = Path(path).parent
    df["sys"] = os.path.split(os.path.dirname(path))[-1]

    for gn, (groups, base) in speedup_pairs.items():
        df.loc[df["name"]==base, "is_base"] = True
        base_value = df.loc[df["name"]==base].iloc[0].at["trials_norm"]
        for el in groups: 
            df.loc[df["name"]==el, "group"] = gn 
            df.loc[df["name"]==el, "base_value"] = base_value 

    df["speedup"] = df["trials_norm"]/df["base_value"] 
    return df
    
def get_sub_files(path: str, file_extension: str)->List[str]:
    full_name = [os.path.join(path, f) for f in os.listdir(path)]
    files =  [f for f in full_name if os.path.isfile(f)]
    return [f for f in files if os.path.splitext(f)[1]==f".{file_extension}"]

def process_dir(path: str):
    sub_dirs = [os.path.join(path, f) for f in os.listdir(path) if os.path.isdir(os.path.join(path, f))]

    df = pd.DataFrame()

    for sd in sub_dirs:
        for f in get_sub_files(sd, "csv"):
            df = df.append(process_file(f))
    print(sub_dirs)

    return df



if __name__ == "__main__":
    print()
    print(BASE_DIR)
    df = process_dir(BASE_DIR)
    print(df.head())
    exit()
    print("--------- Kernel Compare Analysis ----------")
    print("Hamilton 7")
    process_file("ham7/ham7-intel-60s.csv")
    print("Hamilton 8")
    process_file("ham8/ham8-amd-60s.csv")


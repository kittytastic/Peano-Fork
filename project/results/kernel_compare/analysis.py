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
ARTIFACTS = BASE_DIR+"/../Artifacts"


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
            df = pd.concat([df, process_file(f)])
    print(sub_dirs)

    return df

def hand_made_comparision(all_results: pd.DataFrame):
    df = all_results.loc[(all_results["run_time"]==60)&(all_results["group"]=="Euler 2D")&(all_results["sys"]=="ham8")]

    name_map = {"Kernel 1: Base Euler":"default", "Kernel 2: Basic Inline":"handmade", "Kernel 3: Compiled": "compiled"}
    df = df.replace({"name":name_map})
    base_value = df.loc[df["name"]=="handmade"].iloc[0].at["trials_norm"]
    df["hm_speedup"] = df["trials_norm"]/base_value
    df["iter_per_msec"] = df["trials_norm"]*1e6
    print(df.head())

    out_df = df[["name", "iter_per_msec", "speedup", "hm_speedup"]]
    out_df = out_df.rename(columns={"name": "Kernel", "num_trials": "Num. Iterations", "run_time": "Run Time (s)", "iter_per_msec": "Iterations per ms", "speedup":"Speedup vs Default", "hm_speedup": "Speedup vs Handmade"})    
    s = out_df.style
    s.format(precision=2)  
    s.hide(axis="index")
    file_name = ARTIFACTS+"/hand-made-vs-generated-tab.tex"
    s.to_latex(file_name, hrules=True)


if __name__ == "__main__":
    print("--------- Kernel Compare Analysis ----------")
    df = process_dir(BASE_DIR)
    hand_made_comparision(df)

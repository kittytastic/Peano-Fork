from typing import List
import pandas as pd
import os
from pathlib import Path
import numpy as np

speedup_pairs = {
    "Euler 3D": ({"Euler3D 2: Compiled", "Euler 3D: default"}, "Euler 3D: default"),
    "SWE": ({"SWE 2: Compiled", "SWE 1: Default SWE"}, "SWE 1: Default SWE"),
    "Euler 2D": ({"Kernel 2: Basic Inline", "Kernel 3: Compiled", "Kernel 1: Base Euler"}, "Kernel 1: Base Euler"),
}

name_map = {"Kernel 1: Base Euler":"default", "Kernel 2: Basic Inline":"handmade", "Kernel 3: Compiled": "compiled", "SWE 2: Compiled": "compiled", "SWE 1: Default SWE": "default", "Euler3D 2: Compiled":"compiled", "Euler 3D: default":"default"}


BASE_DIR = os.path.dirname(os.path.realpath(__file__)) 
ARTIFACTS = BASE_DIR+"/../Artifacts"


def sys_filter(df:pd.DataFrame, sys:List[str])->pd.DataFrame:
    assert(len(sys)>0)
    mask = (df["sys"]==sys[0])
    for i in range(1, len(sys)):
        mask = mask | (df["sys"]==sys[i])
    
    return df[mask]


def process_file(path: str):
    df = pd.read_csv(path)
    df = df.rename(columns=lambda x: x.strip())
    
    df["trials_norm"] = df["num_trials"]/df["total_time"]
    df["run_time"] = df["total_time"]/1e9
    df= df.round({"run_time":0})
    df["run_time"] = df["run_time"].astype(int)
    df["sys"] = os.path.split(os.path.dirname(path))[-1]

    for gn, (groups, base) in speedup_pairs.items():
        df.loc[df["name"]==base, "is_base"] = True
        base_value = df.loc[df["name"]==base].iloc[0].at["trials_norm"]
        for el in groups: 
            df.loc[df["name"]==el, "group"] = gn 
            df.loc[df["name"]==el, "base_value"] = base_value 

    df["iter_per_msec"] = df["trials_norm"]*1e6
    df["speedup"] = df["trials_norm"]/df["base_value"] 
    df = df.replace({"name": name_map})
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

    return df

def hand_made_comparision(all_results: pd.DataFrame):
    df = all_results.loc[(all_results["run_time"]==60)&(all_results["group"]=="Euler 2D")]
    df = sys_filter(df, ["ham8"])
    df = df.copy()

    base_value = df.loc[df["name"]=="handmade"].iloc[0].at["trials_norm"]
    df["hm_speedup"] = df["trials_norm"]/base_value
    df["iter_per_msec"] = df["trials_norm"]*1e6

    out_df = df[["name", "iter_per_msec", "speedup", "hm_speedup"]]
    out_df = out_df.replace({"name":{"handmade": "handopt"}}) 
    out_df = out_df.rename(columns={"name": "Kernel", "num_trials": "Num. Iterations", "run_time": "Run Time (s)", "iter_per_msec": "Iterations per ms", "speedup":"Speedup vs Default", "hm_speedup": "Speedup vs Handopt"})
    s = out_df.style
    s.format(precision=2)  
    s.hide(axis="index")
    file_name = ARTIFACTS+"/hand-made-vs-generated-tab.tex"
    s.to_latex(file_name, hrules=True)
    print("Finished handmade vs compiled.")

def kernel_compare(all_results: pd.DataFrame):
    df = all_results.loc[(all_results["run_time"]==60)&(all_results["name"]!="handmade")]
    df = sys_filter(df, ["ham7", "ham8"])
    df = df.sort_values(by=["sys", "group", "speedup"])

    df = df[["group", "name", "sys", "iter_per_msec", "speedup"]]
    df = df.replace({"sys":{"ham7": "Intel", "ham8": "AMD"}})
    df = df.rename(columns={"name": "Kernel", "group":"Problem", "iter_per_msec": "Iterations per ms", "speedup":"Speedup", "sys": "System"})    
    df["Speedup"] = df["Speedup"].mask(np.isclose(df["Speedup"].values, 1.0))
    s= df.style
    s.format(precision=2, na_rep="-")  
    s.hide(axis="index")
    file_name = ARTIFACTS+"/kernel_compare_results.tex"
    s.to_latex(file_name, hrules=True)

    print("Finished default vs compiled results.")
    
    kernel_compare_small(df)


def kernel_compare_small(kc_results:pd.DataFrame):
    df = kc_results.copy()
    df = df.loc[(df["System"]=="Intel")|(df["Kernel"]=="compiled")]
    
    s= df.style
    s.format(precision=2, na_rep="-")  
    s.hide(axis="index")
    file_name = ARTIFACTS+"/kernel_compare_results_small.tex"
    s.to_latex(file_name, hrules=True)

    print("Finished default vs compiled results [small].")



def ofastmath(all_results: pd.DataFrame):
    df = all_results.loc[(all_results["run_time"]==60)&(all_results["name"]!="default")]
    df = sys_filter(df, ["ham8-o3", "ham8-o3-fastmath", "ham8", "ham8-o3-fnoerrno"])

    hand_made_mask = df["name"]=="handmade"
    df.loc[hand_made_mask, "group"] = df.loc[hand_made_mask, "group"].apply(lambda x: f"{x} (handopt)")

    df = df[["group", "sys", "speedup"]]
    for g in ["Euler 2D", "Euler 2D (handopt)", "Euler 3D", "SWE"]:
        sub_df_mask = df["group"]==g
        sub_df = df[sub_df_mask]
        base_v = sub_df[sub_df["sys"]=="ham8-o3"].loc[:,"speedup"].iloc[0]
        base_v_2 = sub_df[sub_df["sys"]=="ham8-o3-fastmath"].loc[:,"speedup"].iloc[0]
        df.loc[sub_df_mask, "rel_speedup_o3"] = df.loc[sub_df_mask, "speedup"]/base_v
        #df.loc[sub_df_mask, "rel_speedup_o3fast"] = df.loc[sub_df_mask, "speedup"]/base_v_2

    df["rel_speedup_o3"] = df["rel_speedup_o3"].mask(np.isclose(df["rel_speedup_o3"].values, 1.0))
    #df["rel_speedup_o3fast"] = df["rel_speedup_o3fast"].mask(np.isclose(df["rel_speedup_o3fast"].values, 1.0))
    
    sys_name_map = {"ham8": "-Ofast", "ham8-o3-fastmath": "-O3 -ffast-math", "ham8-o3": "-O3", "ham8-o3-fnoerrno":"-O3 -fno-math-errno"}
    df = df.replace({"sys":sys_name_map})
    df["sys"] = pd.Categorical(df["sys"], 
                      categories=[sys_name_map["ham8-o3"], sys_name_map["ham8-o3-fnoerrno"], sys_name_map["ham8-o3-fastmath"],sys_name_map["ham8"]],
                      ordered=True)
    df = df.sort_values(by=["group", "sys"])
    df = df[["group", "sys", "rel_speedup_o3"]]
    df = df.rename(columns={"group":"Problem", "speedup":"Speedup vs Default", "sys": "Compiler Options", "rel_speedup_o3": "Relative Speedup", "rel_speedup_o3fast": "Relative Speedup"})    
    
    s= df.style
    s.format(precision=2, na_rep="-")  
    s.hide(axis="index")
    file_name = ARTIFACTS+"/o3_results.tex"
    s.to_latex(file_name, hrules=True)

    print("Finished -O3 results.")


def our_opts(all_results: pd.DataFrame):
    df = all_results.loc[(all_results["run_time"]==60)&(all_results["name"]=="compiled")]
    df = sys_filter(df, ["ham7", "ham7-noopt", "ham8", "ham8-noopt"])
    
    
    df = df[["group", "sys", "speedup", "iter_per_msec"]]
    df = df.sort_values(by=["group", "sys"])
    #print(df.head(12))
    print("Finished our opt ---- No table generated")

if __name__ == "__main__":
    print("--------- Kernel Compare Analysis ----------")
    df = process_dir(BASE_DIR)
    kernel_compare(df)
    hand_made_comparision(df)
    ofastmath(df)
    our_opts(df)

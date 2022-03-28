from typing import List
import pandas as pd
import os
from pathlib import Path
import numpy as np

BASE_DIR = os.path.dirname(os.path.realpath(__file__)) 
ARTIFACTS = BASE_DIR+"/../Artifacts"


def pre_proccess(file_name: str):
    df = pd.read_csv(file_name)
    df = df.rename(columns=lambda x: x.strip())
    df["kernel_type"] = df["kernel_type"].map({" generated":"compiled", " default":"default"})
    return df

def speedup(x:pd.DataFrame):
    min_el = x[x["kernel_type"]=="default"].loc[:,"time_mean"].iloc[0]
    return_val = min_el/x.loc[:, "time_mean"]
    return_val = return_val.rename("speedup")
    return return_val

def analyze(df: pd.DataFrame):
    df_summary = df.groupby(["problem", "kernel_type"]).agg({'time': ['mean', 'min', 'max', 'std']})
    df_summary = df_summary.reset_index()
    df_summary.columns = ['_'.join(col).strip("_") for col in df_summary.columns.values]
    df_speedup = df_summary.groupby(["problem"]).apply(speedup)
    df_summary = df_summary.reset_index()
    df_speedup = df_speedup.reset_index()
    df_summary["speedup"] = df_speedup["speedup"]
    df_summary = df_summary.drop(columns=["index"])

    return df_summary

def to_table(df: pd.DataFrame):
    out_df = df[["problem", "kernel_type", "time_mean", "speedup"]]
    out_df = out_df.rename(columns={"problem": "Problem", "kernel_type": "Kernel Type", "time_mean": "Run Time (s)", "speedup":"Speedup"}) 

    out_df["Speedup"] = out_df["Speedup"].mask(np.isclose(out_df["Speedup"].values, 1.0))
    s = out_df.style
    s.format(precision=2, na_rep="-")  
    s.hide(axis="index")
    file_name = ARTIFACTS+"/exahype_results.tex"
    s.to_latex(file_name, hrules=True)

if __name__ == "__main__":
    print("--------- ExaHyPE Analysis ----------")
    df = pre_proccess("results.csv")
    df = analyze(df)
    to_table(df)
    
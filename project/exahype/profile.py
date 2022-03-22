import sys
import time
from typing import Any
import subprocess


def info(problem:str, kernel_type:str):
    return {"problem":problem, "type":kernel_type}

KERNELS = {
    
    
    "SWE/default_kernel/SWE_Default":info("SWE", "default"),
    "SWE/generated/SWE_Generated":info("SWE", "generated"),
    
    "Euler2D/default_kernel/Euler2D_Default":info("Euler 2D", "default"),
    "Euler2D/generated/Euler2DGenerated":info("Euler 2D", "generated"),
    "Euler3D/default_kernel/Euler3D_Default":info("Euler 3D", "default"),
    "Euler3D/generated/Euler3D_Generated":info("Euler 3D", "generated"),
}


def run_and_time_kernel(kernel_path:str, log_file:Any)->float:
    start = time.time()
    subprocess.run([kernel_path], stdout=log_file, stderr=log_file)
    end = time.time()
    return end-start

def remove_old_logs():
    subprocess.run(["rm *.log"], shell=True)

def full_trial(f:Any, id:int):
    hashes = 75
    with open(f"trial_log_{id}.log", "w+") as l:
        for k, k_info in KERNELS.items(): 
            l.write("#"*hashes + "\n")
            l.write(f"Running: {k_info['problem']} ({k_info['type']})\n")
            l.write("#"*hashes + "\n\n\n")
            print(f"    Running: {k_info['problem']} ({k_info['type']})")

            with open("running_proc_log.log", "w+") as rpl:
                run_time = run_and_time_kernel(k, rpl)
            
            with open("running_proc_log.log", "r") as rpl:
                out_log = rpl.read()
                l.write(out_log)


            line_val = f"{run_time}, {k_info['problem']}, {k_info['type']}, {k}\n"
            f.write(line_val)
            l.write("\n\n"+"#"*hashes + "\n")
            l.write(f"Done in: {run_time}s\n")
            l.write("#"*hashes+"\n\n")

    




if __name__=="__main__":
    print("------- ExaHyPE profile -------")

    if len(sys.argv)==1:
        trials = 1
    else:
        trials  = int(sys.argv[1])

    remove_old_logs()
    with open("results.csv", "w+") as f:
        f.write("time, problem, kernel_type, cmd\n")
        for i in range(trials):
            print(f"Running trial {i+1}/{trials}")
            full_trial(f, i)
            print()
    
    print("\n\nResults saved to: results.csv")
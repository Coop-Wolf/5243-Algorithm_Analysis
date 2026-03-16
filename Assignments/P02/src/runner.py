
import os
import subprocess

# list of structures
# list fo workloads
# for each structure run a workload and save output to csv file

# list of each structure
structures = ["list", "array", "hash", "bst", "avl", "heap"]

# read in all files in workloads folder
workload_dir = "../workloads"
workloads = os.listdir(workload_dir)

# outfile file
output_file = "../results/result.csv"


# Running every workload on every structure
for structure in structures:
  for workload in workloads:
    
    # concat workload folder to file
    workload_path = os.path.join(workload_dir, workload)
    subprocess.run(["./main", structure, workload_path, output_file])
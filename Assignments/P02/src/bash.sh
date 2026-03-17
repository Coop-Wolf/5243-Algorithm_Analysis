for w in A B C D
do
  for s in 100 1000 5000 10000 20000 40000
  do
    ./workload_generator --json -workload $w --size $s > ../workloads/workload_${w}_${s}.json
  done
done
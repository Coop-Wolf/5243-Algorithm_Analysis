## Program 2


## Programs Goal

The goal is to track stats for each of the data structures we have been discussing as they process the same data sets. The "big picture" as I see it is for you to learn and understand certain choices we make when determining what structures would work best in specific conditions. But before we compare structures, we need to determine what data points are important enough to track. The following is a list (with descriptions) of the stats (data points) we will analyze. 

### Comparisons

- A **comparison** occurs whenever two values are evaluated relative to one another (e.g., `<`, `>`, or `==`).  Comparisons are the fundamental operations that drive decision-making in most data structures. For example, a binary search tree uses comparisons to determine whether to traverse left or right, and a sorted array uses comparisons during binary search. Tracking comparisons helps reveal how efficiently a structure locates elements as the data size grows.

---

### Structural Operations
- A **structural operation** is any action that modifies the internal organization of the data structure rather than simply reading data. Examples include pointer rewiring in linked structures, node rotations or swaps in trees or heaps, or element shifts in arrays. These operations typically represent the “maintenance work” required to preserve the structure’s invariants (ordering, heap property, collision chains, etc.).

---

### Inserts
- An **insert** records each attempt to add a value to the data structure. If the structure enforces uniqueness (like a set), an insert may fail if the value already exists. Insert metrics help measure how efficiently the structure accommodates growth and how costly it is to maintain ordering or structural constraints while adding new elements.

---

### Deletes
 - A **delete** records each attempt to remove a value from the data structure. Depending on the implementation, deletion may involve locating the element first and then restructuring the surrounding elements or pointers. Tracking delete operations highlights how expensive removal is for different structures, particularly those that require shifting elements or reorganizing nodes.

---

### Lookups
- A **lookup** represents a membership query such as `contains(value)` or `find(value)`. Lookups measure how quickly a structure can determine whether an element is present. Because many real-world systems perform far more reads than writes, lookup performance is often one of the most important metrics in evaluating a data structure.

---

### Resize Events
- A **resize event** occurs when a data structure must allocate a larger block of memory to accommodate additional elements. This commonly happens in dynamic arrays or hash tables when the current capacity is exhausted or a load factor threshold is exceeded. Although resizing is infrequent, it can be costly because existing elements often must be copied or rehashed into the new storage.

---
 
## Workload Types

Above we discuss (well list) the data structures we will compare, we discuss how to compile some code, and we discuss a bit about counting events for each structure. Now we need to discuss the different workload types, which very much impact which data structure we would normally choose. But for our experiment, we will expose each structure to all workload types. Just for a simple overview, the major workload types are:

- Build once, tons of searches with few inserts and deletes (stable structure)
- Highly fluctuating: lots of inserts and deletes with few searches. 
- Mix : a little bit of everything 

A little more to think about that doesn't have a lot to do with our experiment (except "is it ordered") because ordered data destroys a binary search tree that doesn't do rotations. 

- Type of data (string, integer)
- **Is it ordered**
- Is it mixed
- Is it random
- is it missing values

So based on some pretty common workload experiences, here are 4 that we will use to test our structures:

### Workload A

- Random inserts followed by random lookups (not a ton of fluctuation)

- Pattern:
```
     insert
     insert
     insert
     ...
     contains
     contains
```


---------------------------------------------------------
### Workload B


- Same as workload A except **inserts are sorted first**
- This often stresses ordered data structures differently 
- Example:  BSTs without balancing


---------------------------------------------------------
### Workload C

- Mixed workload with random ordering of operations.

- Operation mix:
  - 50% contains
  - 25% insert
  - 25% delete

- Deletes only occur if something exists in the population.


---------------------------------------------------------
### Workload D

- Insert n items then perform heavy lookup activity (stable structure).

- Pattern:
   - n inserts
   - 5n lookups
- Useful for read-heavy workloads.

---


### Folder Structure

Here is the new organization for `Program 02`'s 

```txt
📁 05-P02
├── ✳️ README.md                     // This file
├── 📁 results                       // Folder containing results
|   ├── 📁 result.csv
├── 📁 analysis                      // Folder containing graphs and charts
|   ├── 📁 workload_A.png
|   ├── 📁 workload_B.png
|   ├── 📁 workload_C.png
|   ├── 📁 workload_D.png
|   ├── 📁 README.md                // Contains analysis of structures
├── 📁 workloads                    // Folder workloads generated
|   ├── 📁 workload_A_1000.json
|   ├── 📁 workload_B_1000.json
|   ├── 📁 ...
|   ├── 📁 ...
|   ├── 📁 ...
|   ├── 📁 workload_D_20000.json
└── 📁 src                            // Code files  
    ├── 📁 include                    // Include hpps can't run directly
    │   ├── 📕 binaryHeap.hpp
    │   ├── 📕 bst.hpp
    │   ├── 📕 counters.hpp
    │   ├── 📕 hashTable.hpp
    │   ├── 📕 json.hpp
    │   ├── 📕 linkedList.hpp
    │   ├── 📕 sortedArraySet.hpp
    │   ├── 📕 termcolor.hpp
    │   └── 📕 usagePrinter.hpp
    ├── 📁 tests                      // Tests for each of the hpp data structures
    │   ├── 📕 test_BinaryHeap.cpp  
    │   ├── 📕 test_Bst.cpp
    │   ├── 📕 test_HashTable.cpp
    │   ├── 📕 test_LinkedList.cpp
    │   └── 📕 test_SortedArraySet.cpp
    ├── 📕 main                       // c++ executable
    ├── 📕 main.cpp                   // main code
    ├── 📕 workload_generator         // c++ executable
    ├── 📕 workload_generator.cpp     // workload generator code
    ├── 📕 runner.py                  // script to run all structures on all workloads
    └── 📕 bash.sh                    // script to generate multiple workloads
```



## Struggles

1. Creating the main.cpp file that would create objects of each structure
2. Having to create template functions because there is not base class for the structures
3. Getting the csv files to work
4. Having to parse json input
5. Finding workaround for heap, since it doesn't have insert, delete or contains


## How to Run

### 1. Generate Workloads
Run the bash script to generate 16 workloads with varying characteristics:
```bash
./bash.sh
```

### 2. Create Results Directory
Create a `results` folder in the `P02` directory — this is where `results.csv` will be written:
```bash
mkdir results
```

### 3. Compile
```bash
g++ -std=c++20 -Iinclude main.cpp -o main
```

### 4. Run
```bash
python3 runner.py
```

### 5. View Results
Open `results/results.csv` to view the recorded counters for each data structure and workload combination.
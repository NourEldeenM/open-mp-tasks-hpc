# 🚀 HPC: Assignment 3 – OpenMP + MPI

This project showcases **OpenMP** and **MPI** through three parallel programming tasks using C.

## 🛠️ Tasks Overview

### 🔧 Problem 1: Matrix-Vector Multiplication using OpenMP

**Goal**: Multiply a square matrix `A` of size `n x n` with a vector `v` of size `n` to get result vector `r`.

**Parallelization**:  
- Loops parallelized using **OpenMP `#pragma omp parallel for`**.
- Each thread computes a portion of the rows in the matrix.

**Example**:
```
Matrix A:       Vector v:       Resulting r:
1 2 3           1               6
4 5 6     x     1         =     15
7 8 9           1               24
```

---

### 🧮 Problem 2: Standard Deviation using OpenMP

**Goal**: Compute the standard deviation of an array of `n` integers.

**Steps**:
1. Calculate the **mean**.
2. Calculate the **variance**.
3. Compute the **standard deviation**:  
   `std_dev = sqrt(variance)`

**Parallelization**:
- Mean and variance computations are parallelized with OpenMP.
- Utilizes **reduction operations** to safely compute sums in parallel.

**Example**:
```
Input Array: [1,2,3,4,5,6,7,8,9,10]
Standard Deviation: 2.872281
```

---

### 🌐 Problem 3: Array Summation with MPI + OpenMP

**Goal**: Compute the sum of a large array using a hybrid approach:
- **MPI** for distributed memory (process-level) parallelism
- **OpenMP** for shared memory (thread-level) parallelism

**Execution Flow**:
1. 🚀 **MPI** initializes and splits array among processes.
2. 🧵 Each process uses **OpenMP** threads to compute **local sum**.
3. 🌍 Global sum is computed using `MPI_Reduce`.
4. 🏁 Root process prints the **final result**.

**Key Concepts**:
- `MPI_Init`, `MPI_Comm_rank`, `MPI_Comm_size`
- `#pragma omp parallel for reduction(+:sum)`
- `MPI_Reduce` to collect results

---

## 💡 Technologies Used

- C Language
- [OpenMP](https://www.openmp.org/) for multi-threaded parallelism
- [MPI (MPICH or OpenMPI)](https://www.mpi-forum.org/) for distributed computing

---

**Faculty of Computers and Artificial Intelligence – Cairo University**  
**Spring 2025**

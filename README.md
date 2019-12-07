# Spectral-Segmentation


```
gcc `/usr/bin/python3.6-config --cflags` latency_kmeans.c -o kmeans `/usr/bin/python3-config --ldflags`
```

```
./kmeans method
```

```
gcc -std=c99 -O2 -mavx2 -o kmeans_fast.o kmeans_fast.c
./kmeans_fast.o
```

Code snippets associated with the report. 
- kmeans - Baseline
- kmeans_fast - Initial Kernel (1.5) 
- kmeans_fast_ls_dist - Load & Store for SUB and Output Registers (1.6.1)
- kmeans_fast_small - Smaller Kernel (1.6.3)
- kmeans_fast_ls_cluster2 - Load & Store for BCAST Registers (1.6.2)

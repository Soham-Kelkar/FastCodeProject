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

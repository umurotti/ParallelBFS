#!/bin/bash
gcc serial_bfs.c util.c -o serial_bfs
mpicc parallel_bfs.c util.c stack.c -o parallel_bfs

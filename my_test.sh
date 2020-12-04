#!/bin/bash
./compile.sh
echo "***********************Small P=1:********************************"
time mpirun -np 1 --oversubscribe ./serial_bfs ./input/small_csr.txt 0 small_output_source_0.txt
time mpirun -np 1 --oversubscribe ./serial_bfs ./input/small_csr.txt 2 small_output_source_2.txt
time mpirun -np 1 --oversubscribe ./parallel_bfs ./input/small_csr.txt 0 0 small_output_source_0.txt
time mpirun -np 1 --oversubscribe ./parallel_bfs ./input/small_csr.txt 2 0 small_output_source_2.txt
echo "Press enter to continue..."
read _
echo "***********************Small P=2:********************************"
time mpirun -np 2 --oversubscribe ./serial_bfs ./input/small_csr.txt 0 small_output_source_0.txt
time mpirun -np 2 --oversubscribe ./serial_bfs ./input/small_csr.txt 2 small_output_source_2.txt
time mpirun -np 2 --oversubscribe ./parallel_bfs ./input/small_csr.txt 0 0 small_output_source_0.txt
time mpirun -np 2 --oversubscribe ./parallel_bfs ./input/small_csr.txt 2 0 small_output_source_2.txt
echo "Press enter to continue..."
read _
echo "***********************Small P=4:*********************************"
time mpirun -np 4 --oversubscribe ./serial_bfs ./input/small_csr.txt 0 small_output_source_0.txt
time mpirun -np 4 --oversubscribe ./serial_bfs ./input/small_csr.txt 2 small_output_source_2.txt
time mpirun -np 4 --oversubscribe ./parallel_bfs ./input/small_csr.txt 0 0 small_output_source_0.txt
time mpirun -np 4 --oversubscribe ./parallel_bfs ./input/small_csr.txt 2 0 small_output_source_2.txt
echo "Press enter to continue..."
read _
echo "***********************Small P=8:*********************************"
time mpirun -np 8 --oversubscribe ./serial_bfs ./input/small_csr.txt 0 small_output_source_0.txt
time mpirun -np 8 --oversubscribe ./serial_bfs ./input/small_csr.txt 2 small_output_source_2.txt
time mpirun -np 8 --oversubscribe ./parallel_bfs ./input/small_csr.txt 0 0 small_output_source_0.txt
time mpirun -np 8 --oversubscribe ./parallel_bfs ./input/small_csr.txt 2 0 small_output_source_2.txt
echo "Press enter to MID"
read _

echo "***********************Mid P=1:********************************"
time mpirun -np 1 --oversubscribe ./serial_bfs ./input/mid_csr.txt 7 mid_output_source_7.txt
time mpirun -np 1 --oversubscribe ./parallel_bfs ./input/mid_csr.txt 7 0 mid_output_source_7.txt
echo "Press enter to continue..."
read _
echo "***********************Mid P=2:*********************************"
time mpirun -np 2 --oversubscribe ./serial_bfs ./input/mid_csr.txt 7 mid_output_source_7.txt
time mpirun -np 2 --oversubscribe ./parallel_bfs ./input/mid_csr.txt 7 0 mid_output_source_7.txt
echo "Press enter to continue..."
read _
echo "***********************Mid P=4:*********************************"
time mpirun -np 4 --oversubscribe ./serial_bfs ./input/mid_csr.txt 7 mid_output_source_7.txt
time mpirun -np 4 --oversubscribe ./parallel_bfs ./input/mid_csr.txt 7 0 mid_output_source_7.txt
echo "Press enter to continue..."
read _
echo "***********************Mid P=8:*********************************"
time mpirun -np 8 --oversubscribe ./serial_bfs ./input/mid_csr.txt 7 mid_output_source_7.txt
time mpirun -np 8 --oversubscribe ./parallel_bfs ./input/mid_csr.txt 7 0 mid_output_source_7.txt
echo "Press enter to LARGE"
read _

echo "***********************Large P=1:********************************"
time mpirun -np 1 --oversubscribe ./serial_bfs ./input/large_csr.txt 4 large_output_source_4.txt
time mpirun -np 1 --oversubscribe ./parallel_bfs ./input/large_csr.txt 4 0 large_output_source_4.txt
echo "Press enter to continue..."
read _
echo "***********************Large P=2:********************************"
time mpirun -np 2 --oversubscribe ./serial_bfs ./input/large_csr.txt 4 large_output_source_4.txt
time mpirun -np 2 --oversubscribe ./parallel_bfs ./input/large_csr.txt 4 0 large_output_source_4.txt
echo "Press enter to continue..."
read _
echo "***********************Large P=4:*********************************"
time mpirun -np 4 --oversubscribe ./serial_bfs ./input/large_csr.txt 4 large_output_source_4.txt
time mpirun -np 4 --oversubscribe ./parallel_bfs ./input/large_csr.txt 4 0 large_output_source_4.txt
echo "Press enter to continue..."
read _
echo "***********************Large P=8:*********************************"
time mpirun -np 8 --oversubscribe ./serial_bfs ./input/large_csr.txt 4 large_output_source_4.txt
time mpirun -np 8 --oversubscribe ./parallel_bfs ./input/large_csr.txt 4 0 large_output_source_4.txt
echo "Press enter to continue VERY LARGE"
read _

echo "***********************Very Large P=1:********************************"
time mpirun -np 1 --oversubscribe ./serial_bfs ./input/very_large_csr.txt 21 very_large_output_source_21.txt
time mpirun -np 1 --oversubscribe ./parallel_bfs ./input/very_large_csr.txt 21 0 very_large_output_source_21.txt
echo "Press enter to continue..."
read _
echo "***********************Very Large P=2:********************************"
time mpirun -np 2 --oversubscribe ./serial_bfs ./input/very_large_csr.txt 21 very_large_output_source_21.txt
time mpirun -np 2 --oversubscribe ./parallel_bfs ./input/very_large_csr.txt 21 0 very_large_output_source_21.txt
echo "Press enter to continue..."
echo "***********************Very Large P=4:*********************************"
time mpirun -np 4 --oversubscribe ./serial_bfs ./input/very_large_csr.txt 21 very_large_output_source_21.txt
time mpirun -np 4 --oversubscribe ./parallel_bfs ./input/very_large_csr.txt 21 0 very_large_output_source_21.txt
echo "Press enter to continue..."
read _
echo "***********************Very Large P=8:*********************************"
time mpirun -np 8 --oversubscribe ./serial_bfs ./input/very_large_csr.txt 21 very_large_output_source_21.txt
time mpirun -np 8 --oversubscribe ./parallel_bfs ./input/very_large_csr.txt 21 0 very_large_output_source_21.txt
echo "Press enter to continue..."
read _

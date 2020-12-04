#!/bin/bash
./compile.sh
echo "***********************Part A: Serial:********************************"
./timeout -t 30 -m 6000000 ./serial_bfs ./input/small_csr.txt 0 small_output_source_0.txt
./timeout -t 30 -m 6000000 ./serial_bfs ./input/small_csr.txt 2 small_output_source_2.txt
./timeout -t 30 -m 6000000 ./serial_bfs ./input/mid_csr.txt 7 mid_output_source_7.txt
./timeout -t 30 -m 6000000 ./serial_bfs ./input/large_csr.txt 4 large_output_source_4.txt
./timeout -t 30 -m 6000000 ./serial_bfs ./input/very_large_csr.txt 21 very_large_output_source_21.txt

diff ./output/small_output_source_0.txt small_output_source_0.txt >> diff_small_source_0.txt
diff ./output/small_output_source_2.txt small_output_source_2.txt >> diff_small_source_2.txt
diff ./output/mid_output_source_7.txt mid_output_source_7.txt >> diff_mid_source_7.txt
diff ./output/large_output_source_4.txt large_output_source_4.txt >> diff_large_source_4.txt
diff ./output/very_large_output_source_21.txt very_large_output_source_21.txt >> diff_very_large_source_21.txt

echo "Press enter to continue Part B"
read _
echo "***********************Part B: Parallel:********************************"
rm *output*.txt
rm diff*.txt
echo "Press enter to continue Part B, parallel, P=1"
echo "***********************Part B: MPI:*********************************"
echo "********* P=1:************"
./timeout -t 30 -m 6000000 mpirun -np 1 ./parallel_bfs ./input/small_csr.txt 0 0 small_output_source_0.txt
./timeout -t 30 -m 6000000 mpirun -np 1 ./parallel_bfs ./input/small_csr.txt 2 0 small_output_source_2.txt
./timeout -t 30 -m 6000000 mpirun -np 1 ./parallel_bfs ./input/mid_csr.txt 7 0 mid_output_source_7.txt
./timeout -t 30 -m 6000000 mpirun -np 1 ./parallel_bfs ./input/large_csr.txt 4 0 large_output_source_4.txt
./timeout -t 30 -m 6000000 mpirun -np 1 ./parallel_bfs ./input/very_large_csr.txt 21 0 very_large_output_source_21.txt

diff ./output/small_output_source_0.txt small_output_source_0.txt >> diff_small_source_0.txt
diff ./output/small_output_source_2.txt small_output_source_2.txt >> diff_small_source_2.txt
diff ./output/mid_output_source_7.txt mid_output_source_7.txt >> diff_mid_source_7.txt
diff ./output/large_output_source_4.txt large_output_source_4.txt >> diff_large_source_4.txt
diff ./output/very_large_output_source_21.txt very_large_output_source_21.txt >> diff_very_large_source_21.txt
echo "Press enter to continue Part B, parallel, P=4"
read _
rm *output*.txt 
rm diff*.txt
echo "********* P=4*************:"
./timeout -t 30 -m 6000000 mpirun -np 4 ./parallel_bfs ./input/small_csr.txt 0 0 small_output_source_0.txt
./timeout -t 30 -m 6000000 mpirun -np 4 ./parallel_bfs ./input/small_csr.txt 2 0 small_output_source_2.txt
./timeout -t 30 -m 6000000 mpirun -np 4 ./parallel_bfs ./input/mid_csr.txt 7 0 mid_output_source_7.txt
./timeout -t 30 -m 6000000 mpirun -np 4 ./parallel_bfs ./input/large_csr.txt 4 0 large_output_source_4.txt
./timeout -t 30 -m 6000000 mpirun -np 4 ./parallel_bfs ./input/very_large_csr.txt 21 0 very_large_output_source_21.txt

diff ./output/small_output_source_0.txt small_output_source_0.txt >> diff_small_source_0.txt
diff ./output/small_output_source_2.txt small_output_source_2.txt >> diff_small_source_2.txt
diff ./output/mid_output_source_7.txt mid_output_source_7.txt >> diff_mid_source_7.txt
diff ./output/large_output_source_4.txt large_output_source_4.txt >> diff_large_source_4.txt
diff ./output/very_large_output_source_21.txt very_large_output_source_21.txt >> diff_very_large_source_21.txt
echo "Press enter to continue Part B, parallel, P=9"
read _
rm *output*.txt
rm diff*.txt
echo "********* P=9*************:"
./timeout -t 30 -m 8000000 mpirun -np 9 --oversubscribe ./parallel_bfs ./input/small_csr.txt 0 0 small_output_source_0.txt
./timeout -t 30 -m 8000000 mpirun -np 9 --oversubscribe ./parallel_bfs ./input/small_csr.txt 2 0 small_output_source_2.txt
./timeout -t 30 -m 8000000 mpirun -np 9 --oversubscribe ./parallel_bfs ./input/mid_csr.txt 7 0 mid_output_source_7.txt
./timeout -t 30 -m 8000000 mpirun -np 9 --oversubscribe ./parallel_bfs ./input/large_csr.txt 4 0 large_output_source_4.txt
./timeout -t 30 -m 8000000 mpirun -np 9 --oversubscribe ./parallel_bfs ./input/very_large_csr.txt 21 0 very_large_output_source_21.txt

diff ./output/small_output_source_0.txt small_output_source_0.txt >> diff_small_source_0.txt
diff ./output/small_output_source_2.txt small_output_source_2.txt >> diff_small_source_2.txt
diff ./output/mid_output_source_7.txt mid_output_source_7.txt >> diff_mid_source_7.txt
diff ./output/large_output_source_4.txt large_output_source_4.txt >> diff_large_source_4.txt
diff ./output/very_large_output_source_21.txt very_large_output_source_21.txt >> diff_very_large_source_21.txt

echo "Please enter to finish test"
read _
rm *output*.txt 
rm diff*.txt

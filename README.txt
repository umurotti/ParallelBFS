* my_test.sh is created for testing run time of algorithms with various number of inputs and number of processing elements.
* util.c is included in the gcc line of the compile.sh
* util.c and stack.c are included int mpicc line of the compile.sh
* in test.sh, final run with 9 number of processors is slightly changed
|---* memory constraint is set to 8000000 instead of 6000000
|---* 8000000 is a changing number with different input values.
|---|--* 8000000 is chosen as a guarnteed number for given inputs. It is not an exact working border.
* in test.sh, --oversubscribe option is added since we do not know the number of processing units for testing
  and -np given number can be greater than the actural number of processors, making --oversubsribe usage a must.

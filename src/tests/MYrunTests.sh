#!/bin/bash
echo "Compiling"
make clean
make
chmod 777 part2
echo "running the tests"
echo "running example test 1"
./part2 <  example1.cmm > myex1.out
echo "Running example test 2"
./part2 <  example2.cmm > myex2.out
echo "running the example err test"
./part2 < example-err.cmm > myexErr.out
echo "Running facebook tests ex3 "
./part2 <  example3.in >  myex3.out
echo "Running facebook tests ex4 "
./part2 <  example4.in >  myex4.out

echo "diffing example test ex1 "
diff example1.tree myex1.out
echo "diffing example test ex2"
diff example2.tree myex2.out
echo "diffing example test err"
diff example-err.output myexErr.out
echo "diffing facebook tests ex3 "
diff myex3.out example3_out.out
echo "diffing facebook tests ex4 "
diff myex4.out example4.out
#vimdiff myex4.out example4.out

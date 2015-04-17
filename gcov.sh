#!/bin/sh

rm -f *.gcno */*.gcno
make fclean
make CFLAGS="-fprofile-arcs -ftest-coverage" OUT=src ex
./test.sh
gcov `ls src/* main.c`
mkdir -p gcov
mv *.gcov gcov
rm -vf src/*.gcda src/*.gcno main.gcda main.gcno
make OUT=src fclean

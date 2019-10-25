#!/bin/bash
if [ -f ./cache-test ]
then
  rm cache-test
fi

echo
echo "Provided Cache TESTS: "
echo
make cache-test TEST_CACHE=caches/cache_1c_1e_1k.o
./cache-test
echo
rm cache-test
make cache-test TEST_CACHE=caches/cache_65536c_2e_16k.o
./cache-test
echo
rm cache-test
make cache-test TEST_CACHE=caches/cache_1048576c_256e_256k.o
./cache-test
echo
rm cache-test
make cache-test TEST_CACHE=caches/cache_16384c_4e_4k.o
./cache-test
echo
rm cache-test
make cache-test TEST_CACHE=caches/cache_32768c_8e_8k.o
./cache-test
echo
echo "Finished."
echo
rm cache-test

if [ -d build ]
then
	rm -r build
fi

mkdir build

echo "compiling ring_tests.cpp..."
g++ ./src/tests/ring_tests.cpp -o main.exe -std=c++17 > build/good_case_compile.txt
if [ -e main.exe ]
then
    echo "...done"
else
    echo "TESTS FAILED TO COMPILE"
fi
echo ""


echo "testing compile-time failure cases..."
g++ ./src/tests/ring_tests.cpp -o fail.exe -std=c++17 -DCOMPILE_TIME_TESTS 2> build/fail_case_errors.txt 1> build/fail_case_compile.txt
if [ -e fail.exe ]
then
    echo "COMPILATION TEST FAILED"
else
    echo "...done"
fi
echo ""


if [ -e main.exe ]
then
	echo "running test executable..."
	./main.exe
	echo "...done"
fi
echo ""


function test_with_std() {
	echo "compiling with std"
	clang++ -Wall -Wextra -Werror -std=c++98 main.cpp -DSTD -o test_std
}
function test_with_no_std() 
{
	echo "compiling with ft"
	clang++ -Wall -Wextra -Werror -std=c++98 main.cpp -o test_no_std
}
function random() {
	echo "generating random seed"
	seed=$RANDOM
	echo $seed
}
function timer() {
	echo "running the two executables, with the same seed"
	echo "running std"
	/usr/bin/time ./test_std $seed
	echo "running ft"
	/usr/bin/time ./test_no_std $seed
}

test_with_std
test_with_no_std
random
timer

rm test_no_std
rm test_std
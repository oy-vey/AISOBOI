generate_bin "%1"
g++.exe -DONLINE_JUDGE -O2 -static -Wall -Wextra -x c++ -I"{common}" --std=c++11 -o "stdsort.exe" "stdsort.cpp"
stdsort
showfile input.bin > input.txt
showfile output.bin > output.txt
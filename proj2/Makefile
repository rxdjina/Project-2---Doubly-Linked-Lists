# all: test_list proj2

test_list: List.hpp test_list.cpp 
	g++ -std=c++11 test_list.cpp -o test_list.x 

# proj2: List.hpp Memory.hpp mem_manager.cpp
# 	g++ -std=c++11 mem_manager.cpp -o proj2.x 

clean:
	rm -f test_list.x proj2.x
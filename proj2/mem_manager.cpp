#include <iostream>
#include <cstring>
#include "List.h"
#include "Memory.h" 

static char const MENU_OPTIONS[] = {'d', 'r', 'l', 'm', 'x'};

void print_memu() {
	std::cout << std::string(20, '=') << std::endl;
	std::cout << "d: memory dump" << std::endl;
	std::cout << "r: request memory" << std::endl;
	std::cout << "l: release memory" << std::endl;
	std::cout << "m: merge memory" << std::endl;
	std::cout << "x: quit program" << std::endl;
	std::cout << "Your choice: ";	
}

bool valid_input(char const input) {
	auto *i = std::find(std::begin(MENU_OPTIONS), std::end(MENU_OPTIONS), input);

	return i != std::end(MENU_OPTIONS) ? true : false;
}

int main(void) {
	char input;
	int i, j;

	std::cout << "Memory Configuration: " << std::endl;
	std::cout << "Number of memory blocks (integer):" << std::endl;
	std::cin >> i;
	std::cout << "Memory block size (integer):" << std::endl;
	std::cin >> j;

	MyMemory<int> mem(i, j);
	MyMemoryBlock mem_block(i, j);

	print_memu();
	std::cin >> input;

	while (!valid_input(input)) {
		std::cout << "INVALID CHOICE" << std::endl;
		print_memu();
		std::cin >> input;
	}



	while (input != 'x') {
		switch (input)
		{
		case 'd':
			mem.dump();
			break;

		case 'r':
			std::cout << "Length: " <<  std::endl;
			std::cin >> i;
			mem.req_mem(i);
			break;

		case 'l':
			std::cout << "Index: " <<  std::endl;
			std::cin >> i;

			std::cout << "Length: " <<  std::endl;
			std::cin >> j;
			mem.release_mem(i, j);
			break;

		case 'm':
			mem.merge_mem();
			break;

		case 'x':
			std::cout << "Quitting Program..." << std::endl;
			return 0;

		default:

			break;
		}
	}

	return 0;
}

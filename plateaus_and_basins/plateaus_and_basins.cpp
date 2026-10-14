// this file is provided

#include <iostream>
#include "functions.h"

int main() {
	bool quit = false;
	// Note: we use long long because the input number can exceed the system max limit
	// for what an int can hold
	long long a = 0;
	long long b = 0;
	while (!quit) {
		std::cout << "Enter range: ";
		std::cin >> a >> b;
		if(a == 0) {
			quit = true;
			break;
		}
		while(!is_valid_range(a, b)) {
			std::cout << "Invalid Range" << std::endl;
			std::cout << "Enter range: ";
			std::cin >> a >> b;
		}
		plateaus_and_basins count = count_pb_numbers(a, b);
		std::cout << "There are " << count.plateaus << " plateaus"
	              << " and " << count.basins << " basins"
	              << " between " << a << " and " << b << "." << std::endl;
	}
	return 0;
}


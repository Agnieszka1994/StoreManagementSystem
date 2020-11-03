#pragma once
#include <iostream>
#include <iomanip>

template<typename T>
T getChoice() {
	T choice;
	std::cin >> choice;
	// error check
	while (std::cin.good() == false) {
		// clear stream
		std::cout << "Wrong input type! Please try again:" << std::endl;
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		// get input again		
		std::cin >> choice;
	}
	return choice;
}
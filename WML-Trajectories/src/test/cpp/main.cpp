#include <iostream>

#include "gtest/gtest.h"

int main(int argc, char** argv) {
	// std::cout << "Trajectory Test Start" << std::endl;
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
#pragma once
#include <iostream>
#include <ostream>

static void outputException(const std::exception& e, const std::string& where = "...")
{
	std::cout << "Exception captured [" + where + "]"
			<< std::endl
			<< "===================================="
			<< std::endl
			<< e.what() << std::endl;
}

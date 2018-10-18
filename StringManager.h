#ifndef STRINGMANAGER_H
#define STRINGMANAGER_H


#include <sstream>

template<typename T>
std::string toString(const T& value) {
	std::stringstream ss;
	ss << value;
	return ss.str();
}

#endif STRINGMANAGER_H
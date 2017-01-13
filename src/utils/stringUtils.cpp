/*
 * stringUtils.cpp
 *
 *  Created on: 6 февр. 2016 г.
 *      Author: lladmin
 */

#include <utils/stringUtils.h>
namespace ffactory {

	StringVector* splitString(const std::string &s, char delim, StringVector* elems) {
		std::stringstream ss(s);
		std::string item;
		while (std::getline(ss, item, delim)) {
			elems->push_back(item);
		}
		return elems;
	}

}

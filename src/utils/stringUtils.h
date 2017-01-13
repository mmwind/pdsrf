/*
 * trimstring.h
 *
 *  Created on: 5 февр. 2016 г.
 *      Author: lladmin
 */

#ifndef UTILS_STRINGUTILS_H_
#define UTILS_STRINGUTILS_H_

#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

#include <string>
#include <sstream>
#include <vector>
#include <memory>

namespace ffactory {


	typedef  std::vector<std::string> StringVector;
	typedef  StringVector *StringVectorPtr;
	typedef std::unique_ptr< StringVector > StringVectorUniquePtr;

	/**
	 * trim string from start
	 * @param s
	 * @return
	 */
	inline std::string &ltrim(std::string &s) {
			s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
			return s;
	}


	/**
	 * trim string from end
	 * @param s
	 * @return
	 */
	inline std::string &rtrim(std::string &s) {
			s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
			return s;
	}

	/**
	 * trim string from both ends
	 * @param s
	 * @return
	 */
	inline std::string &trim(std::string &s) {
			return ltrim(rtrim(s));
	}



	StringVector* splitString(const std::string &s, char delim, StringVector* elems);

	/**
	 * Split string with char \a delim
	 * @param s
	 * @param delim
	 * @return vector of substrings
	 */
	inline StringVector split(const std::string &s, char delim) {
		StringVector elems;
		splitString(s, delim, &elems);
		return elems;
	}

}
#endif /* UTILS_STRINGUTILS_H_ */

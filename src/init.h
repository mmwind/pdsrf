/*
 * init.h
 *
 *  Created on: 21 окт. 2015 г.
 *      Author: llproger
 */

#ifndef INIT_H_
#define INIT_H_

/**
 * Include this in all class files!
 */

/**
 * \def DEBUG
 * Debug messages enable/disable macro
 */
#define DEBUG 1

#ifdef DEBUG
	#define FINFO(M) std::cout << "{INFO} [ " <<  __FUNCTION__ << " ] "<< M << std::endl
	#define INFO(M) std::cout << "{INFO} [ " << typeid(this).name() << " -> " << __FUNCTION__ << " ] "<< M << std::endl
	#define INFO_F(M) std::cout << "{INFO} [ " << __FUNCTION__ << " ] "<< M << std::endl
	#define WARN(M) std::cout << "{WARN} [ " << typeid(this).name() << " -> " << __FUNCTION__ << " ] "<< M << std::endl
#else
	#define INFO(M)
	#define INFO_F(M)
	#define WARN(M)
	#define WARN_F(M)
#endif

#include <Base.h>
#include <utils/macros.h>
#include <utils/exceptions.h>
#include <utils/FOREACH.h>
#include <stdexcept>


/**
 *  Standard EIGEN macro redefined to throw exceptions instead of plain abortion
 *  Trouble with unexpected behavior was solved.
 *  Use (!(x)) instead of (!x)
 *  \link https://forum.kde.org/viewtopic.php?t=129009
 */

#undef eigen_assert
#define eigen_assert(x) \
  if (!(x)) { \
	  std::string s = std::string(" < EIGEN > ") + std::string(__FILE__) + std::string(" : ") + std::string(__FUNCTION__) + std::string(" : ") + std::string(EIGEN_MAKESTRING(x)); \
	  throw (std::runtime_error(s.c_str() )); }

#endif /* INIT_H_ */

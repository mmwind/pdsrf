/*
 * exceptions.h
 *
 *  Created on: 21 окт. 2015 г.
 *      Author: llproger
 */

#ifndef UTILS_EXCEPTIONS_H_
#define UTILS_EXCEPTIONS_H_

// using standard exceptions
#include <iostream>
#include <exception>

#ifdef __MINGW32__
	#include <typeinfo.h>

#endif

#ifdef __linux__
	#include <typeinfo>

#endif

#include <Base.h>

namespace ffactory {

	/**
	 * Base exception class
	 */
	class FFException: public std::exception
	{
	public:
	  FFException();
	  FFException(Base *object, std::string method, std::string mes){
		  info = "[" + object->getName() + "." + method + "] " +  mes;
	  }

	  FFException(std::string objectname, std::string method, std::string mes){
		  info = "[" + objectname + "." + method + "] " +  mes;
	  }

	  FFException(std::string func, std::string mes){
		  info = "[" + func + "] " +  mes;
	  }

	  ~FFException() throw(){

	  }

	  virtual const char* what() const throw()
	  {
		return info.c_str();
	  }

	private:
	  Base* obj;
	  std::string info;
	};


#define THROW(M) throw FFException(typeid(this).name(), __FUNCTION__ , M)
#define THROW_F(M) throw FFException( __FUNCTION__ , M)

/**
 * \def CHECK(EXPR,M)
 * Тестирования выражения EXPR на истинность. Если оно ложно, выбрасывается исключение.
 * \param EXPR тестируемое выражение
 * \param M сообщение об ошибке
 */
#define CHECK(EXPR,M) if(!(EXPR)) { std::cout << "<TEST FAIL> "; throw FFException(typeid(this).name(), __FUNCTION__ , M); }

}

#endif /* UTILS_EXCEPTIONS_H_ */

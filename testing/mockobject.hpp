/*
 * mockobject.hpp
 *
 *  Created on: 18 нояб. 2015 г.
 *      Author: llproger
 */

#ifndef MOCKOBJECT_HPP_
#define MOCKOBJECT_HPP_

#include <memory>
#include <gmock/gmock.h>
#include <utils/gtest_macros.h>
#include <utils/macros.h>


using ::testing::_;
using ::testing::Invoke;

//#define REMOCK_METHOD(ARGC,CLASS,METHOD, )
DEFINE_PTR(double);

class ClassTest {
public:
  ClassTest(){  };
  virtual ~ClassTest(){ };

  virtual double One(){
	  return(1);
  }

  virtual double Two(double x) = 0;

 // virtual doubleUniquePtr Three(doubleUniquePtr x) = 0;

  virtual double Four(double x){
	  return(4*One());
  }
};

class MockClassTest: public ClassTest{
public:
	MockClassTest(){
		UNMOCK(MockClassTest,ClassTest,One,());
	}
	  MOCK_METHOD0(One, double());
	  MOCK_METHOD1(Two, double(double x));
//	  MOCK_METHOD1(Three, doubleUniquePtr (doubleUniquePtr x));
	  MOCK_METHOD0(Four, double());

	  UNMOCK_WRAPPER(ClassTest,double,One,());
};

#endif /* MOCKOBJECT_HPP_ */

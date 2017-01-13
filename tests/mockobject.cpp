/*
 * mockobject.cpp
 *
 *  Created on: 18 нояб. 2015 г.
 *      Author: llproger
 */
#include "mockobject.hpp"

using ::testing::_;
using ::testing::AtLeast;

TEST(ClassTest, UseOfMock) {
	MockClassTest c;
	EXPECT_CALL(c, One()).Times(AtLeast(1));
	EXPECT_TRUE(c.One()==1);
}



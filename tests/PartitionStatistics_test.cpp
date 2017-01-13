/*
 * PartitionStatistics_test.cpp
 *
 *  Created on: 23 нояб. 2015 г.
 *      Author: lladmin
 */


#include <test.h>
#include <classifiers/PartitionStatistics.h>

namespace ffactory{

	TEST(PartitionStatistics, addPoint) {
		PartitionStatistics part(2 , 2);
		Sample s1;
		DataVector a(2);
		a << -7, 14;
		s1.setVector(a);
		s1.setY(0);

		Sample s2;
		DataVector b(2);
		b <<  5, 1;
		s2.setVector(b);
		s1.setY(1);

		part.addPoint(&s1);


		DataVector maxrange(2);
		maxrange << -7,14;
		EIGEN_EQ((*part.getMaxRanges()),maxrange );

		part.addPoint(&s2);

		maxrange << 5,14;
		EIGEN_EQ((*part.getMaxRanges()),maxrange );
	}

	TEST(PartitionStatistics, addPointInRange) {
		PartitionStatistics part(2 , 2);
		Sample s1;
		DataVector a(2);
		a << -7, 14;
		s1.setVector(a);
		s1.setY(0);

		Sample s2;
		DataVector b(2);
		b <<  5, 1;
		s2.setVector(b);
		s2.setY(1);

		part.addPoint(&s1);
		part.addPoint(&s2);

		Sample s3;
		DataVector c(2);
		c <<  1, 6;
		s3.setVector(c);
		s3.setY(1);

		part.addPointInRange(&s3);// In ranges

		EXPECT_EQ(1,part.getPointsByClass(0));
		EXPECT_EQ(2,part.getPointsByClass(1));

		Sample s4;
		DataVector d(2);
		d <<  3, -1; // Data vector is not in ranges  [-7..5, 1..14]
		s4.setVector(d);
		s4.setY(0);

		part.addPointInRange(&s4);// Not in ranges

		part.addPointInRange(&s3);// In ranges

		EXPECT_EQ(1,part.getPointsByClass(0));
		EXPECT_EQ(3,part.getPointsByClass(1));

		//EIGEN_EQ((*part.getMaxRanges()),maxrange );
	}

	TEST(PartitionStatistics, isUniform) {
		PartitionStatistics part(2 , 2);
		Sample s1;
		s1.setY(0);

		Sample s2;
		s1.setY(1);

		part.addPoint(&s1);
		ASSERT_TRUE(part.isUniform());

		part.addPoint(&s1);
		ASSERT_TRUE(part.isUniform());

		part.addPoint(&s2);
		ASSERT_FALSE(part.isUniform());

		part.addPoint(&s1);
		ASSERT_FALSE(part.isUniform());
	}

	TEST(PartitionStatistics, IsInRanges) {
		PartitionStatistics part(2 , 2);

		Sample s1;
		DataVector c(2);
		c <<  2, 2;
		s1.setVector(c);
		s1.setY(0);

		Sample s2;
		DataVector d(2);
		d <<  3, 4;
		s2.setVector(d);
		s2.setY(1);

		part.addPoint(&s1);
		part.addPoint(&s2);

		ASSERT_FALSE(  part.isInRanges( &s1 ) );
		ASSERT_TRUE (  part.isInRanges( &s2 ) );
		DataRanges dr(c,d);
		part.setGlobalRanges(&dr);

		ASSERT_TRUE (  part.isInRanges( &s1 ) );
		ASSERT_TRUE (  part.isInRanges( &s2 ) );

	}

}

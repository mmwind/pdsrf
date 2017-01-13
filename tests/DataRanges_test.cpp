/*
 * DataRanges_test.cpp
 *
 *  Created on: 15 дек. 2015 г.
 *      Author: lladmin
 */

#include <test.h>
#include <data/Sample.h>
#include <data/Dataset.h>
#include <data/DataRanges.h>

namespace ffactory{

	TEST(DataRanges, addPoint) {

		Dataset d;
						d.setNumClasses(2);
						d.setNumFeatures(2);
						d.initStatistics();

						Sample s1;
						DataVector a(2);
						a << 1, 1;
						s1.setVector(a);
						s1.setY(0);

						Sample s2;
						DataVector b(2);
						b <<  2, 3;
						s2.setVector(b);
						s1.setY(1);

						d.add(s1);
						d.add(s2);

		DataRanges dr;

		DataVector minval(2);
		minval << 1, 1 ;
		DataVector maxval(2);
		maxval <<  2, 3;

		dr.minValues = minval;
		dr.maxValues = maxval;

		//ASSERT_TRUE(  dr.isInRanges( s1.getVector() ) );
		//ASSERT_TRUE(  dr.isInRanges( s2.getVector() ) );

		//ASSERT_FALSE(  dr.isInRangesExcludeGreater( s1.getVector() ) );
		//ASSERT_TRUE (  dr.isInRangesExcludeGreater( s2.getVector() ) );

	}

}

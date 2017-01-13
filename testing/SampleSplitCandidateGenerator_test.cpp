/*
 * SampleSplitCandidateGenerator_test.cpp
 *
 *  Created on: 15 дек. 2015 г.
 *      Author: lladmin
 */
#include <test.h>
#include <classifiers/trees/splits/splitCandidateGenerator/SampleSplitCandidateGenerator.h>


namespace ffactory{

	TEST(SampleSplitCandidateGenerator, TwoPointsSet) {

		Dataset d;
		d.setNumClasses(2);
		d.setNumFeatures(2);
		d.initStatistics();

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

		d.add(s1);
		d.add(s2);

		SampleSplitCandidateGenerator gen;
		gen.setDataset(&d);
		gen.generate();

		EXPECT_EQ(4,gen.getSplitNum());

		gen.clear();
		gen.generate(d.getStatistics()->getRanges());

		EXPECT_EQ(2,gen.getSplitNum());
	}




}


/*
 * Partitioner_test.cpp
 *
 *  Created on: 17 янв. 2016 г.
 *      Author: lladmin
 */

/*
 * PartitionStatistics_test.cpp
 *
 *  Created on: 23 нояб. 2015 г.
 *      Author: lladmin
 */


#include <test.h>
#include <classifiers/trees/Partitioner.h>
#include <classifiers/trees/splits/splitCandidateGenerator/SampleSplitCandidateGenerator.h>
#include <classifiers/trees/splits/qualityMeasurer/simpleSplitQualityMeasurer.h>
#include <classifiers/trees/impurityMeasures/giniImpurityMeasure.h>

namespace ffactory{

	TEST(Partitioner, TwoPointDataset) {
		// Подготовим датасет
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
		ASSERT_TRUE(d.getStatistics()->getGlobalRanges() != NULL);
		ASSERT_TRUE(d.getStatistics()->getGlobalRanges()->isEqual(d.getStatistics()->getRanges()));
		// Сгенерируем сплиты
						SampleSplitCandidateGenerator gen;
							gen.setDataset(&d);
							gen.generate();
		// Подготовим
			SimpleSplitQualityMeasurer Qm;
			BaseImpurityMeasureUniquePtr impM(new GiniImpurityMeasure);
			Qm.setImpurityMeasureFunction( std::move(impM) );

		// Инициализируем Partitioner
		Partitioner p;
		p.setSv(gen.getSplitSet());
		p.setGlobalRanges(*d.getStatistics()->getRanges());
		p.setSamples(d.getSamples());
		p.setQm(&Qm);
		p.setNumClasses(2);
		p.setNumFeatures(2);


		PartitionStatistics ps;
		ps.copyStatistics( *d.getStatistics());

		BinarySplit s;
		s.setFeatureIndex(0);
		s.setFeatureValue(1.5);

		DataType score = p.getSplitScore(&ps, &s);
		EXPECT_EQ( score , 0);
	}

	TEST(Partitioner, ThreePointDataset) {
			// Подготовим датасет
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
							s2.setY(1);

							Sample s3;
							DataVector c(2);
							c <<  1.5, 1.5;
							s3.setVector(c);
							s3.setY(1);

							d.add(s1);
							d.add(s2);
							d.add(s3);

			ASSERT_TRUE(d.getStatistics()->getGlobalRanges() != NULL);
			ASSERT_TRUE(d.getStatistics()->getGlobalRanges()->isEqual(d.getStatistics()->getRanges()));
			// Сгенерируем сплиты
							SampleSplitCandidateGenerator gen;
								gen.setDataset(&d);
								gen.generate();
			// Подготовим
				SimpleSplitQualityMeasurer Qm;
				BaseImpurityMeasureUniquePtr impM(new GiniImpurityMeasure);
				Qm.setImpurityMeasureFunction( std::move(impM) );

			// Инициализируем Partitioner
			Partitioner p;
			p.setSv(gen.getSplitSet());
			p.setGlobalRanges(*d.getStatistics()->getRanges());
			p.setSamples(d.getSamples());
			p.setQm(&Qm);
			p.setNumClasses(2);
			p.setNumFeatures(2);


			PartitionStatistics ps;
			ps.copyStatistics( *d.getStatistics());

			BinarySplit s;
			s.setFeatureIndex(0);
			s.setFeatureValue(1.5);

			DataType score = p.getSplitScore(&ps, &s);
			EXPECT_NE( 0, score );

			s.setFeatureValue(1.4);

			score = p.getSplitScore(&ps, &s);
			EXPECT_EQ(0,  score);

			INFO("findBestSplit");
			score = p.findBestSplit(&ps);
			EXPECT_EQ(0,  score);
			EXPECT_EQ(0,  p.getBestSplitIndex());

		}

	TEST(Partitioner, FourPointDatasetWeighted) {
			// Подготовим датасет
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
								b <<  3, 1;
								s2.setVector(b);
								s2.setY(1);

							Sample s3;
								DataVector c(2);
								c <<  3, 3;
								s3.setVector(c);
								s3.setY(0);
								s3.setW(0.5);

							Sample s4;
								DataVector e(2);
								e <<  3, 5;
								s4.setVector(e);
								s4.setY(0);
								s4.setW(0.4);

							d.add(s1);
							d.add(s2);
							d.add(s3);
							d.add(s4);

							// Сгенерируем сплиты
							SampleSplitCandidateGenerator gen;
								gen.setDataset(&d);
								gen.generate();
							// Подготовим
							SimpleSplitQualityMeasurer Qm;
							BaseImpurityMeasureUniquePtr impM(new GiniImpurityMeasure);
							Qm.setImpurityMeasureFunction( std::move(impM) );

							// Инициализируем Partitioner
							Partitioner p;
								p.setSv(gen.getSplitSet());
								p.setGlobalRanges(*d.getStatistics()->getRanges());
								p.setSamples(d.getSamples());
								p.setQm(&Qm);
								p.setNumClasses(2);
								p.setNumFeatures(2);
							PartitionStatistics ps;
								ps.copyStatistics( *d.getStatistics());
								p.findBestSplit(&ps);
								IndexType i = p.getBestSplitIndex();
								BinarySplit* s = gen.getSplit(i);
								EXPECT_EQ(  0,  s->getFeatureIndex());
								EXPECT_NEAR(1,  s->getFeatureValue(), 0.0001);


								d.getSample(3)->setW(1);
								d.computeStatistics();
								ps.copyStatistics( *d.getStatistics());
								p.findBestSplit(&ps);
								i = p.getBestSplitIndex();
								s = gen.getSplit(i);
								EXPECT_EQ(  1,  s->getFeatureIndex());
								EXPECT_NEAR(1,  s->getFeatureValue(), 0.0001);


	}


}




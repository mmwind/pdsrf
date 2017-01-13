/*
 * dataset_gen.cpp
 *
 *  Created on: 22 янв. 2016 г.
 *      Author: lladmin
 */
#include "../testing/dataset_gen.h"

#include <init.h>
#include <data/fileFormats/CsvFileReader.h>
#include <data/fileFormats/BinaryEigenFileReader.h>

namespace ffactory{
	/**
	 * Simple iris dataset loader
	 * @param d
	 */
	void loadIrisDataset(Dataset& d){
				CsvFileReader r;
				r.setDataset(&d);
				r.setFilename("test.csv");
				r.setDelimiter(';');
				r.read();
	}

	void loadCovTypeDatasetCSV(Dataset& d){
		CsvFileReader r;
		r.setDataset(&d);
		r.setFilename("covtype.csv");
		r.setDelimiter(';');
		r.read();
		FINFO("DATASET LOADED. PROCESSING...");
		for(IndexType i=0; i< d.getNumSamples(); i++){
			Sample *s = d.getSample(i);
			s->setY( s->getY() -1 );
		}
		d.setNumClasses(7);
		d.remove(d.getNumSamples());
		FINFO("DATASET PROCESSED.");
	}

	void loadCovTypeDataset(Dataset& d){
		BinaryEigenFileReader r;
		r.setDataset(&d);
		r.setFilename("covtype.bin");
		r.read();
	}


	/**
	 * Trivial 2 points dataset (two points on one line)
	 * @param d
	 */
	void loadTrivialTwoPointsDataset(Dataset &d){
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
					b <<  1, 2;
					s2.setVector(b);
					s1.setY(1);
				d.add(s1);
				d.add(s2);
	}

	/**
	 * Trivial 3 points dataset with categorial attribute (two points on one line)/
	 * First attribute is CONTINUOUS, second is CATEGORIAL
	 * @param d
	 */
	void loadTrivialCategorialThreePointsDataset(Dataset &d){
		d.setNumClasses(3);
		d.addAttribute("V1",ATTR_CONTINUOUS, NULL);
		StringVector sv;
		sv.push_back("0");sv.push_back("1");sv.push_back("2");
		d.addAttribute("V2",ATTR_CATEGORIAL, &sv);
		d.initStatistics();

		DataVector e(2);
		Sample s1;
		e <<  1, 0;
		s1.setVector(e);
		s1.setY(1);

		Sample s2;
		e <<  1, 1;
		s2.setVector(e);
		s2.setY(0);

		Sample s3;
		e <<  1, 2;
		s3.setVector(e);
		s3.setY(0);

		d.add(s1);
		d.add(s2);
		d.add(s3);
	}

	/**
	 * Simple 2 points dataset
	 * @param d
	 */
	void loadTwoPointsDataset(Dataset &d){
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
	}

	/**
	 * Simple 3 points dataset
	 * @param d
	 */
	void loadThreePointsDataset(Dataset &d){
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
	}


	/**
	 * Simple 4 points dataset (variant I)
	 * @param d
	 */
	void loadFourPointsWeihtedDataset1(Dataset &d){
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
	}


	/**
	 * Simple 4 points dataset (variant II)
	 * @param d
	 */
	void loadFourPointsWeihtedDataset2(Dataset &d){
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
			s3.setW(1);

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
	}

	/**
	 * Simple 5 points dataset with categorial and continuous variables
	 * @param d
	 */
	void loadFivePointsCategorialDataset(Dataset &d){
		d.setNumClasses(2);
		d.addAttribute("V1",ATTR_CONTINUOUS, NULL);
		StringVector sv;
		sv.push_back("0");sv.push_back("1");
		d.addAttribute("V2",ATTR_CATEGORIAL, &sv);
		d.initStatistics();

		DataVector e(2);
		Sample s1;
		e <<  1, 0;
		s1.setVector(e);
		s1.setY(1);

		Sample s2;
		e <<  2, 0;
		s2.setVector(e);
		s2.setY(0);

		Sample s3;
		e <<  3, 0;
		s3.setVector(e);
		s3.setY(0);

		Sample s4;
		e <<  2, 1;
		s4.setVector(e);
		s4.setY(1);

		Sample s5;
		e <<  3, 1;
		s5.setVector(e);
		s5.setY(1);

		d.add(s1);
		d.add(s2);
		d.add(s3);
		d.add(s4);
		d.add(s5);
	}

}

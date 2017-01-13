/*
 * sample.h
 *
 *  Created on: 16 ���. 2015 �.
 *      Author: llproger
 */

#ifndef DATA_SAMPLE_H_
#define DATA_SAMPLE_H_

#include <iostream>
#include <init.h>
#include <data/data.h>

namespace ffactory {


/**
 * Sample class supports various types of data containers including Eigen library types for storing data samples.
 */
class Sample {
private:
	/**
	 * Feature vector
	 */
		DataVector x;

	/**
	 * Label
	 */
		IndexType y;

	/**
	 * Sample weight (reserved)
	 */
	    double w;

	/**
	 * Sample Identifier (reserved)
	 */
	    IndexType id;
public:

	/**
	 * Stream output
	 * @param stream
	 * @param matrix
	 * @return
	 */
	friend std::ostream& operator<< (std::ostream& stream, Sample& s) {
		 DataVector v = *s.getVector();
		  VEC_TO_STREAM(v.transpose(), stream);
		  return (stream);
	}


	Sample(unsigned int size = 0):
		y(0),
		w(1.0),
		id(0)
	{
		x = ZERO_VECTOR(size);
	}

	virtual ~Sample(){
	}

	int getId() const {
		return id;
	}

	void setId(int id) {
		this->id = id;
	}

	double getW() const {
		return w;
	}

	void setW(double w) {
		this->w = w;
	}

	IndexType getY() {
		return y;
	}

	void setY(IndexType y) {
		this->y = y;
	}

	DataVector* getVector() {
		return &x;
	}

	IndexType size(){
		return( VECTOR_SIZE(x) );
	}

	IndexType getNumFeatures(){
		return( VECTOR_SIZE(x) );
	}

	DataType getValue(IndexType i) {
		if( i >= size() ) THROW(std::string("Try to get an element that is out of bound: index >= ") + std::to_string( size() ));
		return x(i);
	}

	void setVector(DataVector& newx) {
		x = newx;
	}


	void setValue(unsigned int i, DataType v) {
		if( i >= size() ) THROW(std::string("Try to set an element that is out of bound: index >= ") + std::to_string( size() ));
		(x)(i) = v;
	}

	/**
	 * Fulls all elements of sample data vector with specified value
	 * @param v
	 */
	void fullWith(DataType v){
		for(IndexType i=0; i< size(); ++i)
			setValue(i, v);
	}

	/**
	 * Changes size of vector. Please note than all data content will be forgotten!
	 * @param size
	 */
	void resize(unsigned int size){
		if(size != 0){
			x.resize(size);
		}
	}

	/**
	 * Fulls all elements of sample data vector with uniformly distributed pseudo-random values with specified seed and ranges
	 * @param minv
	 * @param maxv
	 * @param seed
	 */
	void fullRandom(DataType& minv, DataType& maxv, unsigned int seed){
		srand(seed);
		for(IndexType i=0; i< size(); ++i)
			setValue(i, minv + (maxv - minv) * std::rand() / RAND_MAX );
	}
};

DEFINE_PTR(Sample)

} /* namespace tf */

#endif /* DATA_SAMPLE_H_ */

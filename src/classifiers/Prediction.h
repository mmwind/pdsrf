/*
 * prediction.h
 *
 *  Created on: 17 ���. 2015 �.
 *      Author: llproger
 */

#ifndef CLASSIFIERS_PREDICTION_H_
#define CLASSIFIERS_PREDICTION_H_

#include <data/Dataset.h>
#include <data/Sample.h>
#include <algorithm>    // std::min_element, std::max_element


namespace ffactory {

/**
 * Class represents result of prediction such as class probabilities. Obtaining of Confusion matrix, final class can be performed.
 */
class Prediction {
public:
	Prediction(){}

	virtual ~Prediction(){

	}

	/**
	 * Stream output operator << for Prediction class
	 */
	friend std::ostream& operator<< (std::ostream& stream, const Prediction& s){
			stream << "Prediction summary for " << "'" << s.getClassifierName() << "'"<< std::endl;
			stream << "Features: " << s.getNumFeatures() << std::endl;

		  return (stream);
	}

	const DataMatrix& getConfidences() const
	{
		return confidences;
	}

	unsigned int getNumFeatures() const
	{
		return numFeatures;
	}

	void setNumFeatures(unsigned int numFeatures)
	{
		this->numFeatures = numFeatures;
	}

	DataVector& getPrediction()
	{
		return predictedValues;
	}

	/**
	 * Get classes probability vector for sample with index \a i
	 */
	DataVector getConfidence(unsigned int sampleIndex){
		check();
		return( MATRIX_COL(confidences, sampleIndex) );
	}

	const std::string& getClassifierName() const
	{
		return classifierName;
	}

	void setClassifierName(const std::string& classifierName)
	{
		this->classifierName = classifierName;
	}

	void setConfidences(const DataMatrix& confidences)
	{
		this->confidences = confidences;
	}

	unsigned int computeSamplePrediction(){
		check();
		return(computePrediction(0));
	}

	unsigned int computePrediction(unsigned int sampleIndex){
		check();
		unsigned int ClassIndex;
		MAX_VECTOR_INDEX( getConfidence(sampleIndex), ClassIndex);
		return( ClassIndex );
	}

	/**
	 * Computation of prediction error for sample with index \a sampleIndex
	 * @param sampleIndex
	 * @param actualClass
	 * @return
	 */
	unsigned int computePredictionError(unsigned int sampleIndex, unsigned int actualClass){
		check();
		return( 1 - getConfidence(sampleIndex)(actualClass) );
	}
/**
 * Set classes probability vector \v for sample with index \a i
 * @param i
 * @param v
 */
	void setConfidence(unsigned int i, DataVector& v){
		check();
		MATRIX_COL(confidences,i) = v;
	}


	void setDiscretePredictionConfidence(IndexType sampleIdx, IndexType  classLabel){
		DataVector v = ZERO_VECTOR(numClasses);

		if(classLabel > numClasses) THROW("classLabel > numClasses");

		v(classLabel) = 1;
		setConfidence(sampleIdx,v);
	}

	unsigned int getNumClasses() const
	{

		return numClasses;
	}

	void setNumClasses(unsigned int numClasses)
	{

		this->numClasses = numClasses;
	}


	void setPredictedClass(IndexType sampleIdx, IndexType  classLabel){
		predictedValues(sampleIdx) = classLabel;
		MATRIX_COL(confidences,sampleIdx)(classLabel) = 1;
	}

	unsigned int getNumSamples()
	{
		if(VECTOR_SIZE(predictedValues) != numSamples) THROW (" VECTOR_SIZE(predictedValues) != numSamples ");
		return VECTOR_SIZE(predictedValues);
	}

	void setNumSamples(unsigned int numSamples)
	{
		this->numSamples = numSamples;
		if(VECTOR_SIZE(predictedValues) != numSamples){
			//RESIZE_VECTOR(predictedValues, numSamples);
			predictedValues = ZERO_VECTOR(numSamples);
		}

		if(MATRIX_COLS(confidences) != numSamples){
			//RESIZE_MATRIX(confidences, numClasses, numSamples);
			confidences = ZERO_MATRIX(numClasses, numSamples);
		}
	}

	void check(){
		if(numFeatures == 0) THROW("numFeatures = 0");
		if(numClasses < 2)   THROW("numClasses < 2");
		if(VECTOR_SIZE(predictedValues) != numSamples) THROW("VECTOR_SIZE(predictedValues) != numSamples");
		if(MATRIX_COLS(confidences) != numSamples)     THROW("MATRIX_COLS(confidences) != numSamples");
	}

private:
	std::string classifierName;
	unsigned int numFeatures;
	unsigned int numClasses;
	unsigned int numSamples;
	DataMatrix confidences;
    DataVector predictedValues;

};


} /* namespace ffactory */

#endif /* CLASSIFIERS_PREDICTION_H_ */

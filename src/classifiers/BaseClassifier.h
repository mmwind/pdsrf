/*
 * baseClassifier.h
 *
 *  Created on: 16 ���. 2015 �.
 *      Author: llproger
 */

#ifndef CLASSIFIERS_BASECLASSIFIER_H_
#define CLASSIFIERS_BASECLASSIFIER_H_

#include <memory>
#include <init.h>
#include <classifiers/Prediction.h>
#include <data/Dataset.h>
#include <data/Sample.h>
#include <classifiers/errorMeasures/baseErrorMeasure.h>

namespace ffactory {


/**
 * Class with essential functions for all classification problems
 */
class BaseClassifier: public Base {
public:
	BaseClassifier(){
		numClasses = 0;
		verbose = true;
		numFeatures = 0;
		setName("Base Classifier interface");
	}

	virtual ~BaseClassifier(){ };

	/**
	 * Train classifier on dataset \a d
	 * @param d
	 * @return Value of specified error measure on dataset \a d
	 */
	virtual double train(Dataset *d) = 0;

	/**
	 * Predict class probability of one sample
	 * @param sample
	 * @return Index of class
	 */
	virtual DataVectorUniquePtr predictClassProb(Sample * sample) = 0;

	/**
	 * Predict class of one sample
	 * @param sample
	 * @return  Prediction object
	 */
	virtual Prediction predict(Sample* sample){
		DataVectorUniquePtr classProbPtr = std::move(predictClassProb(sample));
		Prediction p;
		p.setNumFeatures(this->getNumFeatures());
		p.setNumClasses(this->getNumClasses());
		p.setNumSamples(1);
		IndexType classLabel;

		classProbPtr.get()->maxCoeff(&classLabel); /** \todo Use MACRO instead of this */

		p.setPredictedClass(0,classLabel);
		return(p);
	}

	/**
	 * Predict class for dataset
	 * @param d
	 * @return Prediction object
	 */
	virtual Prediction predict(Dataset& d){
		Prediction p;
		p.setNumFeatures(this->getNumFeatures());
		p.setNumClasses(this->getNumClasses());
		p.setNumSamples(d.getNumSamples());
		DataVector AvgClassProb = ZERO_VECTOR( this->getNumClasses() );
		for(IndexType i=0; i< d.getNumSamples(); i++){
			Sample* s = d.getSample(i);
			DataVectorUniquePtr classProbPtr = predictClassProb(s);
			DataVector classProb = *(classProbPtr.get());
			p.setConfidence(i, classProb);
			IndexType classLabel;
			MAX_VECTOR_INDEX(classProb,classLabel);
			p.setPredictedClass(0,classLabel);
		}
		return(p);
	}

	/**
	 * Test trained classifier on dataset \a d
	 * @param d
	 * @return specified error measure value for \a d
	 */
	virtual double test(Dataset* d){
		check();
		double error = getErrorMeasure()->getError(this,d);
		double accuracy = 1 - error;
		return(accuracy);
	}

	/**
	 * Generates information string
	 * @return std::string contains information about object
	 */
	virtual std::string getInfo(){
		std::stringstream stream;
		if(this->getTrainDataset() != NULL){
			 stream << "Train Dataset\n"  << (*this->getTrainDataset());
		}
		stream <<  this->getName() << " classifier" << std::endl;
		return(stream.str());
	}

	IndexType getNumClasses() const {
		return numClasses;
	}

	void setNumClasses(IndexType numClasses) {
		this->numClasses = numClasses;
	}

	IndexType getNumFeatures() const {
		return numFeatures;
	}

	void setNumFeatures(IndexType numFeatures) {
		this->numFeatures = numFeatures;
	}

	IndexType getNumTrainSamples() const {
		return numTrainSamples;
	}

	void setNumTrainSamples(IndexType numTrainSamples) {
		this->numTrainSamples = numTrainSamples;
	}

	bool isVerbose() const {
		return verbose;
	}

	void setVerbose(bool verbose) {
		this->verbose = verbose;
	}

	Dataset* getTrainDataset() {
		return trainDataset;
	}

	void setTrainDataset(Dataset* trainDataset) {
		this->trainDataset = trainDataset;
		numClasses = trainDataset->getNumClasses();
		numTrainSamples = trainDataset->getNumSamples();
		numFeatures = trainDataset->getNumFeatures();
	}

	IndexVector& getTrainIndices() {
		return trainIndices;
	}

	void setTrainIndices(IndexVector& trainIndices) {
		this->trainIndices = trainIndices;
	}

	BaseErrorMeasure* getErrorMeasure() {
		return errorMeasure.get();
	}

	void setErrorMeasure(BaseErrorMeasureUniquePtr errorMeasure) {
		this->errorMeasure = std::move(errorMeasure);
	}

	void check(){
		if(getErrorMeasure() == NULL) THROW("ErrorMeasure is not set!");
	}

private:

	Dataset *trainDataset;
	IndexVector trainIndices;/** \todo trainIndices? */
    int numClasses;
    int numTrainSamples;
    int numFeatures;
    bool verbose;
    BaseErrorMeasureUniquePtr errorMeasure; /** BaseErrorMeasure */
};

DEFINE_PTR(BaseClassifier)

} /* namespace ffactory */

#endif /* CLASSIFIERS_BASECLASSIFIER_H_ */

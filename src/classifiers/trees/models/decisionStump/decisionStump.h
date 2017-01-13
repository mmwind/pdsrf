/*
 * decisionStump.h
 *
 *  Created on: 18 ���. 2015 �.
 *      Author: llproger
 */

#ifndef CLASSIFIERS_DECISIONSTUMP_H_
#define CLASSIFIERS_DECISIONSTUMP_H_

#include <classifiers/baseClassifier.h>
#include <classifiers/trees/splits/binarySplit.h>
#include <classifiers/trees/baseTreeClassifier.h>

namespace ffactory {

/*
 *
 */
class DecisionStump: public BaseTreeClassifier {
public:
	DecisionStump();
	virtual ~DecisionStump();
	/**
	 * Train classifier on dataset \a d
	 * @param d
	 * @return FIXME: splitScore for now. Must be value of specified error measure on dataset \a d
	 */
	virtual double train(Dataset d);

	/**
	 * Predict class of one sample
	 * @param sample
	 * @return Prediction
	 */
	virtual Prediction predict(Sample& sample);


	friend std::ostream& operator<< (std::ostream& stream, DecisionStump& s){
		 stream << "Classifier: " << s.getName() << std::endl;
		 stream << "Features: " << s.getNumFeatures() << std::endl;
		 stream << "Classes: " << s.getNumClasses() << std::endl;
		 stream << "Samples: " << s.getNumTrainSamples() << std::endl;
		 if(s.impurityFunction == NULL){
			 stream << "Impurity function: NA " << std::endl;
		 } else {
			 stream << "Impurity function: " << s.impurityFunction->getName() << std::endl;
		 }
		 return (stream);
	}

	/**
	 * Generates information string
	 * @return std::string contains information about classifier
	 */
	virtual std::string getInfo(){
		std::string s;
		 if(impurityFunction == NULL){
			 s = "Impurity function: NA \n";
		 } else {
			 s = "Impurity function: " + impurityFunction->getName() + "\n";
		 }
		return(s);
	}
private:
	BinarySplit split;
	DataType splitScore;
	//BaseImpurityMeasure* impurityFunction;
};

} /* namespace ffactory */

#endif /* CLASSIFIERS_DECISIONSTUMP_H_ */

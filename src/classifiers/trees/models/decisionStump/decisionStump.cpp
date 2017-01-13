/*
 * decisionStump.cpp
 *
 *  Created on: 18 окт. 2015 г.
 *      Author: llproger
 */

#include "decisionStump.h"


namespace ffactory {

DecisionStump::DecisionStump() {

	//SampleSplitCandidateGenerator();

	setName("Simple Decision Stump");
	setNumClasses(2);
}

DecisionStump::~DecisionStump() {
	// TODO Auto-generated destructor stub
}

 double DecisionStump::train(Dataset d){

	 // Initialize model with dataset parameters
	setNumTrainSamples(d.getNumSamples());
	setNumFeatures(d.getNumFeatures());

	// Check model limitations
	if(d.getNumClasses()!=2){
		std::cout << "[ERROR] " << getName()<< " supports only " << getNumClasses() << " classes." << std::endl;
		exit(EXIT_FAILURE);
	}

	splitScore = 1E+16; // FIXME: What is correct splitScore at initialization?

	BaseSplitCandidateGenerator* gen = this->getSplitGenerator();
	gen->setDataset(&d);
	gen->generate();
	for(unsigned int i = 0; i< gen->getSplitNum(); i++){
		BinarySplit* newSplit = gen->getSplit(i);
		newSplit->setImpurityMeasureFunction(this->getImpurityFunction());
		DataType score = newSplit->getImpurityScore(d);
		if(score < splitScore){
						splitScore = score;
						split = *newSplit;
		}
		INFO( "Feature " << newSplit->getFeatureIndex()  <<" at "<< newSplit->getFeatureValue() << " imp: " << score );
	}
	/*
	for(unsigned int i = 0; i< d.getNumSamples(); i++){
		BinarySplit newSplit;
		newSplit.setImpurityMeasureFunction(impurityFunction);
		for(unsigned int f = 0; f< d.getNumFeatures(); f++){
			newSplit.setFeatureIndex(f);
			newSplit.setFeatureValue(d.getSample(i).getValue(f));

			DataType score = newSplit.getImpurityScore(d);

			if(score < splitScore){
				splitScore = score;
				split = newSplit;
			}

			std::cout << d.getSample(i).getVector().transpose() << " feature " << f << " imp: ";
			std::cout << score << std::endl;
		}
		}*/

		   INFO("Best split found in feature " << split.getFeatureIndex() << " at value " << split.getFeatureValue() << " with impurity "<< splitScore);

	return(splitScore);
}

 Prediction DecisionStump::predict(Sample& sample){
	Prediction p;
	p.setClassifierName(getName());
	p.setNumFeatures(getNumFeatures());
	DataVector conf = ZERO_VECTOR(getNumFeatures());

	if( split.decide(sample.getVector()) ){
		conf(0) = 1;
	} else {
		conf(1) = 1;
	}
	p.setConfidences(conf);
	return(p);
}

} /* namespace ffactory */

/*
 * SampleSplitCandidateGenerator.h
 *
 *  Created on: 21 окт. 2015 г.
 *      Author: llproger
 */

#ifndef CLASSIFIERS_SPLITS_SAMPLESPLITCANDIDATEGENERATOR_H_
#define CLASSIFIERS_SPLITS_SAMPLESPLITCANDIDATEGENERATOR_H_

#include <classifiers/trees/splits/splitCandidateGenerator/BaseSplitCandidateGenerator.h>
#include <init.h>
#include <limits>

namespace ffactory {

/**
 * Generates splits in sample points for selected features
 */
class SampleSplitCandidateGenerator: public BaseSplitCandidateGenerator {
public:
	SampleSplitCandidateGenerator(){
		this->setName("SampleSplits");
	}

	void addNewSplit(Sample * s, IndexType f){
		BinarySplit newSplit;
		IndexType idx = featureMask[f];
		newSplit.setFeatureIndex(idx); // 0.01);

		newSplit.setFeatureValue(s->getValue(idx) + std::numeric_limits<DataType>::epsilon());
		addSplit(newSplit);
		//INFO(s->getVector()->transpose() << " feature " << idx );
	}

	/**
	 * Produce split-candidates at sample values
	 * @return Vector of generated splits
	 */
	virtual void generate(DataRanges * ranges = NULL) {

		// if all the features used to produce split-candidates
		if(isUseAllFeatures()){
			featureMask.clear();
			for(IndexType i=0;i< dataset->getNumFeatures(); i++)
				featureMask.push_back(i);
		}

		if(ranges != NULL){
			for(unsigned int i = 0; i< dataset->getNumSamples(); i++){
				for(unsigned int f = 0; f< featureMask.size(); f++){
					if(ranges->isInFeatureRanges(dataset->getSample(i)->getVector(),f)){
						addNewSplit(dataset->getSample(i),f);
					}
				}
			}
		} else {
			for(unsigned int i = 0; i< dataset->getNumSamples(); i++){
				for(unsigned int f = 0; f< featureMask.size(); f++){
						addNewSplit(dataset->getSample(i),f);
				}
			}
		}
	}

};

} /* namespace ffactory */

#endif /* CLASSIFIERS_SPLITS_SAMPLESPLITCANDIDATEGENERATOR_H_ */

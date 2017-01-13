/*
 * baseSplitCandidateGenerator.h
 *
 *  Created on: 21 окт. 2015 г.
 *      Author: llproger
 */

#ifndef CLASSIFIERS_BASESPLITCANDIDATEGENERATOR_H_
#define CLASSIFIERS_BASESPLITCANDIDATEGENERATOR_H_

#include <init.h> // Base
#include <data/data.h>
#include <data/DataRanges.h>
#include <classifiers/trees/splits/binarySplit.h>
#include <data/Dataset.h>
/** \todo Abstract split class must be used for unified interface baseSplit. Only binary splits ( binarySplit class ) are used for now. */

namespace ffactory {


/**
 * Base class for split candidate generators.
 * The class spawns splits which will be examined and the best split will be found.
 */
class BaseSplitCandidateGenerator: public Base {
public:
		BaseSplitCandidateGenerator():
			useAllFeatures(true)
		{
		}
	/**
	 * Produce split-candidates using MaskVector
	 * if \a ranges == 0 then dataset ranges will be used
	 * @param ranges
	 */
	virtual void generate(DataRanges * ranges = NULL) = 0;

	Dataset* getDataset() const {
		return dataset;
	}

	void setDataset(Dataset* dataset) {
		this->dataset = dataset;
		if(dataset != NULL)
			setNumFeatures(dataset->getNumFeatures());
		else
			WARN("Null dataset assigned!");
	}

	const IndexVector& getFeatureMask() const {
		return featureMask;
	}

	void setFeatureMask(IndexVector& featureMask) {
		this->featureMask = featureMask;
	}

	bool isUseAllFeatures() const {
		return useAllFeatures;
	}

	void setUseAllFeatures(bool useAllFeatures) {
		this->useAllFeatures = useAllFeatures;
	}

	std::vector<BinarySplit>* getSplitSet(){
		return &splitSet;
	}

	BinarySplit* getSplit(IndexType s){
		return (&splitSet[s]);
	}

	IndexType getSplitNum(){
		return (splitSet.size());
	}

	void addSplit(BinarySplit &split){
		splitSet.push_back(split);
	}

	void checkData(){
		if(dataset == NULL){
			THROW("Dataset is null. It must be set.");
		}

		if(dataset->getNumSamples() == 0){
			THROW("Dataset is empty.");
		}

		numFeatures = dataset->getNumFeatures();
		if(numFeatures == 0){
			THROW("Dataset features number is 0.");
		}

		splitSet.clear();
	}

	unsigned int getNumFeatures()
	{
		return numFeatures;
	}

	void setNumFeatures(unsigned int _numFeatures)
	{
		this->numFeatures = _numFeatures;
	}

	std::string getInfo(){
		std::stringstream ss;
		ss << "Split Candidate Generator";
		return(ss.str());
	}

	/**
	 * Delete all the splits form buffer
	 */
	void clear(){
		splitSet.clear();
	}
protected:
    Dataset *dataset; /** Dataset which is used to get splits. Feature information is obtained from here. */

    bool useAllFeatures; /** \todo implement this, if set, all the features will be used to generate splits */
    IndexVector featureMask; /** \todo implement this, if useAllFeatures==false, all the features will be used to generate splits */
    IndexType numFeatures;

    SplitVector splitSet;

};

DEFINE_PTR(BaseSplitCandidateGenerator)

} /* namespace ffactory */

#endif /* CLASSIFIERS_BASESPLITCANDIDATEGENERATOR_H_ */

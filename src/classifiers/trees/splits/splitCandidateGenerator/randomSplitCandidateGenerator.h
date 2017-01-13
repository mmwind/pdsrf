/*
 * randomSplitCandidateGenerator.h
 *
 *  Created on: 21 окт. 2015 г.
 *      Author: llproger
 */

#ifndef CLASSIFIERS_RANDOMSPLITCANDIDATEGENERATOR_H_
#define CLASSIFIERS_RANDOMSPLITCANDIDATEGENERATOR_H_

#include <classifiers/trees/splits/splitCandidateGenerator/BaseSplitCandidateGenerator.h>
#include <utils/Random.h>

namespace ffactory {

/**
 * Class generates random splits
 */
class RandomSplitCandidateGenerator: public BaseSplitCandidateGenerator {
public:
	RandomSplitCandidateGenerator(){
		std::stringstream ss;
		ss << "RandomSplit";
		this->setName(ss.str());
		setUseAllFeatures(true);
	}

	RandomSplitCandidateGenerator(IndexType splitNum, IndexType featNum):
		splitNumber(splitNum){
		setNumFeatures(featNum);
		setUseAllFeatures(true);
		randomSeed = 13; /** \bug */
		std::stringstream ss;
		ss << "RandomSplit(splitNum = " << splitNum << ")";
		this->setName(ss.str());

	}

	/**
	 * Produce split-candidates
	 * @return Vector of generated splits
	 */
	virtual void generate(DataRanges * ranges = NULL) {
		checkData();
		//initRandomEngine();
		// if all the features used to produce split-candidates
		if(isUseAllFeatures()){
			featureMask.clear();
			for(IndexType i=0;i< dataset->getNumFeatures(); i++)
				featureMask.push_back(i);
		}

		DataRanges * r;
		if(ranges == NULL){
			r = dataset->getStatistics()->getRanges();
		} else {
			r = ranges;
		}

		auto genFeatureMask = getUniformIntGenerator(0, featureMask.size() - 1);

		//INFO("Splitting by ");
		std::vector< std::function<double()> > generators;
		for(IndexType i = 0; i<featureMask.size(); i++){
			IndexType featureIndex = featureMask[ i ];
			Attribute *a = getDataset()->getAttribute( featureIndex );
			if(a->getType() == ATTR_CATEGORIAL ){
				generators.push_back( getUniformIntGenerator(0, a->getNumCategories() - 1) );
			} else {
				double minv = r->minValues(featureIndex);
				double maxv = r->maxValues(featureIndex);
				//INFO(" f " << featureIndex << " | min = " << minv << " , max = "<< maxv);
				generators.push_back( getNormalRealGenerator(minv + (maxv - minv)/2,  (maxv - minv)/6) );
			}
		}

		for(IndexType s = 0; s < splitNumber; s++){
			BinarySplit newsplit;

			 IndexType randomFeature = genFeatureMask();
			 IndexType idx = featureMask[ randomFeature ];

			 newsplit.setFeatureIndex( idx );
			 double minv = r->minValues(idx);
			 double maxv = r->maxValues(idx);
			 if( minv == maxv) continue;

			 double val = 0;
			 Attribute *a = getDataset()->getAttribute(idx);
			 if(a->getType() == ATTR_CATEGORIAL ){
				 val = generators[randomFeature]();
			 } else {

					do{
					  val = generators[randomFeature]();
					} while(val < minv || val > maxv);

				 //val = generators[idx]();
				 if(a->getType() == ATTR_INTEGER){
					 val = trunc(val);
				 }
			 }
			 newsplit.setFeatureValue( val );
			 this->addSplit(newsplit);
			 //INFO(" f = " << newsplit.getFeatureIndex() << " | v = " << newsplit.getFeatureValue() << " , "<< a->getTypeName());
		}

	}

	unsigned int getSplitNumber() const {
		return splitNumber;
	}

	void setSplitNumber(unsigned int splitNumber) {
		this->splitNumber = splitNumber;
	}

	unsigned int getRandomSeed()
	{
		return randomSeed;
	}

	void setRandomSeed(unsigned int randomSeed)
	{
		this->randomSeed = randomSeed;
	}

	std::string getInfo(){
		std::stringstream ss;
		ss << BaseSplitCandidateGenerator::getInfo() << ": Random Splits(number=" << splitNumber << ")";
		return(ss.str());
	}
private:
	IndexType splitNumber; /** number of random splits to produce */
	IndexType randomSeed;

};

} /* namespace ffactory */

#endif /* CLASSIFIERS_RANDOMSPLITCANDIDATEGENERATOR_H_ */

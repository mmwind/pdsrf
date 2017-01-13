/*
 * randomFeaturesSplitCandidateGenerator.h
 *
 *  Created on: 6 нояб. 2015 г.
 *      Author: llproger
 */

#ifndef CLASSIFIERS_TREES_SPLITS_SPLITCANDIDATEGENERATOR_RANDOMFEATURESSPLITCANDIDATEGENERATOR_H_
#define CLASSIFIERS_TREES_SPLITS_SPLITCANDIDATEGENERATOR_RANDOMFEATURESSPLITCANDIDATEGENERATOR_H_

#include <classifiers/trees/splits/splitCandidateGenerator/BaseSplitCandidateGenerator.h>
#include <utils/Random.h>

namespace ffactory {

/**
 * Base Class template for random subset of features.
 * T must have BaseSplitCandidateGenerator class.
 * It uses idea of Random Subspace Method proposed by Tin Kam Ho in \cite ho1998random
 */
template <typename T>
class RandomFeaturesSplitCandidateGenerator: public T {
private:
	IndexType mtry;
	IndexType randomSeed;
public:
		/**
		 * Get base
		 * @return
		 */
		T getGenerator(){
			return( static_cast<T>(*this) );
		}

		/**
		 * Produce random feature subset split-candidates for class T on each generation
		 * @return Vector of generated splits
		 */
		virtual void generate(DataRanges * ranges = NULL) {
			this->checkData();
			if(mtry > this->getNumFeatures()) THROW("TYPE");


			IndexVectorUniquePtr maskvec (std::move(getRandomIndexVector<IndexType>(mtry, 0, this->getNumFeatures() - 1, false)));

			/*
			IndexVector mask;

			for(IndexType i = 0; i < this->getNumFeatures(); i++){
				mask.push_back(i);
			}

			auto gen = getUniformIntGenerator(0, mask.size() - 1);

			for(IndexType i = 0; i < this->getNumFeatures() - mtry; i++){
				IndexType idx = gen();
				mask.erase(mask.begin() + idx);
			}*/
/*
			std::cout << "Feature subset [ ";
			for(IndexType i = 0; i < mask.size(); i++) std::cout << mask[i] << " ";
			std::cout << "]" << std::endl;
*/
			//this->setFeatureMask(mask);
			this->setFeatureMask(*maskvec);
			this->setUseAllFeatures(false);

			T::generate(ranges);
		}

	unsigned int getMtry()
	{
		return mtry;
	}

	void setMtry(unsigned int mtry)
	{
		this->mtry = mtry;
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
		ss << T::getInfo() << " for random feature subsets (mtry=" << mtry <<")";
		return(ss.str());
	}
};

} /* namespace ffactory */

#endif /* CLASSIFIERS_TREES_SPLITS_SPLITCANDIDATEGENERATOR_RANDOMFEATURESSPLITCANDIDATEGENERATOR_H_ */

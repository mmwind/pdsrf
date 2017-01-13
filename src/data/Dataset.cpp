/*
 * Dataset.cpp
 *
 *  Created on: 28 февр. 2016 г.
 *      Author: lladmin
 */

#include <data/Dataset.h>

namespace ffactory {


	Dataset::Dataset():
			numClasses(0)
		//	,numFeatures(0)
		{

			//classSamplesNumber = ZERO_VECTOR(2);
		}

	Dataset::~Dataset(){

	}

	/**
	 * Set target attribute for dataset
	 * @param name
	 * @param type
	 * @param cat (optional) vector of categories
	 */
	void Dataset::setTargetAttribute(std::string name,
			AttributeType type,
			StringVector *cat){
		targetAattribute.setName(name);
		targetAattribute.setType(type);
		targetAattribute.setCategories(cat);
	}

	/**
	 * Add new attribute to dataset
	 * @param name
	 * @param type
	 * @param cat (optional) vector of categories
	 */
	void Dataset::addAttribute(	std::string name,
						AttributeType type,
						StringVector *cat)
	{
		Attribute a;
		a.setName(name);
		a.setType(type);
		a.setCategories(cat);
		attributes.push_back(a);
	//	numFeatures++;
	}

	Attribute* Dataset::getAttribute(IndexType index){
		return( &attributes[index]);
	}

	/**
	 * Get attribute's Index By Name
	 * @param name
	 * @return attribute index if it was found or  NumFeatures if not
	 */
	IndexType Dataset::getAttributeIndexByName(std::string name){
		for(IndexType i = 0; i< getNumFeatures(); i++){
			if( attributes[i].getName() == name ){
				return(i);
			}
		}
		return(getNumFeatures());
	}

	Attribute* Dataset::getAttributeByName(std::string name){
		IndexType i = getAttributeIndexByName(name);
		if(i == getNumFeatures())
			return( NULL );
		else
			return( getAttribute(i) );
	}

	PartitionStatistics* Dataset::getStatistics(){
		return(statistics.get());
	}

	unsigned int Dataset::getNumClasses() {
		return numClasses;
	}

	void Dataset::initStatistics(){
		if(getNumFeatures() > 0 && numClasses > 1){
			if(statistics != nullptr) statistics.reset();
			statistics = std::move(
				PartitionStatisticsUniquePtr(new PartitionStatistics(numClasses, getNumFeatures()))
			);
		}
	}

	void Dataset::computeStatistics(){
		if(getNumFeatures() > 0 && numClasses > 1){
			if(statistics != nullptr) statistics.reset();
			statistics = std::move(
				PartitionStatisticsUniquePtr(new PartitionStatistics(numClasses, getNumFeatures(),this->getSamples()))
			);
		}
	}

	void Dataset::setNumClasses(unsigned int numClasses) {
		this->numClasses = numClasses;
	}

	unsigned int Dataset::getNumFeatures() {
		return this->attributes.size();

	}

	void Dataset::setNumFeatures(unsigned int numFeatures) {
		this->attributes.resize(numFeatures);
	}

	unsigned int Dataset::getNumSamples() {
		return samples.size();
	}

	std::vector<Sample>* Dataset::getSamples() {
		return &samples;
	}

	/**
	 * Set samples vector with computing of ranges and class samples numbers
	 * @param samples
	 */
	void Dataset::setSamples(std::vector<Sample>* samples) {
		this->samples = *samples;
		calculateRanges();
		//computeClassSamplesNumber();
	}

	/**
	 * Calculate ranges of dataset features
	 */
	DataRanges Dataset::calculateRangesMasked(MaskVector * sampleMask) {
	    DataVector minRangeVec = VECTOR(getNumFeatures());
	    DataVector maxRangeVec = VECTOR(getNumFeatures());

	    double minv, maxv;
	    for (unsigned int f = 0; f < getNumFeatures(); f++) {
	        minv = samples[0].getValue(f);
	        maxv = samples[0].getValue(f);
        	if(sampleMask == NULL){
				for (unsigned int s = 1; s < getNumSamples(); s++) {
						if (samples[s].getValue(f) < minv) minv = samples[s].getValue(f);
						if (samples[s].getValue(f) > maxv) maxv = samples[s].getValue(f);
				}
	        } else {
				for (unsigned int s = 1; s < getNumSamples(); s++) {
					if((*sampleMask)[s]){
						if (samples[s].getValue(f) < minv) minv = samples[s].getValue(f);
						if (samples[s].getValue(f) > maxv) maxv = samples[s].getValue(f);
					}
				}
	        }

	        minRangeVec(f) = minv;
	        maxRangeVec(f) = maxv;
	    }

	    return(DataRanges(minRangeVec,maxRangeVec));
	}

	void Dataset::calculateRanges() {
		DataRanges dr = calculateRangesMasked(NULL);
	    minRange = dr.minValues;
	    maxRange = dr.maxValues;
	}

	void Dataset::clear(){
		samples.clear();
	}

	/**
	 * Method adds new sample to dataset and recalculate ranges
	 * @param s
	 */
	void Dataset::add(Sample &s){
		statistics.get()->addPoint(&s);
		statistics->setGlobalRanges(statistics->getRanges());
		push(s);
	}

	/**
	 * Method removes sample with index \a sampleIdx from dataset and recalculate ranges
	 * @param sampleIdx
	 */
	void Dataset::remove(IndexType sampleIdx){
		Sample * s = &samples[sampleIdx];
		statistics->removeSample(s);
		samples.erase(samples.begin() + sampleIdx);
	}

	/**
	 * Get pointer to sample with index \a i
	 * @param i
	 * @return pointer
	 */
	Sample* Dataset::getSample(unsigned int i){
		return(&samples[i]);
	}

	/**
	 * Get copy of sample with index \a i
	 * @param i
	 * @return Sample Object
	 */
	Sample Dataset::copySample(unsigned int i){
		return(samples[i]);
	}

	/**
	 * Get copy of sample with index \a i
	 * @param i
	 * @return Sample Object
	 */
	/*Sample takeSample(unsigned int i){
		return(samples[i]);
	}*/

	/**
	 * Get pointer to data vector of sample with index \a i
	 * @param i
	 * @return
	 */
	DataVector* Dataset::getSampleVector(unsigned int i){
		return(samples[i].getVector());
	}

	/**
	 * Compute samples number for each class in the dataset
	 */
	/*void computeClassSamplesNumber(){
		IndexType classCount = 2;
		for (unsigned int s = 0; s < getNumSamples(); s++){
			IndexType y = getSample(s)->getY();
			if(classCount <= y) classCount = y + 1;
		}
		setNumClasses(classCount);

		for (unsigned int s = 0; s < getNumSamples(); s++){
			unsigned int classNumber = getSample(s)->getY();
			classSamplesNumber(classNumber)++;
		}
	}*/

	/**
	 * Get precomputed samples number of class \a c in the dataset
	 * @return
	 */
/*	unsigned int getClassSamplesNumber(unsigned int c){
		return(classSamplesNumber(c));
	}*/

	/**
	 * Shuffle all the samples randomly
	 */
	void Dataset::shuffle(){
		std::random_shuffle(samples.begin(), samples.end());
	}

	std::string Dataset::getInfo(){
		std::stringstream stream;
		stream << "\tDataset: " << this->getName() << std::endl;
			 stream << "\tFeatures: " << this->getNumFeatures() << std::endl;
			 stream << "\tClasses: " << this->getNumClasses() << std::endl;
			 stream << "\tSamples: " << this->getNumSamples() << std::endl<< std::endl;
			 stream << "\tClass distibution: " << this->classSamplesNumber.transpose();
			 for(IndexType i=0; i< getNumFeatures(); i++){
				 stream <<"\t\t"<< *this->getAttribute(i);
			 }
		return(stream.str());
	}

	/**
	 *
	 * @param d
	 * @param vec
	 * @param excluding
	 * @return
	 */
	DatasetUniquePtr Dataset::getSubset(IndexVector* vec, bool excluding){
		DatasetUniquePtr d(new Dataset);

		d->setNumClasses(getNumClasses());
		d->setNumFeatures(getNumFeatures());
		d->initStatistics();
		std::unique_ptr<IndexVector> v (new IndexVector);
		if(!excluding){
			*v = *vec;
		} else {
			IndexVectorUniquePtr vall ( new IndexVector(this->getNumSamples()) );
			for(IndexType i = 0; i < this->getNumSamples(); i++) vall.get()->push_back(i);
			std::sort(vec->begin(), vec->end());

			std::set_difference(
			    vec->begin(), vec->end(),
				vall->begin(), vall->end(),
			    std::back_inserter( *v ));

		}
		for(IndexType i = 0; i < v->size(); i++){
			IndexType idx = (*v)[i];
			d->add( *this->getSample(idx) );
			//d->push( copySample( idx ) );
		}
		//d->calculateRanges();
		return(std::move(d));
	}


	/**
	 * Method adds new sample to dataset without ranges recalculation
	 * @param s
	 */
	void Dataset::push(Sample s){
		if(statistics == nullptr) THROW("Statistics is null!");
		IndexType d = s.getY();
		if(this->getNumClasses() <= d){
			THROW("Class label is out of bound!");
		}
		this->samples.push_back(s);
	}

}




/*
 * PartitionStatistics.h
 *
 *  Created on: 23 нояб. 2015 г.
 *      Author: lladmin
 */

#ifndef CLASSIFIERS_PARTITIONSTATISTICS_H_
#define CLASSIFIERS_PARTITIONSTATISTICS_H_

#include <init.h>
#include <data/data.h>
#include <data/DataRanges.h>
#include <data/Sample.h>
#include <data/Attribute.h>

namespace ffactory {
	/**
	 * Propose facilities to get info about points in data-space partition
	 */
	class PartitionStatistics {
		public:

			void copyStatistics(PartitionStatistics& stat)
			{
				if(&stat == NULL) THROW("PartitionStatistics is NULL!");
				this->setNumClasses( stat.getNumClasses() );
				this->setNumFeatures( stat.getNumFeatures() );
				this->initDataRanges( stat.getRanges() );
				this->setPointsNumber( stat.getPointsNumber() );
				this->setCountsVector( stat.getCountsVector() );
				this->setDistrVector( stat.getDistrVector() );
				this->setGlobalRanges( stat.getGlobalRanges() );
				this->uniform = stat.isUniform();
			}


			PartitionStatistics& operator=(PartitionStatistics& other) // copy assignment
			{
			    if (this != &other) { // self-assignment check expected
			    	copyStatistics(other);
			    }
			    return *this;
			}

			PartitionStatistics(PartitionStatistics& other):
				pointsNumber(0),
				uniform(true)

			{
						copyStatistics(other);
			}

			PartitionStatistics():
				pointsNumber(0),
				uniform(true)
			{

			}

			PartitionStatistics(IndexType numClasses,
								IndexType numFeatures,
								std::vector<Sample> * data = NULL,
								DataRanges* dr = NULL,
								DataRanges* globalRanges = NULL
								):
				numClasses(numClasses),
				numFeatures(numFeatures),
				pointsNumber(0),
				uniform(true)
			{

				initDataRanges(dr);
				if(globalRanges!= nullptr){
					this->globalRanges.reset(new DataRanges(globalRanges));
				}
				initSampleStatistics(data, dr != NULL);
			}

			void addSamples(std::vector<Sample> * data){
				for(IndexType i=0; i< data->size(); ++i){
					addPoint(&(*data)[i]);
				}
			}

			void addSamplesInRange(std::vector<Sample> * data){
				for(IndexType i=0; i< data->size(); ++i){
					addPointInRange(&(*data)[i]);
				}
			}

			/**
			 * virual destructor
			 */
			virtual ~PartitionStatistics(){

			}


			void addCategorialPartitionRanges(IndexType attrIdx, DataType category){
				partitionRanges.minValues(attrIdx) = category;
				partitionRanges.maxValues(attrIdx) = category;
			}

			/**
			 * Removes sample from statistics.
			 * It should be used carefully because of sample weights changing.
			 * All points must be removed before change or after recomputing of class distribution!
			 * @param s
			 */
			void removeSample(Sample * const s){
				if(s->getY() >= numClasses)
									THROW(std::string("Invalid class label("+ std::to_string(s->getY()) +") >= numClasses(") + std::to_string(numClasses) + std::string(")") );
				pointsByClasses(s->getY())--;
				classesDistr(s->getY()) -= s->getW();

				if(getPointsNumber()==1){
							oldY = s->getY();
							uniform = true;
							return;
				}
			}

			/**
			 * Take point into account. Ranges values will be corrected if needed.
			 * @param s
			 */
			void addPoint(Sample * const s){
				//INFO(std::string("Class label = "+ std::to_string(s->getY()) +" (>=) numClasses =") + std::to_string(numClasses) + std::string(";") );

				if(s->getY() >= numClasses)
					THROW(std::string("Invalid class label("+ std::to_string(s->getY()) +") >= numClasses(") + std::to_string(numClasses) + std::string(")") );

				pointsByClasses(s->getY())++;
				classesDistr(s->getY()) += s->getW();

				setPointsNumber(getPointsNumber() + 1);

				if(getPointsNumber()==1){
					for (unsigned int f = 0; f < s->getNumFeatures(); f++) {
						setMinRangeValue(f, s->getValue(f));
						setMaxRangeValue(f, s->getValue(f) );
					}
					oldY = s->getY();
					uniform = true;
					return;
				} else {
					uniform = ( uniform && (oldY == s->getY()) );
				}


				for (unsigned int f = 0; f < s->getNumFeatures(); f++) {
		            if (s->getValue(f) < getMinRangeValue(f) ) {
		            	setMinRangeValue(f, s->getValue(f));
		            }
		            if (s->getValue(f) > getMaxRangeValue(f)) {
		            	setMaxRangeValue(f, s->getValue(f) );
		            }
				}
			}

			/**
			 * Take point into account if it is in range.
			 * @param s
			 */
			void addPointInRange(Sample * const s){
				if(s->getY() >= numClasses) THROW("Invalid class label >= numClasses");
				if( isInRanges( s )){
					pointsByClasses(s->getY())++;
					classesDistr(s->getY()) += s->getW();
					setPointsNumber(getPointsNumber() + 1);
					if(getPointsNumber()==1){
						oldY = s->getY();
						uniform = true;
					} else {
						uniform = ( uniform && (oldY == s->getY()) );
					}
					//INFO("Point "<< s->getVector()->transpose() << " is in Ranges");
				} else {
					//INFO("Point "<< s->getVector()->transpose() << " is NOT in Ranges");
				}
			}

			/**
			 * Set data ranges(if set) and initialize data structures for data ranges
			 * @param dr
			 */
			void initDataRanges(DataRanges* dr = NULL){
				if(numFeatures<1) THROW("numFeatures < 1 or unset at all");
				if(dr == NULL){
					partitionRanges.minValues  =  ZERO_VECTOR(numFeatures); // MIN VALUES
					partitionRanges.maxValues =  ZERO_VECTOR(numFeatures); // MAX VALUES
					//globalRanges->minValues  =  ZERO_VECTOR(numFeatures); // MIN VALUES
					//globalRanges->maxValues =  ZERO_VECTOR(numFeatures); // MAX VALUES
				} else {
					this->setRanges(*dr);
				}
			}

			/**
			 * Add samples to statistics in range(if ranged is set) of calculate range
			 * @param data
			 * @param ranged
			 */
			void initSampleStatistics(std::vector<Sample> * data = NULL, bool ranged = false){
				if(numClasses<2) THROW("numClasses < 2 or unset at all");
				this->pointsByClasses  =  ZERO_VECTOR(numClasses);
				this->classesDistr =  ZERO_VECTOR(numClasses);
				if(data){
					if(ranged){
						addSamplesInRange(data);
					} else {
						addSamples(data);
					}
				}
			}

			IndexType getPointsByClass(IndexType classNum){
				return(pointsByClasses(classNum));
			}

			void copyCountsVector(DataVector &ret){
				ret = pointsByClasses;
			}

			/**
			 * Get pointer to vector with counts of points by class
			 * @return
			 */
			DataVector * getCountsVector(){
				return(&pointsByClasses);
			}

			/**
			 * Get pointer to vector with class distribution (weighted samples)
			 * @return
			 */
			DataVector * getDistrVector(){
				return(&classesDistr);
			}

			void setDistrVector(DataVector * distr){
				classesDistr = *distr;
			}


			DataType getDistrNorma(){
				return(classesDistr.sum());
			}
			/**
			 * Set vector with counts of points by class (for copy constructor only)
			 * @return
			 */
			void setCountsVector(DataVector* v){
				pointsByClasses = *v;
			}

			void setMinRanges(DataVector& minVal){
				partitionRanges.minValues = minVal;
			}

			void setMaxRanges(DataVector& maxVal){
				partitionRanges.maxValues = maxVal;
			}

			DataVector * getMinRanges(){
				return(&partitionRanges.minValues);
			}

			DataVector * getMaxRanges(){
				return(&partitionRanges.maxValues);
			}

			DataType  getMinRangeValue(IndexType i){
				return(partitionRanges.minValues(i));
			}

			DataType  getMaxRangeValue(IndexType i){
				return(partitionRanges.maxValues(i));
			}

			void  setMinRangeValue(IndexType i,DataType v){
				partitionRanges.minValues(i) = v;
			}

			void  setMaxRangeValue(IndexType i,DataType v){
				partitionRanges.maxValues(i) = v;
			}

			/**
			 * Get total points number in the partition
			 * @return
			 */
			unsigned int getPointsNumber()
			{
				return pointsNumber;
			}

			void setPointsNumber(unsigned int pointsNumber)
			{
				this->pointsNumber = pointsNumber;
			}

			unsigned int getNumClasses()
			{
				return numClasses;
			}

			void setNumClasses(unsigned int numClasses)
			{
				this->numClasses = numClasses;
			}

			unsigned int getNumFeatures()
			{
				return numFeatures;
			}

			void setNumFeatures(unsigned int numFeatures)
			{
				this->numFeatures = numFeatures;
			}

			/**
			 * In contrary to DataRanges. isInRanges this method take global ranges into account
			 * @param s
			 * @return
			 */
			bool isInRanges(Sample* s){
				DataVector* v = s->getVector();

				if(partitionRanges.minValues.size()!=  v->size() || partitionRanges.maxValues.size()!=  v->size()) THROW("Vectors length must be the same.");

				if(globalRanges != nullptr){
						for(unsigned int i=0; i<v->size(); i++){
							Attribute *a = &(*attributes)[i];
							DataType data = v->coeff(i);

							if(a->getType() == ATTR_CATEGORIAL){

								if(!( data == partitionRanges.minValues(i) && partitionRanges.maxValues(i) == globalRanges->minValues(i))){
									return(false);
								}
							} else {

								if(!( (data == partitionRanges.minValues(i) && data == globalRanges->minValues(i)) ||
									  (data == partitionRanges.maxValues(i) && data == globalRanges->maxValues(i)) )
								  )
								if( data <= partitionRanges.minValues(i) || data > partitionRanges.maxValues(i) ){
									return(false);
								}
							}



						}
				} else {
					for(unsigned int i=0; i<v->size(); i++){
						DataType data = v->coeff(i);
						Attribute *a = &(*attributes)[i];
						if(a->getType() == ATTR_CATEGORIAL){
							if( data != partitionRanges.minValues(i) || data != partitionRanges.maxValues(i) ){
								return(false);
							}
						} else {
							if( data <= partitionRanges.minValues(i) || data > partitionRanges.maxValues(i) ){
								return(false);
							}
						}
					}
				}
				return(true);
			}


			DataRanges * getRanges(){
				return &partitionRanges;
			}

			void setRanges(DataRanges& dranges){
				partitionRanges = dranges;
			}
			/**
			 * Returns true if there is only one class points in partition
			 * in case of empty partition it also returns true
			 * @return
			 */
			bool isUniform(){
				return(uniform);
			}

			/**
			 * Returns true if partition is empty
			 * @return
			 */
			bool isEmpty(){
				return(pointsNumber == 0);
			}

			IndexType getMajorClass(){
				if(isEmpty()) WARN("Empty partition");
				IndexType cIdx;
				//MAX_VECTOR_INDEX(pointsByClasses,cIdx);/** \fixme Use weighted count! */
				MAX_VECTOR_INDEX(classesDistr,cIdx);
				return(cIdx);
			}

			DataRanges* getGlobalRanges() {
				return globalRanges.get();
			}

			void setGlobalRanges(DataRanges * globalRanges) {
				if(globalRanges)
					this->globalRanges.reset(new DataRanges(globalRanges));
			}


			/**
			* Generates information string
			* @return std::string contains information about object
			*/
			virtual std::string getInfo(){
				std::stringstream info;
				info << "PartitionStatistics"<< std::endl;


				info << "\tnumClasses: " << this->getNumClasses()<< std::endl;
				info << "\tnumFeatures: " << this->getNumFeatures()<< std::endl;
				info << "\t Points: " << this->getPointsNumber()<< std::endl;
				info << "\tPointsDistr: " << this->getCountsVector()->transpose()<< std::endl;
				info << "\tClassDistr: " << this->getDistrVector()->transpose()<< std::endl;

				info << "\tRanges";
				if(this->getRanges() != NULL){
					info << "\t\t" << *this->getRanges();
				} else
					info << "Not set";
				info << std::endl;

				info << "\tGlobalRanges";
				if(this->getRanges() != NULL){
					info << "\t\t" << *this->getGlobalRanges();
				} else
					info << "Not set";
				info << std::endl;

				return(info.str());
			}

			friend std::ostream& operator<< (std::ostream& stream, PartitionStatistics& b) {
				 stream << b.getInfo();
				 return (stream);
			}

			std::vector<Attribute>* getAttributes(){
				return attributes;
			}

			void setAttributes(std::vector<Attribute>* attributes) {
				this->attributes = attributes;
			}

			private:
				DataVector pointsByClasses;
				std::vector<Attribute>* attributes;
				DataVector classesDistr; /** Class distribution is used to take sample weights into account*/
				IndexType numClasses;
				IndexType numFeatures;
				DataRanges partitionRanges;
				DataRangesUniquePtr globalRanges;
				IndexType pointsNumber;

				bool uniform;
				IndexType oldY; // Uniformity check variable
	};

	DEFINE_PTR(PartitionStatistics)
} /* namespace ffactory */

#endif /* CLASSIFIERS_PARTITIONSTATISTICS_H_ */

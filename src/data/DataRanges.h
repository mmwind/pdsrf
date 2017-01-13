/*
 * DataRanges.h
 *
 *  Created on: 25 нояб. 2015 г.
 *      Author: lladmin
 */

#ifndef DATA_DATARANGES_H_
#define DATA_DATARANGES_H_

#include <data/data.h>
#include <utils/exceptions.h>

namespace ffactory {
	/**DataRanges
	 * first minimal sample range values
	 * second maximal sample range values
	*/
	class DataRanges{
	public:
			DataVector minValues;
			DataVector maxValues;

			DataRanges(){

			}

			DataRanges(DataVector &minRangeVec,DataVector &maxRangeVec){
				minValues = minRangeVec;
				maxValues = maxRangeVec;
			}

			DataRanges(DataRanges  *dr){
				if(dr != NULL){
					minValues = dr->minValues;
					maxValues = dr->maxValues;
				}
			}

			virtual ~DataRanges(){

			}

			virtual std::string getInfo(){
				std::stringstream info;
				info << "\t DataRanges"<< std::endl;
				info << "\t\t max:" << maxValues.transpose() << std::endl;
				info << "\t\t min:" << minValues.transpose() << std::endl;
				info << std::endl;

				return(info.str());
			}

			friend std::ostream& operator<< (std::ostream& stream, DataRanges& b) {
				 stream << b.getInfo();
				 return (stream);
			}


			/**
			 * Check if current data range is equal to \a dr
			 * @param dr
			 * @return
			 */
			bool isEqual(DataRanges  *dr){
				return( maxValues.isApprox( dr->maxValues ) && minValues.isApprox( dr->minValues ) );
			}


			/*
			 * Check if point is in specific range (including the values which are equal to range values)
			 * PLESE NOTE: There're some differences from PartitionStatistics.isInRanges !
			 * @param v
			 * @return
			 *
			bool isInRanges(DataVector *v){
				if(minValues.size()!=  v->size() || maxValues.size()!=  v->size()) THROW("Vectors length must be the same.");
				for(unsigned int i=0; i<v->size(); i++){
					DataType data = v->coeff(i);
					if( data > minValues(i) && data < maxValues(i) )
						return(false);
				}
				return(true);
			}
*/
			/***
			 * Check if point is in specific range (but in case of v(i) = maxRange(i) method returns false)
			 * PLESE NOTE: There're some differences from PartitionStatistics.isInRanges !
			 * @param v
			 * @return
			 **/
			bool isInRangesExcludeGreater(DataVector *v){
				if(minValues.size()!=  v->size() || maxValues.size()!=  v->size()) THROW("Vectors length must be the same.");
				for(unsigned int i=0; i<v->size(); i++){
					DataType data = v->coeff(i);
					if( data <= minValues(i) || data > maxValues(i) ){
						return(false);
					}
				}
				return(true);
			}






						/**
						 * Check if point is in specific range (including the values which are equal to range values)
						 * PLESE NOTE: There're some differences from PartitionStatistics.isInRanges !
						 * @param v
						 * @param featureNum
						 * @param excludeLowBound
						 * @return
						 */
						bool isInFeatureRanges(DataVector *v, IndexType featureNum, bool excludeLowBound = true){
							if(minValues.size()!=  v->size() || maxValues.size()!=  v->size()) THROW("Vectors length must be the same.");

								DataType data = v->coeff(featureNum);
								if( minValues(featureNum)==maxValues(featureNum) && data == maxValues(featureNum) )
									return(true);
								if(excludeLowBound){
									if( data < minValues(featureNum) || data >= maxValues(featureNum) )
										return(false);
								} else {
									if( data < minValues(featureNum) || data > maxValues(featureNum) )
										return(false);
								}
							return(true);
						}

	};
	DEFINE_PTR(DataRanges)
}

#endif /* DATA_DATARANGES_H_ */

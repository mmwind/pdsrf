/*
 * PDStreamingRF.h
 *
 *  Created on: 24 янв. 2016 г.
 *      Author: lladmin
 */

#ifndef CLASSIFIERS_ENSEMBLE_PDSTREAMINGRF_H_
#define CLASSIFIERS_ENSEMBLE_PDSTREAMINGRF_H_

#include <classifiers/ensemble/aggregator/AverageEnsembleAggregator.h>
#include <classifiers/errorMeasures/MissclassificationErrorMeasure.h>
#include <classifiers/ensemble/WeightedBaggingClassifier.h>
#include <models/ExtremelyRandomizedTree.h>

namespace ffactory {

	class PDStreamingRF: public WeightedBaggingClassifier<ExtremelyRandomizedTree> {
		protected:
			DataVector predictedLeafIds;
			DataVector predictedErrors;
		public:
			PDStreamingRF(IndexType seed):
				WeightedBaggingClassifier<ExtremelyRandomizedTree>(seed) {

				BaseErrorMeasureUniquePtr em(new MissclassificationErrorMeasure);
				BaseEnsembleAggregatorUniquePtr agg(new AverageEnsembleAggregator);
				this->setErrorMeasure(std::move(em));
				this->setAggregator(std::move(agg));

			}

			DataVector* getPredictedLeafIds(){
				return(&predictedLeafIds);
			}

			DataVector* getPredictedErrors(){
				return(&predictedErrors);
			}

			virtual void setupNewClassifier(BaseClassifier* clf){
				static_cast<ExtremelyRandomizedTree*>(clf)->setMtry();
			}

			virtual double train(Dataset *d){
				predictedLeafIds = ZERO_VECTOR(getNumClassifiersToTrain());
				predictedErrors = ZERO_VECTOR(getNumClassifiersToTrain());
				for(IndexType i=0; i< getNumClassifiersToTrain(); i++){
					trainNewClassifier(d);

					DataType a = getClassifierOOBError(i);
					if(this->isVerbose())
						INFO("Accuracy(" << i <<") = "<<a);
				}
				return(this->test(d));
			}
			/**
			 * Predict class probability of one sample
			 * @param sample
			 * @return Index of class
			 */
			virtual DataVectorUniquePtr predictClassProb(Sample * sample){
				DataVectorUniquePtr confPtr( new  DataVector(getNumClasses()));
				DataVector* conf = confPtr.get();
				(*conf) = ZERO_VECTOR(getNumClasses());

				DataType weightsNorma = 0;
				for(IndexType i=0; i< this->getNumClassifiers(); i++){
					DataVectorUniquePtr ptr = std::move(getClassifier(i)->predictClassProb(sample));
					//INFO("Cl: " << i << " conf: "<< ptr->transpose() << " w: " << ensembleWeights[i] << " y: " << sample->getY());
					predictedErrors(i) = 1 - ptr->coeff(sample->getY());
					predictedLeafIds(i) = static_cast<ExtremelyRandomizedTree*>(getClassifier(i))->getPredictedLeafId();
					(*conf) += (*ptr) * ensembleWeights[i];
					weightsNorma += ensembleWeights[i];
				}
				(*conf) = (*conf) / weightsNorma;
				//INFO("X: " <<sample->getVector()->transpose() << " | Y: " << sample->getY() << " | " << conf.transpose());
				return(std::move(confPtr));
			}
	};

} /* namespace ffactory */

#endif /* CLASSIFIERS_ENSEMBLE_PDSTREAMINGRF_H_ */

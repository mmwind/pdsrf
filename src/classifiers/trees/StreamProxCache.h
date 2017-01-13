/*
 * StreamProxCache.h
 *
 *  Created on: 24 янв. 2016 г.
 *      Author: lladmin
 */

#ifndef CLASSIFIERS_TREES_STREAMPROXCACHE_H_
#define CLASSIFIERS_TREES_STREAMPROXCACHE_H_

#include <data/Dataset.h>
#include <data/weighting/DataTemporalExponentialWeighting.h>
#include <classifiers/ensemble/PDStreamingRF.h>
#include <classifiers/ensemble/weighting/AccuracyDependentWeightFactory.h>

namespace ffactory {

	typedef enum{
	    PROXIMITY_RF   = 0,  //! Proximity obtained from intrinsic RandomForest prox.
		PROXIMITY_EUCLEDIAN  = 1,  //! Basic eucledian distance scaled by feature range (all features have equal weight)
		PROXIMITY_EUCLEDIAN_SCALED  = 2,  //! Basic eucledian distance scaled by feature range and importance of oldblock
	} ProximityMeasureType;


	class StreamProxCache: public Base {
		protected:
			PDStreamingRF rf;
			ProximityMeasureType proximityMeasure;

			IndexType epoch;
			IndexType epochs;

			bool verbose;
			Dataset* datastream;
			DatasetUniquePtr dataset;
			DatasetUniquePtr newblockDataset;

			std::vector<DataType> times;
			DataMatrix predictedLeafs; /** cols - trees, rows - samples */
			DataMatrix predictedErrors; /** cols - trees, rows - samples */

			DataType time;

			std::vector< std::pair<IndexType, DataType> > nearestSamples;

			IndexType currentStreamPosition;
			IndexType blockSize;/** Stream block size (chunk size) */
			IndexType cacheSize;/** Maximal dataset size */
			IndexType nearestNeighbours;
			IndexType treecount;

			DataVector newBlockErrors; // Classifiers errors for new block

			IndexType predictedClass; // predicted class can be obtained after predict method
			IndexType oldPredictedClass; // predicted class can be obtained after predict method

			DataTemporalWeightingFunctionUniquePtr sampleWeighting;
			BaseAccuracyDependentWeightUniquePtr classiferWeighting;

			void initMatrixes(IndexType T, IndexType N){
				predictedLeafs = ZERO_MATRIX(N,T);
				predictedErrors = ZERO_MATRIX(N,T);
			}

		public:

			DataVector testsAccuracyAfter;
			DataVector testsAccuracyBefore;
			DataVector cacheAccuracy;

			StreamProxCache(Dataset* datastream,
							IndexType block = 40,
							IndexType cache = 0,
							IndexType numNearestNeighbours = 5,
							DataType sampleWeight = 0.01,
							std::string clfWeighing = "binary",
							bool _verbose = false,
							IndexType epochsNumber = 0,
							IndexType _treecount = 15,
							ProximityMeasureType _proximityMeasure = PROXIMITY_RF
							):
				rf(13),
				proximityMeasure(_proximityMeasure),
				datastream(datastream),
				blockSize(block),
				dataset(new Dataset()),
				sampleWeighting(new DataTemporalExponentialWeighting(sampleWeight)),
				classiferWeighting(new AccuracyDependentWeight),
				nearestNeighbours(numNearestNeighbours),
				time(0),
				epoch(0),
				epochs(epochsNumber),
				verbose(_verbose),
				treecount(_treecount)
			{

				//rf.setNumSplits(250);
				AccuracyDependentWeightFactory f;
				f.Register();
				classiferWeighting = std::move(f.createUnique(clfWeighing));

				currentStreamPosition = 0;
				cacheSize = cache;
				if(cacheSize == 0)
					cacheSize = blockSize*2;

				if(epochsNumber == 0){
					epochs = floor(datastream->getNumSamples() / blockSize);
				}
				testsAccuracyAfter = ZERO_VECTOR( epochs + 1);
				testsAccuracyBefore = ZERO_VECTOR( epochs + 1 );
				cacheAccuracy = ZERO_VECTOR( epochs + 1 );
				rf.setVerbose(verbose);
			}

			/**
			 * addFirstBlockToDataset добавляет первый блок из потока в кэш
			 * \bug пока кэш не лимитирован, нужно исправить позже
			 */
			void addFirstBlockToDataset(){
				for(IndexType i = 0; i< blockSize; i++){
					currentStreamPosition++;
					Sample *s = datastream->getSample(currentStreamPosition);
					dataset->add(*s);
				}
			}

			void prepareNewblockDataset(){
				newblockDataset.reset(new Dataset);
				newblockDataset->setNumClasses(rf.getNumClasses());
				newblockDataset->setNumFeatures(rf.getNumFeatures());
				newblockDataset->initStatistics();

				for(IndexType i = 0; i< blockSize; i++){
					Sample *s = datastream->getSample(currentStreamPosition + i);
					newblockDataset->add(*s);
				}
			}
			/**
			 * Get accuracy of current classifier test on the new block
			 */
			DataType testNewBlock(){
				DataVector res(rf.getNumClasses());
				DataType acc = 0;
				DataType oldacc = 0;

				prepareNewblockDataset();

				newBlockErrors = ZERO_VECTOR(rf.getNumClassifiers());
				for(IndexType i = 0; i< blockSize; i++){
					Sample *s = datastream->getSample(currentStreamPosition + i);
					predict(s,res);
					newBlockErrors += *rf.getPredictedErrors();
					if(predictedClass == s->getY())
						acc = acc + 1;
					if(oldPredictedClass == s->getY())
						oldacc = oldacc + 1;
				}
				oldacc = oldacc / blockSize;
				acc = acc / blockSize;
				testsAccuracyAfter(epoch) = acc;
				testsAccuracyBefore(epoch) = acc;
				return(acc);
			}


			/**
			 * addBlockToDataset добавляет первый блок из потока в кэш
			 */
			void addBlockToDataset(){
				for(IndexType i = 0; i< blockSize; i++){
					currentStreamPosition++;
					Sample *s = datastream->getSample(currentStreamPosition);
					addSample(s);
				}
				// удалим старые данные из кэша
				while(dataset->getNumSamples()>cacheSize){
					removeSample(0);
					INFO("Remove sample " << dataset->getNumSamples());
				}
			}

			/**
			 * Восстановить простое голосование по большинству
			 */
			void resetClassifiersWeights(){
				  DataVector w(rf.getNumClassifiers());
				  w.fill(1);
				  rf.setClassifersWeights(w);
			}

			/**
			 * Создаём первый блок
			 */
			void firstBuildProxErrors(){
				for(IndexType i = 0; i< dataset->getNumSamples(); i++){
					rf.predict(dataset->getSample(i));
					//INFO("S"<< i <<" L["<< rf.getPredictedLeafIds()->transpose() <<"] E["<< rf.getPredictedErrors()->transpose() << "]");
					predictedLeafs.row(i) = *rf.getPredictedLeafIds();
					predictedErrors.row(i) = *rf.getPredictedErrors();
				}
			}

			DataType evaluateClassifiersError(Dataset *d){
				DataType acc = 0;
				newBlockErrors = ZERO_VECTOR(rf.getNumClassifiers());
				for(IndexType i =0; i<rf.getNumClassifiers(); i++){
						DataType a = rf.getClassifier(i)->test(newblockDataset.get());
						newBlockErrors(i) = 1 - a;
						acc += a;
				}
				return(acc / rf.getNumClassifiers());
			}

			DataType evaluateNewBlockDataset(Dataset *d){
				DataVector res(rf.getNumClasses());
				DataType acc = 0;
				for(IndexType i = 0; i< d->getNumSamples(); i++){
					Sample *s = d->getSample(i);
					predict(s,res);
					if(predictedClass == s->getY())
						acc++;
				}

				return(acc/d->getNumSamples());
			}

			void testStream1(Dataset *preTrain){
				// prepare dataset
								dataset->setNumClasses(datastream->getNumClasses());
								dataset->setNumFeatures(datastream->getNumFeatures());
								dataset->initStatistics();

								// add first block


								for(IndexType i = 0; i< preTrain->getNumSamples(); i++){
									//currentStreamPosition++;
									Sample *s = preTrain->getSample(i);
									dataset->add(*s);
								}

								// prepare ensemble
								rf.setRandomSeed(13);
								rf.setTrainDataset(dataset.get());
								//rf.setTrainSubsetSize(dataset->getNumSamples());
								rf.setTrainSubsetSize(dataset->getNumSamples()/3);
								rf.setNumClassifiersToTrain(treecount);


								//preTrain->initStatistics();
								/*rf.setRandomSeed(13);
								rf.setTrainDataset(preTrain);
								rf.setTrainSubsetSize(preTrain->getNumSamples());
								rf.setNumClassifiersToTrain(treecount);*/

								// train ensemble on first block
								rf.train(dataset.get());

								dataset->clear();
								addFirstBlockToDataset();
								rf.setTrainSubsetSize(dataset->getNumSamples());
								initMatrixes(rf.getNumClassifiersToTrain(),blockSize);

								firstBuildProxErrors();
								testsAccuracyBefore(epoch) = rf.test(dataset.get());
								testsAccuracyAfter(epoch) = rf.test(dataset.get());

								/*if(epochs == 0){
									epochs = floor(datastream->getNumSamples()/ blockSize);
								}*/
								while( epoch < epochs ){
									epoch++;
									//if(verbose)
										INFO("Epoch ["<<epoch<<"] ");
										INFO("Cachesize = ["<<dataset->getNumSamples()<<"] ");
										if(newblockDataset!=nullptr)
											INFO("NewBlockDSSize = ["<<newblockDataset->getNumSamples()<<"] ");

									prepareNewblockDataset();
									testsAccuracyBefore(epoch) = evaluateClassifiersError(newblockDataset.get());
									testsAccuracyAfter(epoch) = evaluateNewBlockDataset(newblockDataset.get());
									addBlockToDataset();
									this->resetClassifiersWeights();
									cacheAccuracy(epoch) = rf.test(dataset.get());

									int counter = rf.getClassifiersNumber();
									DataType a = evaluateClassifiersError(newblockDataset.get());
									while(a<0.99 && counter>0 ){
										if(verbose)
											INFO("Accuracy is low ("<<a<<") ,renew classifier #"<<counter);
										replaceTheLooser();
										a = evaluateClassifiersError(newblockDataset.get());
										counter--;
									}


								}
								//std::cout << "------------------------------" << std::endl;
								//std::cout << testsAccuracyBefore.transpose() << std::endl;
								//std::cout << testsAccuracyAfter.transpose() << std::endl;
								//std::cout << cacheAccuracy.transpose() << std::endl;
								//printError(std::cout);
			}
/*
			void testStream(){
				// prepare dataset
				dataset->setNumClasses(datastream->getNumClasses());
				dataset->setNumFeatures(datastream->getNumFeatures());
				dataset->initStatistics();

				// add first block
				addFirstBlockToDataset();

				// prepare ensemble
				rf.setTrainDataset(dataset.get());
				rf.setTrainSubsetSize(dataset->getNumSamples());
				rf.setNumClassifiersToTrain(treecount);
				initMatrixes(rf.getNumClassifiersToTrain(),blockSize);

				// train ensemble on first block
				rf.train(dataset.get());

				firstBuildProxErrors();
				testsAccuracyAfter(epoch) = rf.test(dataset.get());

				if(epochs == 0){
					epochs = floor(datastream->getNumSamples()/ blockSize);
				}
				while( epoch < epochs ){
					epoch++;
					testNewBlock();
					INFO("old accuracy:" << testsAccuracyBefore(epoch));
					INFO("new accuracy:" << testsAccuracyAfter(epoch));
					//for(int i = 0; i<10; i++)
					int i = 0;
					while( i < rf.getNumClassifiers()){
						replaceTheLooser();
						i++;
					}
					// add new block
					addBlockToDataset();
					cacheAccuracy(epoch) = rf.test( dataset.get());
					INFO("cache accuracy =" << cacheAccuracy(epoch) );
				}
				//INFO("Add new classifier");
				//rf.trainNewClassifier(dataset.get());
				//BaseTree *t = static_cast<BaseTree *>(rf.getClassifier( rf.getNumClassifiers() - 1));
				//addNewClassifier(t);

				//INFO("Accuracy 2 =" << rf.test(dataset.get()) );
				printError(std::cout);
			}
*/
			void printError(std::ostream &s){
				s << "|\tEpoch\t|\told\t|\tnew\t|\tcache\t|" << std::endl;
				s << "|\t----\t|\t---\t|\t---\t|\t----\t|" << std::endl;
				for(IndexType i =0; i< testsAccuracyAfter.rows(); i++){
					s  << "|\t" << i <<"\t|\t" << testsAccuracyBefore(i) <<"\t|"<< testsAccuracyAfter(i) <<"\t|"<< cacheAccuracy(i) <<"\t|" << std::endl;
				}
			}

		  void predict(Sample *s, DataVector &result){
			  this->resetClassifiersWeights();
			  DataVectorUniquePtr p = std::move(rf.predictClassProb(s));
			  p->maxCoeff(&oldPredictedClass);

			  switch(proximityMeasure){
				  case PROXIMITY_RF: computeNearestSamples(rf.getPredictedLeafIds(), nearestNeighbours); break;
				  case PROXIMITY_EUCLEDIAN: computeNearestSamplesEucledian(s, nearestNeighbours); break;
			  }


			  DataVector ClassifersErrors = ZERO_VECTOR(rf.getNumClassifiers());
			  for(IndexType i=0; i< nearestNeighbours; i++){
				  ClassifersErrors += predictedErrors.row( nearestSamples[i].first ); // /rf.getClassifiersNumber() //* nearestSamples[i].second;
			  }
			  ClassifersErrors = ClassifersErrors /nearestNeighbours;



			  DataVector w(rf.getNumClassifiers());
			  w.fill(1);
			  for(IndexType i=0; i< rf.getNumClassifiers(); i++){
					  //w(i) = 1/(ClassifersErrors(i)*ClassifersErrors(i) + 1e-3 );
				  	   w(i) = 1/(ClassifersErrors(i)*ClassifersErrors(i) + 1e-3 );
			  }

			  rf.setClassifersWeights(w);
			  DataVectorUniquePtr p2 = std::move(rf.predictClassProb(s));
			  result = *p2;
			  p2->maxCoeff(&predictedClass);

		  }
		  	  // (row,col)
			DataType getProximity(DataVector* leafIds,IndexType idx){
				DataType prox = 0;
				//INFO("predictedLeafs cols:"<< predictedLeafs.cols() << " rows:" << predictedLeafs.rows() << " leafIds: " << leafIds->size());

				//INFO("leafIds "<< leafIds->transpose() << "predictedLeafs(idx) " << predictedLeafs.row(idx));

				for(IndexType i=0; i<predictedLeafs.cols();i++ ){

					if(leafIds->coeff(i) == predictedLeafs(idx,i))
						prox++;
				}
				return(prox);
			}


			/**
			 * \todo Use more effective sort
			 * @param leafIds
			 * @param numberOfSamples
			 */
			void computeNearestSamples(DataVector* leafIds, IndexType numberOfSamples){
				for(IndexType i=0; i< dataset->getNumSamples(); i++){
					DataType prox = getProximity(leafIds,i);
					std::pair<IndexType, DataType> p =
							std::make_pair(i, prox);
					nearestSamples.push_back(p);
				}

				/*std::sort(nearestSamples.begin(), nearestSamples.end(), [](std::pair<IndexType, DataType> a, std::pair<IndexType, DataType> b) {
				        return b.second > a.second;
				    });*/

				std::partial_sort( nearestSamples.begin(),
							  nearestSamples.end() + numberOfSamples,
							  nearestSamples.end(),
							  [](std::pair<IndexType, DataType> a, std::pair<IndexType, DataType> b) {
							  				        return b.second < a.second;
							  				    });

				nearestSamples.erase(nearestSamples.begin()+numberOfSamples,nearestSamples.end());

				/*for(IndexType i=0; i< nearestSamples.size(); i++){
					INFO("nearest S" << nearestSamples[i].first << " dist=" << nearestSamples[i].second);
				}*/
			}


			void computeNearestSamplesEucledian(Sample *s, IndexType numberOfSamples){

				DataVector scale = *dataset->getStatistics()->getMaxRanges() - *dataset->getStatistics()->getMinRanges();
				for(IndexType i=0; i< dataset->getNumSamples(); i++){
					DataVector d = *dataset->getSample(i)->getVector() - *s->getVector();
					d = d.cwiseQuotient(scale);
					DataType prox = d.norm();
					std::pair<IndexType, DataType> p =
							std::make_pair(i, prox);
					nearestSamples.push_back(p);
				}

				/*std::sort(nearestSamples.begin(), nearestSamples.end(), [](std::pair<IndexType, DataType> a, std::pair<IndexType, DataType> b) {
				        return b.second > a.second;
				    });*/
				std::partial_sort( nearestSamples.begin(),
							  nearestSamples.end() + numberOfSamples,
							  nearestSamples.end(),
							  [](std::pair<IndexType, DataType> a, std::pair<IndexType, DataType> b) {
							  				        return b.second < a.second;
							  				    });

				nearestSamples.erase(nearestSamples.begin()+numberOfSamples,nearestSamples.end());

				//for(IndexType i=0; i< nearestSamples.size(); i++){
				//	INFO("nearest S" << nearestSamples[i].first << " dist=" << nearestSamples[i].second);
				//}
			}

			void addSample(Sample *s){
				if(dataset->getNumSamples() == cacheSize){
					removeSample(0);
				}
				dataset->add(*s);

				times.push_back(time);

				DataVector errors(rf.getClassifiersNumber());
				DataVector leafids(rf.getClassifiersNumber());

				for(IndexType i=0; i< rf.getClassifiersNumber(); i++){
					BaseTree *t = static_cast<BaseTree *>(rf.getClassifier(i));
					Prediction p = t->predict( s );
					errors(i) =  1 - p.getConfidence(0)(s->getY());
					leafids(i) = t->getPredictedLeafId();
				}
				//appendColumn(predictedLeafs,  &leafids);
				//appendColumn(predictedErrors, &errors);
				appendRow(predictedLeafs,  &leafids);
				appendRow(predictedErrors, &errors);
				//predictedLeafs.col( dataset->getNumSamples() - 1 ) = *LeafIds;
			}

			void removeSample(IndexType sampleIdx){
				dataset->remove(sampleIdx);
				times.erase(times.begin() + sampleIdx);
				removeRow(predictedLeafs, sampleIdx);
				removeRow(predictedErrors, sampleIdx);
			}


			void addNewClassifier(BaseTree* t){
				DataVector leafs(dataset->getNumSamples());
				DataVector errors(dataset->getNumSamples());

				for(IndexType i=0; i<dataset->getNumSamples(); i++ ){
					Sample * s = dataset->getSample(i) ;
					Prediction p = t->predict( s );
					errors(i) =  1 - p.getConfidence(0)(s->getY());
					leafs(i) = t->getPredictedLeafId();
				}

				appendColumn(predictedLeafs,  &leafs);
				appendColumn(predictedErrors, &errors);
			}

			void removeClassifier(IndexType cidx){
				removeColumn(predictedLeafs,  cidx);
				removeColumn(predictedErrors, cidx);
				rf.removeClassifier(cidx);
			}

			void replaceTheLooser(){
				IndexType looserIdx;
				MAX_VECTOR_INDEX(newBlockErrors,looserIdx);
				removeClassifier(looserIdx);
				rf.trainNewClassifier(newblockDataset.get());
				BaseTree *t = static_cast<BaseTree *>(rf.getClassifier( rf.getNumClassifiers() - 1));
				addNewClassifier(t);
			}

		Dataset* getDataset()
		{
			return dataset.get();
		}

		Dataset* getDatastream()
		{
			return datastream;
		}

		void setDatastream(Dataset* datastream)
		{
			this->datastream = datastream;
		}

		double getTime() const
		{
			return time;
		}

		void setTime(double time)
		{
			this->time = time;
		}
	};

} /* namespace ffactory */

#endif /* CLASSIFIERS_TREES_STREAMPROXCACHE_H_ */

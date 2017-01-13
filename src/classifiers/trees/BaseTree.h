/*
 * baseTree.h
 *
 *  Created on: 28 окт. 2015 г.
 *      Author: llproger
 */

#ifndef CLASSIFIERS_TREES_BASETREE_H_
#define CLASSIFIERS_TREES_BASETREE_H_

#include <Base.h>
#include <fstream>
#include <classifiers/trees/baseTreeClassifier.h>
#include <classifiers/trees/baseTreeNode.h>
#include <classifiers/trees/splits/SplitStatisticsContainer.h>
#include <classifiers/trees/TreeNodeFactory.h>
//#include <classifiers/trees/Partitioner.h>

namespace ffactory {

/**
 * Base class for all (binary) trees
 */
class BaseTree : public BaseTreeClassifier {
protected:
	BaseTreeNodeUniquePtr Root;
	TreeNodeFactory nodeFactory;
	std::string nodeType;
	IndexType idCounter;
	//Partitioner partitioner;
	IndexType predictedLeafId;

	/**
	 * Get pointer to node with specified \a id from \a FirstNode
	 * @param FirstNode
	 * @param id
	 * @return BaseTreeNode pointer from BaseTreeNodeUniquePtr
	 */
	BaseTreeNode* getTreeNodeById(BaseTreeNode* FirstNode, IndexType id){
		if(FirstNode == NULL) return(NULL);
		if(FirstNode->getId() == id){
			return(FirstNode);
		} else {
			BaseTreeNode* node = getTreeNodeById(FirstNode->getDownNodeLeft(),id);
			if(node != NULL) return(node);
						  node = getTreeNodeById(FirstNode->getDownNodeRight(),id);
			if(node != NULL) return(node);
		}
		return(NULL);
	}


public:
			BaseTree()
			{
				idCounter = 0;
				setName("Decision Tree");
				nodeType = "base";
				nodeFactory.Register();
			}

			/**
			 * Create root node
			 * @return pointer to node
			 */
			BaseTreeNode* addRoot(){
				Root = std::move( nodeFactory.createUnique(nodeType));
				Root->setId(0);
				Root->setDepth(0);
				return(Root.get());
			}


			/**
			 * Add \a newNode to right (or left) branch of \a parentNode
			 * @param newNode
			 * @param parentNode
			 * @param toRight
			 */
			BaseTreeNode* addNode(BaseTreeNode* parentNode, BinaryTreeNodeType type){
				BaseTreeNodeUniquePtr newNode = std::move( nodeFactory.createUnique(nodeType));
				newNode->setId(++idCounter);
				newNode->attachToParent(parentNode);
				BaseTreeNode* node = newNode.get();
				if(type == NODE_RIGHT)
					parentNode->setDownNodeRight( std::move(newNode) );
				else
					parentNode->setDownNodeLeft(  std::move(newNode) );
				return(node);
			}


			/**
			 *
			 * @param id
			 * @return
			 */
			BaseTreeNode* getNodeById(IndexType id){
				return(getTreeNodeById(Root.get(), id));//
			}


			/**
			* Train classifier on dataset \a d
			* @param d
			* @return Value of specified error measure on dataset \a d
			*/
			virtual double train(Dataset* d){
				setTrainDataset(d);
				checkSettings();
				getSplitGenerator()->setDataset(d);

				learn(NULL);
				return(0.0);
			}


			/**
			 * Recursive function of tree learning
			 * @param newNode
			 * @param m
			 * @return
			 */
			BaseTreeNode* learn(BaseTreeNode* newNode){

				// Check for Root node
				if(newNode == NULL){
					newNode = addRoot();
				}

				if(isVerbose())
					INFO( getNodeTypeString(newNode->getNodeType()));

				// Initialize partition statistics
				newNode->setNumClasses(this->getNumClasses());
				newNode->setNumFeatures(this->getNumFeatures());

				// Check for Root node
				if(newNode->isRoot()){
					newNode->getStatistics()->copyStatistics( *getTrainDataset()->getStatistics() );
					for(IndexType i=0; i<this->getNumTrainSamples(); i++)
						newNode->addIndex(i);
				}

				if(isVerbose())
					INFO( "PointsDistr: " << newNode->getStatistics()->getCountsVector()->transpose() );


			   // Check if current subset of samples have the same class
			   // if so we need to produce terminal node with this class
				if(newNode->getStatistics()->isUniform()){
					newNode->computeLabel();
					if(isVerbose()){
						INFO("[UNIFORM] Terminal node #" << newNode->getId() << " with label " << newNode->getClassLabel() );
					}
					return(NULL);
				}

				// Check stoppage criterion
				if( getStoppageCriterion()->IsStoppageNeeded(newNode, *newNode->getStatistics()->getCountsVector()) ){
					newNode->computeLabel();
					if(isVerbose()){
						INFO("[STOP] Terminal node #" << newNode->getId() << " with label " << newNode->getClassLabel() );
					}
					// produce terminal node
					return(NULL);
				}

				DataType bestSplitScore = MAX_DATA_VAL;
				IndexType bestSplitIndex = 0;

				// Repeat until split with non-empty partitions is found
				while (bestSplitScore == MAX_DATA_VAL){
					getSplitGenerator()->clear();
					getSplitGenerator()->generate(newNode->getStatistics()->getRanges());

					// For all generated splits
					for(IndexType j = 0; j<getSplitGenerator()->getSplitNum(); j++ ){
						BinarySplit* splitCandidate = getSplitGenerator()->getSplit(j);
						PartitionStatistics lp( getNumClasses(), getNumFeatures() );
						PartitionStatistics rp( getNumClasses(), getNumFeatures() );

						// For all points in this partition
						for(IndexType i=0; i<newNode->getIndexes()->size(); i++ ){
							IndexType idx = newNode->getIndexes()->at(i);
							Sample *s = this->getTrainDataset()->getSample(idx);
							if( splitCandidate->decide( s->getVector() ) ){
								rp.addPoint(s);
							} else {
								lp.addPoint(s);
							}
						}

						DataType score = this->getSplitQualityMeasurer()->getScore( &lp, &rp );
						splitCandidate->setScore(score);
						if(bestSplitScore > score){
							bestSplitScore = score;
							bestSplitIndex = j;
						}
					}
				}


				/* Add new nodes and calculate statistics */
				BaseTreeNode* nodeLeft  = addNode(newNode, NODE_LEFT );
				BaseTreeNode* nodeRight = addNode(newNode, NODE_RIGHT );
				BinarySplit* best = getSplitGenerator()->getSplit(bestSplitIndex);

				PartitionStatistics lp( getNumClasses(), getNumFeatures() );
				PartitionStatistics rp( getNumClasses(), getNumFeatures() );

				for(IndexType i=0; i<newNode->getIndexes()->size(); i++ ){
					IndexType idx = newNode->getIndexes()->at(i);
					Sample *s = this->getTrainDataset()->getSample(idx);
					if( best->decide( s->getVector() ) ){
						rp.addPoint(s);
						nodeRight->addIndex(idx);
					} else {
						lp.addPoint(s);
						nodeLeft->addIndex(idx);
					}
				}
				nodeLeft->getStatistics()->copyStatistics(lp);
				nodeRight->getStatistics()->copyStatistics(rp);
				newNode->setFeatureIndex(best->getFeatureIndex());
				newNode->setFeatureValue(best->getFeatureValue());
				newNode->setScore(bestSplitScore);

				if(isVerbose()){
					INFO("New split " <<  newNode->getId()  << " at depth " << newNode->getDepth() << " with score " << newNode->getScore() );
					INFO("Feature " << this->getTrainDataset()->getAttribute(newNode->getFeatureIndex())->getName()  << " value " << newNode->getFeatureValue() );
				}

				learn(nodeRight);
				learn(nodeLeft);

				newNode->clearIndexes();
				return(newNode);
			}


			virtual DataVectorUniquePtr predictClassProb(Sample * sample){
				DataVectorUniquePtr classProbPtr( new DataVector( this->getNumClasses() ) );
				classProbPtr.get()->fill(0);
				BaseTreeNode * node = Root.get();

						while(!node->isTerminal()){
							if( node->decide(sample->getVector()) ){
								node = node->getDownNodeRight();
							} else {
								node = node->getDownNodeLeft();
							}
						}
						predictedLeafId = node->getId();
				(*classProbPtr.get())(node->getClassLabel()) = 1;
				return(std::move(classProbPtr));
			}


			/**
			 * Generates information string
			 * @return std::string contains information about classifier
			 */
			virtual std::string getInfo(){
				std::stringstream info;
				info << BaseClassifier::getInfo();

				if(this->getSplitGenerator() != NULL){
					info << "\t" <<(*this->getSplitGenerator());
				} else
					info << "Not set";
				info << std::endl;

				if(this->getSplitQualityMeasurer() != NULL){
					info << "\t" << (*this->getSplitQualityMeasurer());
				} else
					info << "Not set";
				info << std::endl;

				if(this->getStoppageCriterion() != NULL){
					info << "\t" << (*this->getStoppageCriterion());
				} else
					info << "Not set";
				info << std::endl;

				/*
				info << "\tSplit generator: " << (this->getSplitGenerator() != NULL ? *this->getSplitGenerator(): "Not set") << "\n";
				info << "\tQuality measurer: " << (this->getSplitQualityMeasurer() != NULL ? *this->getSplitQualityMeasurer(): "Not set") << "\n";
				info << "\tStoppage criterion: " << (this->getStoppageCriterion() != NULL ? *this->getStoppageCriterion(): "Not set") << "\n";
		*/
				return(info.str());
				/** \todo Написать вывод полной инфы о дереве */
			}

			IndexType getPredictedLeafId(){
				return(predictedLeafId);
			}

			unsigned int getIdCounter() const
			{
				return idCounter;
			}

			void setIdCounter(unsigned int idCounter)
			{
				this->idCounter = idCounter;
			}

			BaseTreeNode* getRoot()
			{
				return Root.get();
			}

			void setRoot(BaseTreeNodeUniquePtr root)
			{
				Root = std::move(root);
			}

			TreeNodeFactory* getNodeFactory()
			{
				return &nodeFactory;
			}

			std::string getNodeType()
			{
				return nodeType;
			}

			void setNodeType(std::string nodeType)
			{
				this->nodeType = nodeType;
			}
		};

DEFINE_PTR(BaseTree)

} /* namespace ffactory */

#endif /* CLASSIFIERS_TREES_BASETREE_H_ */

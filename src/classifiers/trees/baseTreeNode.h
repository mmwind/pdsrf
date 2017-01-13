/*
 * BaseTreeNode.h
 *
 *  Created on: 28 окт. 2015 г.
 *      Author: llproger
 */

#ifndef CLASSIFIERS_TREES_BASETREENODE_H_
#define CLASSIFIERS_TREES_BASETREENODE_H_

#include <init.h>
#include <data/data.h>
#include <classifiers/trees/splits/binarySplit.h>
#include <classifiers/PartitionStatistics.h>

namespace ffactory {

/**
 * \def BinaryTreeNodeType
 * Describe node type by its position in tree (root, left or right)
 */
typedef enum
{
    NODE_ROOT   = 0,  //!< NODE_ROOT
	NODE_RIGHT  = 1,  //!< NODE_RIGHT
	NODE_LEFT   = 2   //!< NODE_LEFT
} BinaryTreeNodeType;

static const char * NodeTypeStrings[] = {
		"ROOT","RIGHT","LEFT"
};

static const char * getNodeTypeString(BinaryTreeNodeType t){
	return NodeTypeStrings[t];
}


class BaseTreeNode;
DEFINE_PTR(BaseTreeNode)

/**
 * Base data structure for containing of decision tree node information
 */
class BaseTreeNode: public BinarySplit {
private:
	BaseTreeNode * upNode;
	BaseTreeNodeUniquePtr  downNodeLeft; //  featureValue  <=  SplitValue
	BaseTreeNodeUniquePtr  downNodeRight; // featureValue  >   SplitValue
	IndexType id;
	IndexType depth;
	IndexType classLabel; // Used if node is terminal

	//IndexType numClasses;
	//IndexType numFeatures;
	std::unique_ptr< std::vector<IndexType> > indexes;
    PartitionStatistics statistics;
public:

	BaseTreeNode(IndexType NodeId = 0):
		upNode(NULL),
		downNodeLeft(nullptr),
		downNodeRight(nullptr),
		id(NodeId),
		depth(0),
		classLabel(0)
	{

	}

	void addIndex(IndexType idx){
		if(indexes == nullptr) indexes.reset(new std::vector<IndexType>);
		indexes->push_back(idx);
	}

	void clearIndexes(){
		indexes.reset();
	}

	IndexType getIndexesSize(){
		if(indexes != nullptr)
			return( indexes->size() );
		else
			return( 0 );
	}

	std::vector<IndexType>* getIndexes(){
		return(indexes.get());
	}

	BaseTreeNode& operator=(BinarySplit arg){
		this->setFeatureIndex( arg.getFeatureIndex() );
		this->setFeatureValue( arg.getFeatureValue() );
		this->setScore( arg.getScore() );
		return *this;
	}

	void setStatistics(PartitionStatistics& s){
		statistics = s;
	}

	virtual ~BaseTreeNode(){

	}

	PartitionStatistics* getStatistics(){
		return(&statistics);
	}

	/*
	newNode->setFeatureIndex( best->getFeatureIndex() );
	newNode->setFeatureValue( best->getFeatureValue() );
	newNode->setScore( best->getScore() );*/

	/*void initStatistics(Dataset* d = NULL, DataRanges* dr = NULL){
		if(numFeatures > 0 && numClasses > 1){
			std::vector<Sample> * data = NULL;
			if(d != NULL) data = d->getSamples();
			statistics.setNumFeatures(numFeatures);
			statistics.setNumClasses(numClasses);
			statistics.init(data, dr);
		}
	}*/

	void setRanges(DataRanges* const dr){
		statistics.setMinRanges(dr->minValues);
		statistics.setMaxRanges(dr->maxValues);
	}


	DataRanges* getRanges(){
		return(statistics.getRanges());
	}

	void attachToParent(BaseTreeNode * parent){
		this->setNumClasses(parent->getNumClasses());
		this->setNumFeatures(parent->getNumFeatures());
		setUpNode(parent);
		if(upNode == NULL){
			depth = 0; /* if it's root */
		} else {
			depth = upNode->getDepth() + 1;
		}
	}

	bool isTerminal(){
		return(downNodeRight == NULL && downNodeLeft == NULL);
	}

	bool isRoot(){
		return(upNode == NULL);
	}

	/**
	 *
	 * @return BinaryTreeNodeType
	 */
	BinaryTreeNodeType getNodeType(){
		if(isRoot()){
			return(NODE_ROOT);
		} else {
			if(this == upNode->getDownNodeLeft()){
				return(NODE_LEFT);
			} else {
				return(NODE_RIGHT);
			}
		}
	}

	BaseTreeNode* getChild(BinaryTreeNodeType type){
		if(type == NODE_ROOT){
			return(this->getUpNode());
		} else {
			if(type == NODE_LEFT){
				return( getDownNodeLeft() );
			} else {
				return( getDownNodeRight() );
			}
		}
	}

	unsigned int getClassLabel() const {
		return classLabel;
	}

	void setClassLabel(const unsigned int classLabel) {
		this->classLabel = classLabel;
	}

	unsigned int getDepth() const {
		return depth;
	}

	void setDepth(const unsigned int depth) {
		this->depth = depth;
	}

	unsigned int getId() {
		return id;
	}

	void setId(const unsigned int id) {
		this->id = id;
	}

	BaseTreeNode* getUpNode()  {
		return upNode;
	}

	void setUpNode( BaseTreeNode* const upNode) {
		this->upNode = upNode;
	}

	BaseTreeNode* getDownNodeLeft()  {
		return downNodeLeft.get();
	}

	void setDownNodeLeft(BaseTreeNodeUniquePtr downNodeLeft) {
		this->downNodeLeft = std::move(downNodeLeft);
	}

	BaseTreeNode* getDownNodeRight()  {
		return downNodeRight.get();
	}

	void setDownNodeRight(BaseTreeNodeUniquePtr downNodeRight) {
		this->downNodeRight = std::move(downNodeRight);
	}

	unsigned int getNumClasses()
	{
		return statistics.getNumClasses();
	}

	void setNumClasses(unsigned int numClasses)
	{
		this->statistics.setNumClasses(numClasses);
	}

	unsigned int getNumFeatures()
	{
		return statistics.getNumFeatures();
	}

	void setNumFeatures(unsigned int numFeatures)
	{
		this->statistics.setNumFeatures(numFeatures);
	}

	/**
	 * Get major class and set label
	 * @return
	 */
	IndexType computeLabel(){
		IndexType label = this->getStatistics()->getMajorClass();
		this->setClassLabel( label );
		return( label );
	}
};

} /* namespace ffactory */

#endif /* CLASSIFIERS_TREES_BASETREENODE_H_ */

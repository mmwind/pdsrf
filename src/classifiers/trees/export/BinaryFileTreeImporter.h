/*
 * BinaryFileTreeImporter.h
 *
 *  Created on: 22 авг. 2016 г.
 *      Author: lladmin
 */

#ifndef CLASSIFIERS_TREES_EXPORT_BINARYFILETREEIMPORTER_H_
#define CLASSIFIERS_TREES_EXPORT_BINARYFILETREEIMPORTER_H_

#include <classifiers/trees/export/BaseTreeImporter.h>

namespace ffactory {

	class BinaryFileTreeImporter: public BaseTreeImporter {
		public:
			void readTreeNode(BaseTreeNode *node, std::ifstream& in){
							BaseTree *T = getTree();
							DataType id;
							in.read((char*) (&id),sizeof(id));
							bool bt;
							in.read((char*) (&bt),sizeof(bt));

							if(node == NULL){
								node = T->addRoot();
							}

							node->setId(id);

							if(!bt){
								AttributeType aType;
								DataType fid;
								double   fval;
								DataType lid;
								DataType rid;
								in.read((char*) (&aType),  sizeof(aType));
								in.read((char*) (&fid),  sizeof(fid));
								in.read((char*) (&fval), sizeof(fval));
								in.read((char*) (&lid),  sizeof(lid));
								in.read((char*) (&rid),  sizeof(rid));
								node->setFeatureType(aType);
								node->setFeatureIndex(fid);
								node->setFeatureValue(fval);
								BaseTreeNodeUniquePtr lnode(new BaseTreeNode(lid));
								BaseTreeNodeUniquePtr rnode(new BaseTreeNode(rid));
								node->setDownNodeLeft(  std::move(lnode) );
								node->setDownNodeRight( std::move(rnode) );
								readTreeNode(node->getDownNodeLeft(),in);
								readTreeNode(node->getDownNodeRight(),in);
							} else {
								DataType cl;
								in.read((char*) (&cl), sizeof(cl));
								node->setClassLabel(cl);
							}
			}

			virtual void Import(){
				std::ifstream in(getFilename(), std::ios::in | std::ios::binary);
			    readTreeNode(NULL,in);
			    in.close();
			}
	};

} /* namespace ffactory */

#endif /* CLASSIFIERS_TREES_EXPORT_BINARYFILETREEIMPORTER_H_ */

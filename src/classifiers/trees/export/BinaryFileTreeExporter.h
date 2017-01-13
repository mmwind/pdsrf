/*
 * BinaryFileTreeExporter.h
 *
 *  Created on: 22 авг. 2016 г.
 *      Author: lladmin
 */

#ifndef CLASSIFIERS_TREES_EXPORT_BINARYFILETREEEXPORTER_H_
#define CLASSIFIERS_TREES_EXPORT_BINARYFILETREEEXPORTER_H_

#include <classifiers/trees/export/BaseTreeExporter.h>
#include <iostream>

namespace ffactory {

	template<class Matrix>
	void write_binary(std::ofstream out, const Matrix& matrix){
	    typename Matrix::Index rows=matrix.rows(), cols=matrix.cols();
	    out.write((char*) (&rows), sizeof(typename Matrix::Index));
	    out.write((char*) (&cols), sizeof(typename Matrix::Index));
	    out.write((char*) matrix.data(), rows*cols*sizeof(typename Matrix::Scalar) );
	}
	template<class Matrix>
	void read_binary(std::ifstream in, Matrix& matrix){
	    typename Matrix::Index rows=0, cols=0;
	    in.read((char*) (&rows),sizeof(typename Matrix::Index));
	    in.read((char*) (&cols),sizeof(typename Matrix::Index));
	    matrix.resize(rows, cols);
	    in.read( (char *) matrix.data() , rows*cols*sizeof(typename Matrix::Scalar) );
	}

	class BinaryFileTreeExporter: public BaseTreeExporter {
		public:
			BinaryFileTreeExporter(){

			}
			virtual ~BinaryFileTreeExporter();

			void writeTreeNode(BaseTreeNode *node, std::ofstream& out){
				DataType id = node->getId();
				out.write((char*) (&id), sizeof(id));
				uint8_t bt = (uint8_t)node->isTerminal();
				out.write((char*) (&bt),  sizeof(bt));

				if(!node->isTerminal()){
					AttributeType aType = node->getFeatureType();
					out.write((char*) (&aType),  sizeof(aType));
					DataType fid = node->getFeatureIndex();
					double   fval = node->getFeatureValue();
					DataType lid = node->getDownNodeLeft()->getId();
					DataType rid = node->getDownNodeRight()->getId();

					out.write((char*) (&fid),  sizeof(fid));
					out.write((char*) (&fval), sizeof(fval));
					out.write((char*) (&lid),  sizeof(lid));
					out.write((char*) (&rid),  sizeof(rid));
					writeTreeNode(node->getDownNodeLeft(),out);
					writeTreeNode(node->getDownNodeRight(),out);
				} else {
					DataType cl = node->getClassLabel();
					out.write((char*) (&cl), sizeof(cl));
				}
			}


			virtual void Export(){
				    std::ofstream out(getFilename(), std::ios::out | std::ios::binary | std::ios::trunc);
				    writeTreeNode(getTree()->getRoot(),out);
				    out.close();
			}
	};

} /* namespace ffactory */

#endif /* CLASSIFIERS_TREES_EXPORT_BINARYFILETREEEXPORTER_H_ */

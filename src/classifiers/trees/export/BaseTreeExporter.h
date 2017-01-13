/*
 * BaseTreeExporter.h
 *
 *  Created on: 29 февр. 2016 г.
 *      Author: lladmin
 */

#ifndef CLASSIFIERS_TREES_EXPORT_BASETREEEXPORTER_H_
#define CLASSIFIERS_TREES_EXPORT_BASETREEEXPORTER_H_

#include <Base.h>
#include <classifiers/trees/BaseTree.h>

namespace ffactory {

	class BaseTreeExporter: public Base {
		private:
			BaseTree* Tree;
			std::string filename;
		public:
			std::string getFilename(){
				return filename;
			}

			void setFilename(std::string& filename) {
				this->filename = filename;
			}

			BaseTree* getTree(){
				return Tree;
			}

			void setTree(BaseTree* tree) {
				Tree = tree;
			}

			virtual void Export() = 0;
	};

} /* namespace ffactory */

#endif /* CLASSIFIERS_TREES_EXPORT_BASETREEEXPORTER_H_ */

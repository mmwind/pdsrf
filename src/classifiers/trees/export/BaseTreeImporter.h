/*
 * BaseTreeImporter.h
 *
 *  Created on: 22 авг. 2016 г.
 *      Author: lladmin
 */

#ifndef CLASSIFIERS_TREES_EXPORT_BASETREEIMPORTER_H_
#define CLASSIFIERS_TREES_EXPORT_BASETREEIMPORTER_H_

#include <Base.h>
#include <classifiers/trees/BaseTree.h>

namespace ffactory {

	class BaseTreeImporter: public Base {
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

			virtual void Import() = 0;
	};

} /* namespace ffactory */

#endif /* CLASSIFIERS_TREES_EXPORT_BASETREEIMPORTER_H_ */

/*
 * PartykitTreeExporter.h
 *
 *  Created on: 29 февр. 2016 г.
 *      Author: lladmin
 */

#ifndef CLASSIFIERS_TREES_EXPORT_PARTYKITTREEEXPORTER_H_
#define CLASSIFIERS_TREES_EXPORT_PARTYKITTREEEXPORTER_H_

#include <iostream>
#include <fstream>
#include <classifiers/trees/export/BaseTreeExporter.h>

namespace ffactory {

	class PartykitTreeExporter: public BaseTreeExporter {
		private:
			void treeSave(BaseTreeNode* node, std::ofstream& file);
			void saveAsPartykitScript(BaseTreeNode* rootNode, std::string filename);
		public:
			virtual void Export();
	};

} /* namespace ffactory */

#endif /* CLASSIFIERS_TREES_EXPORT_PARTYKITTREEEXPORTER_H_ */

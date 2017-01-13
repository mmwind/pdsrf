/*
 * PartykitTreeExporter.cpp
 *
 *  Created on: 29 февр. 2016 г.
 *      Author: lladmin
 */

#include <classifiers/trees/export/PartykitTreeExporter.h>

namespace ffactory {


	void PartykitTreeExporter::treeSave(BaseTreeNode* node, std::ofstream& file){
		if(!node) return;
		std::stringstream ss;
		ss << "\t list(id = ";
		ss << (node->getId()+1) << "L";
		if(!node->isTerminal()){
			ss << ", split = partysplit(varid = " << (node->getFeatureIndex() + 1) << "L, breaks = " << node->getFeatureValue() << "), ";
			ss << "kids = c(" <<  (node->getDownNodeLeft()->getId() + 1) <<  "," << (node->getDownNodeRight()->getId() + 1) << ")";
		}
			ss << "),";

		ss << std::endl;

		std::copy(std::istreambuf_iterator<char>(ss),
				std::istreambuf_iterator<char>(),
				std::ostreambuf_iterator<char>(file));

		treeSave(node->getDownNodeRight(),file);
		treeSave(node->getDownNodeLeft(), file);
	}

	/**
	 * Tree export function
	 * \todo Must be represented as class TreeExporter
	 * @param rootNode
	 * @param filename
	 */
	void PartykitTreeExporter::saveAsPartykitScript(BaseTreeNode* rootNode, std::string filename){
				std::ofstream file;
				file.open(filename.c_str());
				if (!file) {
					THROW("Could not open input file " + filename);
				}
				file << std::endl << "## ForestFactory generated R script" << std::endl << std::endl;
				file << "nodelist <- list("<< std::endl;
				treeSave(rootNode, file);
				file << ")"<< std::endl;
				file << "## convert to a recursive structure" << std::endl << "node <- as.partynode(nodelist)"<< std::endl;
				file.close();
	}

	void PartykitTreeExporter::Export(){
		saveAsPartykitScript(this->getTree()->getRoot(), this->getFilename());
	}
} /* namespace ffactory */

/*
 * BinaryEigenFileWriter.cpp
 *
 *  Created on: 31 янв. 2016 г.
 *      Author: lladmin
 */

#include <init.h>
#include <utils/ProgressBar.h>
#include <data/fileFormats/BinaryEigenFileWriter.h>
#include <data/data.h>

namespace ffactory {
	void BinaryEigenFileWriter::write(){
		DataMatrix data( getDataset()->getNumSamples(), getDataset()->getNumFeatures() + 2);
		INFO("data " << data.rows() << " rows, "<< data.cols() << " cols ");
		INFO("sample " << getDataset()->getSample(0)->getVector()->size());
		INFO("samples " << getDataset()->getNumSamples());

		ProgressBar p(0,getDataset()->getNumSamples());
		for(IndexType i=0; i< getDataset()->getNumSamples(); i++){
			DataVector v;
			Sample *s = getDataset()->getSample(i);
			v = (*s->getVector());
			v.conservativeResize(v.size() + 2);
			v(v.size() - 2) = s->getW();
			v(v.size() - 1) = s->getY();
			data.row(i) = v;
			if(verbose)
				p.show(i);
		}
		writeBinaryMatrix(getFilename().c_str(),data);
		if(verbose)
			p.show(getDataset()->getNumSamples());
	}

} /* namespace ffactory */

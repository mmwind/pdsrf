/*
 * splitQualityMeasurer.h
 *
 *  Created on: 8 дек. 2015 г.
 *      Author: lladmin
 */

#ifndef CLASSIFIERS_TREES_SPLITS_QUALITYMEASURER_SPLITQUALITYMEASURERFACTORY_H_
#define CLASSIFIERS_TREES_SPLITS_QUALITYMEASURER_SPLITQUALITYMEASURERFACTORY_H_

#include <classifiers/trees/splits/qualityMeasurer/baseSplitQualityMeasurer.h>
#include <classifiers/trees/splits/qualityMeasurer/simpleSplitQualityMeasurer.h>
#include <utils/patterns/AbstractFactory.h>

namespace ffactory {


	class SplitQualityMeasurerFactory: public AbstractFactory<BaseSplitQualityMeasurer>{
			virtual void Register(){
				add<SimpleSplitQualityMeasurer>("simple");

			}
	};

}


#endif /* CLASSIFIERS_TREES_SPLITS_QUALITYMEASURER_SPLITQUALITYMEASURERFACTORY_H_ */

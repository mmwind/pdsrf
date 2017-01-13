/*
 * ProgressBar.h
 *
 *  Created on: 31 янв. 2016 г.
 *      Author: lladmin
 */

#ifndef UTILS_PROGRESSBAR_H_
#define UTILS_PROGRESSBAR_H_

#include <data/data.h>
#include <Base.h>

namespace ffactory {

	class ProgressBar: public Base {
		private:
			DataType min;
			DataType max;
			int oldpercents;
			void print(int percents);
		public:
			ProgressBar(DataType _min, DataType _max);
			void show(DataType value);
	};
} /* namespace ffactory */

#endif /* UTILS_PROGRESSBAR_H_ */

/*
 * dataset_test.cpp
 *
 *  Created on: 17 нояб. 2015 г.
 *      Author: llproger
 */
#include <data/Dataset.h>
#include <test.h>


// Тестовый класс для тестирования Dataset.
class DatasetTest : public ::testing::Test {
 protected:
  // Можете удалить любую или все из функций ниже, если они пустые.
	ffactory::Dataset d;

  DatasetTest() {
    // Здесь можно подготовить тестовые данные для каждого теста.
		d.setNumClasses(2);
		d.setNumFeatures(2);
		d.initStatistics();

		ffactory::Sample s(d.getNumFeatures());
		s.resize(d.getNumFeatures());

	/* Test Samples

		5##?#####
		4###1##1#
		3##0##1##
		2########
		1#0#0####
		0########
		 01234567
	*/

		// 0
		s.setId(1);
		s.setY(0);
		s.setValue(0,1);
		s.setValue(1,1);
		d.add(s);

		s.setId(2);
		s.setY(0);
		s.setValue(0,2);
		s.setValue(1,3);
		d.add(s);

		s.setId(3);
		s.setY(0);
		s.setValue(0,3);
		s.setValue(1,1);
		d.add(s);

		// 1
		s.setId(4);
		s.setY(1);
		s.setValue(0,5);
		s.setValue(1,3);
		d.add(s);

		s.setId(5);
		s.setY(1);
		s.setValue(0,6);
		s.setValue(1,4);
		d.add(s);

		// Outlier
		s.setId(6);
		s.setY(1);
		s.setValue(0,4);//3
		s.setValue(1,4);
		d.add(s);

		/*s.setId(6);
		s.setY(1);
		s.setValue(0,2);
		s.setValue(1,5);*/

  }

  virtual ~DatasetTest() {
    // Здесь производится чистка мусора. Данная функция не должна
    // генерировать исключений.
  }

  // Если конструктор или деструктор не подходят вам для настройки
  // тестовых данных и чистки мусора, то можете использовать следующие
  // методы:

  virtual void SetUp() {
    // Данная функция вызывается сразу после конструктора (до теста).
  }

  virtual void TearDown() {
    // Данная функция вызывается сразу после теста (до деструктора).
  }

  // Объекты, объявленные тут, могут быть использованы во всем тестовом
  // классе Dataset.
};


TEST_F(DatasetTest, numberOfClassesAndSamples) {
    EXPECT_EQ(2, d.getNumClasses());
    EXPECT_EQ(6, d.getNumSamples());
}

TEST_F(DatasetTest, ClassSamplesNumber) {
    EXPECT_EQ(3, d.getStatistics()->getPointsByClass(0));
    EXPECT_EQ(3, d.getStatistics()->getPointsByClass(1));
}

TEST_F(DatasetTest, push_ClassSamplesNumber) {
	ffactory::Dataset data;
	data.setNumFeatures(2);
	data.setNumClasses(3);
	data.initStatistics();
		int count[3] = { 7, 13, 17 };
		for(int i=0; i< 3; i++){
			for (int j=0; j< count[i]; j++) {
				ffactory::Sample s(data.getNumFeatures());
				s.setY(i);
				data.add(s);
			}
		}

	    EXPECT_EQ(7, data.getStatistics()->getPointsByClass(0));
	    EXPECT_EQ(13, data.getStatistics()->getPointsByClass(1));
	    EXPECT_EQ(17, data.getStatistics()->getPointsByClass(2));
}

TEST_F(DatasetTest, computeClassSamplesNumber) {
	ffactory::Dataset data;
	data.setNumFeatures(2);
	data.setNumClasses(3);
	data.initStatistics();

		int count[3] = { 7, 13, 17 };
		for(int i=0; i< 3; i++){
			for (int j=0; j< count[i]; j++) {
				ffactory::Sample s(data.getNumFeatures());
				s.setY(i);
				data.add(s);
			}
		}

	data.computeStatistics();
    EXPECT_EQ(7, data.getStatistics()->getPointsByClass(0));
    EXPECT_EQ(13, data.getStatistics()->getPointsByClass(1));
    EXPECT_EQ(17, data.getStatistics()->getPointsByClass(2));
}


TEST_F(DatasetTest, calculateRanges) {
	d.calculateRanges();
	DataVector min(2);
	min << 1,1;
	DataVector minrng = *d.getStatistics()->getMinRanges();
	ASSERT_TRUE(&minrng != NULL);
	EIGEN_EQ(minrng, min);

	DataVector max(2);
	max << 6,4;
	DataVector maxrng = *d.getStatistics()->getMaxRanges();
	ASSERT_TRUE(&maxrng != NULL);
	EIGEN_EQ(maxrng, max);
}




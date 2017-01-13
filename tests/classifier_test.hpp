/*
 * dataset_test.cpp
 *
 *  Created on: 17 нояб. 2015 г.
 *      Author: llproger
 */

#ifndef CLASSIFIER_TEST_H_
#define CLASSIFIER_TEST_H_

#include <classifiers/BaseClassifier.h>
#include <data/Dataset.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <utils/gtest_macros.h>

#include <data/fileFormats/CsvFileReader.h>

// Тестовый класс для тестирования Dataset.
class ClassifierTest : public ::testing::Test {
 protected:
  // Можете удалить любую или все из функций ниже, если они пустые.
	ffactory::Dataset d;

	ClassifierTest() {
    // Здесь можно подготовить тестовые данные для каждого теста.
		// Read dataset
		ffactory::CsvFileReader r;
				r.setDataset(&d);
				r.setFilename("test.csv");
				r.setDelimiter(';');
				r.read();
    }

  virtual ~ClassifierTest() {
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

TEST_F(ClassifierTest, DatasetIsLoaded) {
    EXPECT_EQ(3, d.getNumClasses());
    EXPECT_EQ(150, d.getNumSamples());
}

#endif /* CLASSIFIER_TEST_H_ */

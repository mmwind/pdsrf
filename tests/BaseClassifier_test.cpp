#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "classifier_test.hpp"
#include <classifiers/errorMeasures/MissclassificationErrorMeasure.h>

namespace ffactory {
	class FakeBaseClassifier: public BaseClassifier{
		public:
				virtual double train(Dataset *d){
					return(1.0);
				}

				virtual DataVectorUniquePtr predictClassProb(Sample *sample){
					this->check();
					DataVectorUniquePtr ret(new DataVector(this->getNumClasses()));
					ret.get()->fill(0);
					( *(ret.get()) )(0) = 1;
					return(std::move( ret ));
				}
		};


	class BaseClassifierTest: public ::testing::Test{
	protected:
		FakeBaseClassifier baseClassifier;
		BaseClassifierTest(){
			baseClassifier.setNumClasses(3);
			baseClassifier.setNumFeatures(2);
			BaseErrorMeasureUniquePtr em(new MissclassificationErrorMeasure);
			baseClassifier.setErrorMeasure(std::move(em));
		}

		virtual ~BaseClassifierTest() {
		    // Здесь производится чистка мусора. Данная функция не должна
		    // генерировать исключений.
		}

		virtual void SetUp() {
			// Данная функция вызывается сразу после конструктора (до теста).
		}

		virtual void TearDown() {
			// Данная функция вызывается сразу после теста (до деструктора).
		}
	};

	TEST_F(BaseClassifierTest, setTrainDataset) {
		FakeBaseClassifier cl;
		DatasetUniquePtr d(new Dataset);
		d->setNumClasses(3);
		d->setNumFeatures(2);
		Sample s(d->getNumFeatures());
		d->push(s);
		d->calculateRanges();
		cl.setTrainDataset(d.get());

		EXPECT_EQ(3, cl.getNumClasses() );
		EXPECT_EQ(2, cl.getNumFeatures() );
		EXPECT_EQ(1, cl.getNumTrainSamples() );
	}


	TEST_F(BaseClassifierTest, getConfidence) {
		SampleUniquePtr  s(new  Sample);
		Prediction prediction = baseClassifier.predict( s.get() );
		DataType val = prediction.getConfidence(0)(0);
		EXPECT_EQ( val , 1);
		val = prediction.getConfidence(0)(1);
		EXPECT_EQ( val , 0);
		/*EXPECT_EQ(3, d.getNumClasses());
		EXPECT_EQ(150, d.getNumSamples());*/
	}
}

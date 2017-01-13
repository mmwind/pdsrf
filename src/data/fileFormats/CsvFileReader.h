/*
 * CsvFileReader.h
 *
 *  Created on: 26 окт. 2015 г.
 *      Author: llproger
 */

#ifndef DATA_FILEFORMATS_CSVFILEREADER_H_
#define DATA_FILEFORMATS_CSVFILEREADER_H_


#include <data/Dataset.h>
#include <data/fileFormats/BaseFileReader.h>
#include <init.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <istream>

namespace ffactory {

/**
 * CSV-file support class
 * Restrictions: only features columns and one label format, header is required.
 */

class CsvFileReader: public BaseFileReader {
private:
	bool haveHeader;
	std::vector<std::string> header;
	char delimiter;

	typedef std::pair<DataVector,DataType> DataPair;

	DataPair readRowElements(std::istream &in)
		{
			IndexType numCols = this->getDataset()->getNumFeatures() - 1;
			DataType Y = 0;
			IndexType idx = 0;
			Eigen::VectorXd X(this->getDataset()->getNumFeatures());
			std::stringstream ss;


			while(in.good())
			{
				char c = in.get();
				if (c==delimiter)
				{
					double d = 0;
					ss >> d;
					ss.clear();//clear any bits set
					ss.str(std::string());
					if(idx <= numCols ){
						X(idx++) = d;
					} else {
						Y = d;
						return(DataPair(X,Y));
					}
				} else {
					ss << c;
				}
			}

			ss >> Y;
			return(DataPair(X,Y));
	}


	std::vector<std::string> readRowElementsStr(std::istream &in)
	{

		std::vector<std::string> rowElements;
	    std::stringstream ss;

	    bool quoted = false;


	    while(in.good())
	    {
	        char c = in.get();
	        if(c == -1) {
	        	if(ss.str()!="") rowElements.push_back(ss.str());
	        	return (rowElements);
	        }

	        if( c == '"' ){
				if (!quoted)
				{
					quoted=true;
				}
				else
				{
					if ( in.peek() == '"')
					{
						ss << (char)in.get();
					}
					else
					{
						quoted=false;
					}
				}
	        }
	        else
	        if (!quoted)
	        {
				if (c==delimiter)
				{
					rowElements.push_back(ss.str());
					ss.str("");
				}
				else {
					if ( c=='\r' || c=='\n' )
					{
						if(in.peek()=='\n') { in.get(); }
						rowElements.push_back(ss.str());
						return (rowElements);
					}
					else
					{
						ss << c;
					}
				}
	        }
	        else
	        {
	            ss << c;
	        }
	    }
	    return(rowElements);
	}

	DataPair readRowToDataVector(std::string &line)
	{
	    std::stringstream ss(line);
	    return (readRowElements(ss));
	}

	std::vector<std::string> readRowToStringVector(std::string &line)
	{
	    std::stringstream ss(line);
	    return readRowElementsStr(ss);
	}

public:
	CsvFileReader(){
		delimiter = ';';
		this->haveHeader = true;
		this->setHaveHeader(true);
	}

	virtual void read(){
		if(getDataset() == NULL){
			THROW("Dataset must be setted.");
		}

		std::ifstream file;
		file.open(getFilename().c_str());
		if (!file) {
			THROW("Could not open input file " + getFilename());
		}

		// Read header (required)
		if ( file.good() ){
				std::string s;
				std::getline( file, s , '\n');
				header = readRowToStringVector(s);
				for(IndexType i=0; i<(header.size() - 1); i++ )
					getDataset()->addAttribute(header[i],ATTR_CONTINUOUS);
				//getDataset()->setNumFeatures(header.size() - 1);
		}
		getDataset()->setNumClasses(2); /** \todo NumClasses should be set before add */

		IndexType nClasses = 0;
		std::vector<DataPair> data;
		while(!file.eof()){
			std::string s;
			std::getline( file, s , '\n');
				DataPair d = readRowToDataVector(s);
				data.push_back(d);
				if(d.second > nClasses) nClasses = d.second;
		}
		file.close();

		getDataset()->setNumClasses(nClasses + 1);
		getDataset()->initStatistics();

		// push data to Dataset object
		unsigned int id = 0;
		for(IndexType i=0; i< data.size(); ++i){
			DataPair * d = &data[i];
			Sample sample;
			sample.setVector(d->first);
			sample.setId(id++);
			sample.setW(1.0);
			sample.setY(d->second);
			getDataset()->add(sample);
		}

		//getDataset()->calculateRanges();
	}

	bool isHaveHeader() const
	{
		return haveHeader;
	}

	void setHaveHeader(bool haveHeader)
	{
		this->haveHeader = haveHeader;
	}

	char getDelimiter() const
	{
		return delimiter;
	}

	void setDelimiter(char delimiter)
	{
		this->delimiter = delimiter;
	}
};

} /* namespace ffactory */

#endif /* DATA_FILEFORMATS_CSVFILEREADER_H_ */

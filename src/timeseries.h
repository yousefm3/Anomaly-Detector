
#ifndef TIMESERIES_H_
#define TIMESERIES_H_
#include <iostream>
#include <fstream>
#include<map>
#include <bits/stdc++.h>

using namespace std;

class TimeSeries{
	map<string,vector<float>> timeseries;
	vector <string> attributes; 
    int size;

public:

	TimeSeries(const char* CSVfileName){
		 size = 0;
		 ifstream file(CSVfileName);
		 string line;
		 //check the attributes(first line)
		 getline(file, line);
		 stringstream l1(line);
		 bool check = true;
		 while(getline(l1, line, ',')) {
            vector <float> st;
            attributes.push_back(line);
			timeseries[line] = st;
			size++;
		 }
		 while(!file.eof()){
			getline(file, line);
			int i = 0;
		   stringstream l1(line);
            while(getline(l1,line,',')) {
				timeseries[attributes[i]].push_back(stof(line));
				i++;
			}
       }
	  file.close();
	}
	 int getSize()const{
		return size;
	}
   vector<string> gettAtts()const {
	   return attributes;
   }
     map<string,vector<float>> getTs()const {
	   return timeseries;
   }
const vector<float>& getAttributeData(string name)const{
		return timeseries.at(name);
	}
	TimeSeries(){

	}
};



#endif /* TIMESERIES_H_ */

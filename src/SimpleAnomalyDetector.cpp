
#include "SimpleAnomalyDetector.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() {
	// TODO Auto-generated constructor stub

}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
	// TODO Auto-generated destructor stub
}
/*
return: the max deviation between point and the line
*/
float maxD(float* x, float* y, int size, Line l) {
	float max = 0;
	float dev1 = 0;
    for(int i = 0; i < size; i++) {
		Point p = Point(x[i],y[i]);
		dev1 = dev(p,l);
		if(dev1 > max) max = dev1;
	}
	return max;
}
void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts){
	Line l;
	float dev;
	int c = 0;
	for(int i = 0; i < ts.getSize(); i++) {
		float maxCurr = 0;
		map<string, vector<float>> ts1 = ts.getTs();
		string f1 = ts.gettAtts().at(i);
		//the i vector
		vector<float> v1 =ts.getAttributeData(f1);
		for(int j = i + 1; j< ts.getSize(); j++) {
			string f2 = ts.gettAtts().at(j);
			//the j vector
		vector<float> v2=ts.getAttributeData(f2);
		//&v1[0] pointer to the first element at v1
		   	Point* points[v1.size()];
			for (int k = 0 ; k < v1.size();k++){
				points[k] = new Point(v1[k],v2[k]);
			}
			float p = pearson(&v1[0], &v2[0], v1.size());
			if( p < 0) {
				p*= -1;
			}
		   if(p > maxCurr) {
			maxCurr = p;
			c = j;
			l = linear_reg(points, v1.size());
			dev = maxD(&v1[0],&v2[0],v1.size(),l);
		  }
		}
		if (maxCurr > 0.95){
			correlatedFeatures c1;
			c1.feature1 = f1;
			c1.feature2 = ts.gettAtts().at(c);
			c1.corrlation = maxCurr;
			c1.lin_reg = l;
			c1.threshold = dev * 1.1;
			cf.push_back(c1);
		}
		if (maxCurr>0.5 && maxCurr < 0.95){
			correlatedFeatures c1;
			c1.feature1 = f1;
			c1.feature2 = ts.gettAtts().at(c);
			c1.corrlation = maxCurr;
			c1.lin_reg = l;
			c1.threshold = dev * 1.1;
			Point* ps2[v1.size()];
			vector <float> v2 = ts.getAttributeData(c1.feature2);
            for(int a=0;a<v1.size();a++)
                ps2[a]=new Point(v1[a],v2[a]);
			c1.circle = findMinCircle(ps2, v1.size());
			cf.push_back(c1);
		}
	}
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
	vector<AnomalyReport> ar;
	//check for each pair of vectors in cf
	for (int i = 0 ; i < cf.size() ; i++){
		float cur = cf.at(i).corrlation;
		for (int j = i + 1 ; j<ts.getAttributeData(cf.at(i).feature1).size(); j++){
			Point p = Point(ts.getAttributeData(cf.at(i).feature1)[j], ts.getAttributeData(cf.at(i).feature2)[j]);
			if (dev(p, cf.at(i).lin_reg) > cf.at(i).threshold){
				string descreption = cf.at(i).feature1 + "-" + cf.at(i).feature2;
				long timestep = j + 1;
				AnomalyReport a = AnomalyReport(descreption,timestep);
				ar.push_back(a);
			}
			if((dev(p, cf.at(i).lin_reg) < cf.at(i).threshold) && dev(p, cf.at(i).lin_reg) > 0.5){
			    float d = distance(cf.at(i).circle.center, p);
                if (d >= cf.at(i).circle.radius+1){
				string descreption = cf.at(i).feature1 + "-" + cf.at(i).feature2;
				long timestep = j + 1;
				AnomalyReport a = AnomalyReport(descreption,timestep);
				ar.push_back(a);
				}
			}
		}
	}
	return ar;
}


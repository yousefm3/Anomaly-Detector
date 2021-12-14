

#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_

#include "SimpleAnomalyDetector.h"

class HybridAnomalyDetector:public SimpleAnomalyDetector {

public:

	HybridAnomalyDetector();

    virtual void learnNormal(const TimeSeries& ts);

    virtual vector<AnomalyReport> detect(const TimeSeries& ts);

	virtual ~HybridAnomalyDetector();

};

#endif /* HYBRIDANOMALYDETECTOR_H_ */

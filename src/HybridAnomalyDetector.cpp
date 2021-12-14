#include "HybridAnomalyDetector.h"

HybridAnomalyDetector::HybridAnomalyDetector() {

}

HybridAnomalyDetector::~HybridAnomalyDetector() {
}

void HybridAnomalyDetector::learnNormal(const TimeSeries& ts) {
    SimpleAnomalyDetector::learnNormal(ts);
}

vector<AnomalyReport> HybridAnomalyDetector::detect(const TimeSeries& ts) {
    return SimpleAnomalyDetector::detect(ts);
}
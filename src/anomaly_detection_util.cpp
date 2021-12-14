/*
 * animaly_detection_util.cpp
 *
 * Author: \
 * Ragheb ghazi 314892506
 * Mohamed yousef 211668975
 */

#include <math.h>
#include "anomaly_detection_util.h"
#include <cstdlib>

float avg(float* x, int size) {
	float sum = 0;
	for (int i = 0; i < size; i++) {
		sum += x[i];
	};
	float Avg = sum / size;
	return (Avg);
}

// returns the variance of X and Y
float var(float* x, int size) {
	float sum = 0, sumN, u;
	for (int i = 0; i < size; i++) {
		sum += (x[i] * x[i]);
	};
	sumN = sum / size;
	u = avg(x, size);
	return (sumN - u * u);
}

// returns the covariance of X and Y
float cov(float* x, float* y, int size) {
	float uX, uY, uXY;
	uX = avg(x, size);
	uY = avg(y, size);
	float XY[size];

	for (int i = 0; i < size; i++) {
		XY[i] = x[i] * y[i];
	}
	uXY = avg(XY, size);
	return (uXY - uX * uY);
}


// returns the Pearson correlation coefficient of X and Y
float pearson(float* x, float* y, int size) {
	return cov(x, y, size) / (sqrt(var(x, size)) * sqrt(var(y, size)));
}

// performs a linear regression and returns the line equation
Line linear_reg(Point** points, int size) {
	float x1[size];
	float y1[size];
	for (int i = 0; i < size; i++) {
		x1[i] = points[i]->x;
		y1[i] = points[i]->y;
	}
	float a = cov(x1, y1, size) / var(x1, size);
	float avgX, avgY;
	avgX = avg(x1, size);
	avgY = avg(y1, size);
	float b = avgY - a * avgX;
	return Line(a, b);
}

// returns the deviation between point p and the line equation of the points
float dev(Point p, Point** points, int size) {
	Line l = linear_reg(points, size);
	float y = l.a * p.x + l.b;
	return (abs(y - p.y));
}

// returns the deviation between point p and the line
float dev(Point p, Line l) {
	float x = p.y - l.f(p.x);
	if (x < 0) {
		x *= -1;
	}
	return x;
}
float distance(const Point &a, const Point &b) {
	float d = pow(a.x - b.x, 2) + pow(a.y - b.y, 2);
    return sqrt(d);
}


/*
 * minCircle.cpp
 *
 * Author:
 * Ragheb ghazi 314892506
 * Mohamed yousef 211668975
 */
#include <algorithm>
#include <math.h>
#include <vector>
#include "minCircle.h"

Circle circleFrom2Points(const Point &a, const Point &b) {
    // Setting the center to be the middle point of A and B
    float midPointX = (a.x + b.x) / 2;
    float midPointY = (a.y + b.y) / 2;
    Point point = {midPointX, midPointY};
    float radius = distance(a, b) / 2;
    return {point, radius};
}

Circle circleFrom3Points(float x1, float y1,float x2, float y2,float x3,float y3) {
    // xi is pointi.x, yi is pointi.y
    float A = x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2);
    float sqr1 = x1 * x1 + y1 * y1;
    float sqr2 = x2 * x2 + y2 * y2;
    float sqr3 = x3 * x3 + y3 * y3;
    float B = sqr1 * (x2 * y3 - x3 * y2) + sqr2 * (x3 * y1 - x1 * y3) + sqr3 * (x1 * y2 - y1 * x2);
    float X = (sqr1 * (y2 - y3) + sqr2 * (y3 - y1) + sqr3 * (y1 - y2)) / 2;
    float Y = (sqr1 * (x3 - x2) + sqr2 * (x1 - x3) + sqr3 * (x2 - x1)) / 2;
    float a = X / A; 
    float b = Y / A;
    float radius = sqrt(A * B + X * X + Y * Y) / fabs(A);
    Point center = Point(a , b);
return {center, radius};
}

// checking if the given points is inside the circle
int allInside(const Circle &c, const vector<Point> &points) {
    for (const Point &point : points){
        //if point is inside the circle
        float d = distance(c.center, point);
        if (d <= c.radius+1)
            return 0;
    }
    return 1;
}
Circle trivialCircle(vector<Point> &pointsVector) {
    int size = pointsVector.size();
    Point &begin = pointsVector[0];
    Point &mid = pointsVector[1];
    Point &end = pointsVector[2];
    if (size == 1) {
        return {begin, 0};
    } else if (size == 2) {
        return circleFrom2Points(begin, mid);
    } else if (pointsVector.empty()) {
        return {{0, 0}, 0};
    }
    // current circle
    Circle current = circleFrom3Points(begin.x,begin.y, mid.x,mid.y,end.x, end.y);
    // setting the minCircle as the current circle
    Circle minimumCircle = current;
    Circle c1 = circleFrom2Points(begin, mid);
    Circle c2 = circleFrom2Points(begin, end);
    Circle c3 = circleFrom2Points(mid, end);
    if (allInside(c1, pointsVector)==1 && c1.radius < current.radius)
    // change minCircle  to c1
        minimumCircle = c1;

    if (allInside(c2, pointsVector)==1 && c2.radius < current.radius)
    // change minCircle to c2
        minimumCircle = c2;

    if (allInside(c3, pointsVector)==1 && c3.radius < current.radius)
    // change minCircle to c3
        minimumCircle = c3;
    return minimumCircle;
}

Circle circleHelper(vector<Point> &pointsVector, vector<Point> r, int size) {
    // trivial min circle
    if (size == 0 || r.size() == 3) {
        return trivialCircle(r);
    }
    // set index parameter as a random number:
    int index = rand() % size;
    // pick a random point
    Point p = pointsVector[index];
    //swapping the point with point at index size -1
    swap(pointsVector[index], pointsVector[size - 1]);
    Circle c = circleHelper(pointsVector, r, size - 1);
    float d = distance(c.center, p);
    // if the point is inside the circle
    if (d <= c.radius+1){ 
        return c;
    }
    r.push_back(p);
    Circle res = circleHelper(pointsVector, r, size - 1);
    return res;
}

Circle findMinCircle(Point **points, size_t size) {
    vector<Point> vec;
    for (size_t i = 0; i < size; i++)
        vec.push_back(*points[i]);
    vector<Point> vec1;
    Circle minCircle = circleHelper(vec, vec1, vec.size());
    return minCircle;
}

#ifndef CAMATHFUNCS_H
#define CAMATHFUNCS_H

#include <algorithm>

//double PointsDistance(double* p1, double* p2) {
//	double x1 = p1[0];
//	double x2 = p2[0];
//	double y1 = p1[1];
//	double y2 = p2[1];
//	double z1 = p1[2];
//	double z2 = p2[2];
//
//	double d[] = { abs(x1 - x2), abs(y1 - y2), abs(z1 - z2) };
//	if (d[0] < d[1]) std::swap(d[0], d[1]);
//	if (d[0] < d[2]) std::swap(d[0], d[2]);
//	double distance = d[0] * sqrt(1.0 + d[1] / d[0] + d[2] / d[0]);
//
//	return distance;
//}

double PointsDistance(float* p1, float* p2);

#endif
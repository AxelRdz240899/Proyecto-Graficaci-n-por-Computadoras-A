#pragma once
#include <armadillo>
#include "VerticeBezier.h"

class Bezier {
private:
	float dt = 0.05f;
	arma::dmat Mb;
	VerticeBezier p1, p2, p3, p4;
public:
	Bezier();
	Bezier(VerticeBezier v1, VerticeBezier v2, VerticeBezier v3, VerticeBezier v4);
	std::vector<VerticeBezier> vcurve;
	void calc_Curve();
	void setVertex(VerticeBezier v1, VerticeBezier v2, VerticeBezier v3, VerticeBezier v4);
};

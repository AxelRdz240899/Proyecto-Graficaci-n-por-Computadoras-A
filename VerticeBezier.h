#pragma once
#include <armadillo>

class VerticeBezier{
private:
	arma::dvec v;

public:
	VerticeBezier();
	VerticeBezier(double x, double y, double z);
	void printf();
	arma::dvec GetVertice();
	void set_Vertice(arma::dvec _v);
	void setV(double x, double y, double z);
	double Valores(int Index);
};
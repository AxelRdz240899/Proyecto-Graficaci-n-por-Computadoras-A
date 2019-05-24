#pragma once
#include <armadillo>
class Vertex 
{
private:
	double x, y, z;
public:
	arma::dvec Vertice;
	~Vertex();
	Vertex(double vx, double vy, double vz);
	Vertex();
	void SetVertice(arma::dvec V);
	arma::drowvec get_value();
	double getX();
	double getY();
	double getZ();
	void ToString();
};

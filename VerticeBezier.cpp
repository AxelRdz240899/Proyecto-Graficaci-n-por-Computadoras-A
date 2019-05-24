#include "VerticeBezier.h"



VerticeBezier::VerticeBezier() {
	v = { 0,0,0 };
}

VerticeBezier::VerticeBezier(double x, double y, double z) {
	v = { x, y, z };
}

void VerticeBezier::printf() {
	v.print("Vertice: ");
}

arma::dvec VerticeBezier::GetVertice() {
	return v;
}

void VerticeBezier::set_Vertice(arma::dvec a) {
	v = a;
}

void VerticeBezier::setV(double x, double y, double z) {
	v = { x,y,z };
}
double VerticeBezier::Valores(int index) {
	return v[index];
}
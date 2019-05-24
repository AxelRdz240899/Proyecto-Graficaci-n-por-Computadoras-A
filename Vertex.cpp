#include "Vertex.h"
#include <iostream>
#include <string>
#include <armadillo>
#pragma once

using namespace std;

Vertex::Vertex(double vx, double vy, double vz) {
	x = vx;
	y = vy;
	z = vz;
	Vertice = {vx,vy,vz,1.0f};
}

Vertex::Vertex() {

}
double Vertex::getX() {
	return Vertice[0];
}

double Vertex::getY() {
	return Vertice[1];
}

double Vertex::getZ() {
	return Vertice[2];
}

void Vertex::SetVertice(arma::dvec V) {
	Vertice = { V[0], V[1], V[2] , 1.0 };
	x = Vertice[0];
	y = Vertice[1];
	z = Vertice[2];
}
Vertex::~Vertex()
{
}

arma::drowvec Vertex::get_value() {
	arma::drowvec Aux = {Vertice[0],Vertice[1],Vertice[2] };
	return Aux;
}
void Vertex::ToString() 
{
	cout << "x: " + std::to_string(Vertice[0]) + " y: " + std::to_string(Vertice[1]) + " z: " + std::to_string(Vertice[2]) << endl;
}
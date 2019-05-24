#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <list>
#include <vector>
#include "Vertex.h"
#include <armadillo>
#pragma once
using namespace std;

class Face
{
public:
	Face(vector <Vertex> LI, int N, arma::irowvec C);
	vector <Vertex> Vertices;
	int Numero;
	float R, G, B;
	arma::irowvec Color;
	bool Visible;
	void ToString();
	void SetColor(arma::irowvec C);
	void setRGB(float Rojo, float Verde, float Azul);
	~Face();
};


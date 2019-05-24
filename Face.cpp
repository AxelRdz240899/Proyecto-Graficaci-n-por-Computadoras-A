#include "Face.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <list>
#include <vector>
#include <math.h>

using namespace std;

Face::Face(vector <Vertex> LI, int N, arma::irowvec C) {
	Vertices = LI;
	Numero = N;
	Visible = false;
	Color = C;
	R = 0;
	G = 0;
	B = 0;
}

void Face::ToString() {
	cout << "Cara: " << Numero << endl;
	for (int i = 0; i < Vertices.size(); i++) {
		Vertices[i].ToString();
	}
}

void Face::SetColor(arma::irowvec C) {
	Color = C;
}

void Face::setRGB(float Rojo, float Verde, float Azul) {
	R = Rojo;
	G = Verde;
	B = Azul;
}
Face::~Face()
{
}

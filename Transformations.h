#define _USE_MATH_DEFINES
#include <armadillo>
#include "Objectlist.h"
#include <cmath>
#pragma once
class Transformations
{
public:
	Transformations();
	arma::dmat T(float x, float y, float z);
	arma::dmat S(float x, float y, float z);
	arma::dmat RX(float angulo);
	arma::dmat RY(float angulo);
	arma::dmat RZ(float angulo);
	void Escala(Obj &Objeto, float x, float y, float z);
	void Traslacion0(Obj &Objeto, float x, float y, float z);
	void RotacionX(Obj &Objeto, float angulo);
	void RotacionY(Obj &Objeto, float angulo);
	void RotacionZ(Obj &Objeto, float angulo);
	void MulMatrizTransformacion(Obj &Objeto);
	void MulPuntoProyeccion(Vertex &V, float Zp, float dx, float dy, float dz, float q);
	~Transformations();
};


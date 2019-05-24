#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <list>
#include "Face.h"
#include <sstream>
#include <vector>
#include <GLFW/glfw3.h>
#include <armadillo>
#pragma once
using namespace std;

class Obj
{
private:
	string FileName;
	string NombreObjeto;
	int inicio;
public:
	~Obj();
	vector <Vertex> ListaV;
	vector <Face> ListaC;
	arma::irowvec Color = { 0,0,0 };
	arma::dmat MatrizTransformacion;
	Obj(string N, int ini, string nombreObjeto);
	void Imprime();
	void sImprime(string tipo);
	void CargaVertices();
	void CargaCaras();
	void MuestraTodo();
	void CalculaLuz(arma::drowvec Vn);
	void SetColor(arma::irowvec C);
	void SetMatrizTransformacion(arma::dmat MT);
	void DibujaObjeto();
	arma::dmat GetMatrizTransformacion();
};


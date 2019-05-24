#include <fstream>
#include <string>
#include <string.h>
#include <list>
#include <vector>
#include "Obj.h"
#include <GLFW/glfw3.h>
#include <armadillo>
#pragma once
using namespace std;

class ObjectList
{
private:
	string NombreArchivo;
public:
	vector <Obj> ListaObjetos;
	ObjectList(string NA);
	void CreaObjetos();
	~ObjectList();
	void DibujaObjeto();
	void setColor(int Rojo, int Verde, int Azul);
	void CalculaTodo(arma::drowvec Vn);
};


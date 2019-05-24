#include "Transformations.h"


Transformations::Transformations()
{
}


Transformations::~Transformations()
{
}

arma::dmat Transformations::T(float x, float y, float z) 
{
	arma::dmat T = { 
				   {1.0f, 0.0f, 0.0f, x},
				   {0.0f, 1.0f, 0.0f, y},
				   {0.0f, 0.0f, 1.0f, z},
				   {0.0f, 0.0f, 0.0f, 1.0f}
	};

	return (T);
}

arma::dmat Transformations::S(float x, float y, float z) 
{
	arma::dmat S = {
				   {x, 0.0f, 0.0f, 0.0f},
				   {0.0f, y, 0.0f, 0.0f},
				   {0.0f, 0.0f, z, 0.0f},
				   {0.0f, 0.0f, 0.0f, 1.0f}
	};
	return(S);
}
void Transformations::RotacionX(Obj &Objeto, float angulo) 
{
	arma::dmat RX = {
				   {1.0f, 0.0f, 0.0f, 0.0f},
				   {0.0f, (float)cos(angulo * M_PI / 180.0), - (float)sin(angulo * M_PI / 180.0), 0.0f},
				   {0.0f, (float)sin(angulo * M_PI / 180.0), (float)cos(angulo * M_PI / 180.0) , 0.0f},
				   {0.0f, 0.0f, 0.0f, 1.0f}
	};
	for (int i = 0; i < Objeto.ListaC.size(); i++) {
		for (int j = 0; j < Objeto.ListaC[i].Vertices.size(); j++) {
			Objeto.ListaC[i].Vertices[j].Vertice = RX * Objeto.ListaC[i].Vertices[j].Vertice ;
		}
	}
}

void Transformations::Traslacion0(Obj &Objeto, float x, float y, float z)
{
	arma::dmat T = {
				   {1.0f, 0.0f, 0.0f, x},
				   {0.0f, 1.0f, 0.0f, y},
				   {0.0f, 0.0f, 1.0f, z},
				   {0.0f, 0.0f, 0.0f, 1.0f}
	};

	for (int i = 0; i < Objeto.ListaC.size(); i++) {
		for (int j = 0; j < Objeto.ListaC[i].Vertices.size(); j++) {
			Objeto.ListaC[i].Vertices[j].Vertice = T * Objeto.ListaC[i].Vertices[j].Vertice;
		}
	}
}

void Transformations::RotacionY(Obj &Objeto, float angulo) 
{
	arma::dmat RY = {
				   {(float)cos(angulo * M_PI / 180), 0.0f, (float)sin(angulo * M_PI / 180) , 0.0f},
				   {0.0f, 1.0f, 0.0f, 0.0f},
				   {(float)-sin(angulo * M_PI / 180.0), 0.0f, (float)cos(angulo * M_PI / 180), 0.0f},
				   {0.0f, 0.0f, 0.0f, 1.0f}
	};
	for (int i = 0; i < Objeto.ListaC.size(); i++) {
		for (int j = 0; j < Objeto.ListaC[i].Vertices.size(); j++) {
			Objeto.ListaC[i].Vertices[j].Vertice = RY *  Objeto.ListaC[i].Vertices[j].Vertice;
		}
	}
}

void Transformations::RotacionZ(Obj &Objeto, float angulo)
{
	arma::dmat RZ = {
				   {(float)cos(angulo *  M_PI / 180.0), (float)-sin(angulo * M_PI / 180.0), 0.0f, 0.0f},
				   {(float)sin(angulo * M_PI / 180.0), (float)cos(angulo * M_PI / 180.0), 0.0f, 0.0f},
				   {0.0f, 0.0f, 1.0f, 0.0f},
				   {0.0f, 0.0f, 0.0f, 1.0f}
	};

	for (int i = 0; i < Objeto.ListaC.size(); i++) {
		for (int j = 0; j < Objeto.ListaC[i].Vertices.size(); j++) {
			Objeto.ListaC[i].Vertices[j].Vertice = RZ * Objeto.ListaC[i].Vertices[j].Vertice;
		}
	}
}

void Transformations::Escala(Obj &Objeto, float x, float y, float z)
{
	arma::dmat Sc = {
				   {x, 0.0f, 0.0f, 0.0f},
				   {0.0f, y, 0.0f, 0.0f},
				   {0.0f, 0.0f, z, 0.0f},
				   {0.0f, 0.0f, 0.0f, 1.0f}
	};
	for (int i = 0; i < Objeto.ListaC.size(); i++) {
		for (int j = 0; j < Objeto.ListaC[i].Vertices.size(); j++) {
			Objeto.ListaC[i].Vertices[j].Vertice = Sc * Objeto.ListaC[i].Vertices[j].Vertice;
		}
	}
}

arma::dmat Transformations::RX(float angulo) 
{
	arma::dmat RX = {
				   {1.0f, 0.0f, 0.0f, 0.0f},
				   {0.0f, (float)cos(angulo * M_PI / 180.0), -(float)sin(angulo * M_PI / 180.0), 0.0f},
				   {0.0f, (float)sin(angulo * M_PI / 180.0), (float)cos(angulo * M_PI / 180.0) , 0.0f},
				   {0.0f, 0.0f, 0.0f, 1.0f}
	};
	return(RX);
}

arma::dmat Transformations::RY(float angulo) 
{
	arma::dmat RY = {
				   {(float)cos(angulo * M_PI / 180), 0.0f, (float)sin(angulo * M_PI / 180) , 0.0f},
				   {0.0f, 1.0f, 0.0f, 0.0f},
				   {(float)-sin(angulo * M_PI / 180.0), 0.0f, (float)cos(angulo * M_PI / 180), 0.0f},
				   {0.0f, 0.0f, 0.0f, 1.0f}
	};
	return(RY);
}

arma::dmat Transformations::RZ(float angulo)
{
	arma::dmat RZ = {
				   {(float)cos(angulo *  M_PI / 180.0), (float)-sin(angulo * M_PI / 180.0), 0.0f, 0.0f},
				   {(float)sin(angulo * M_PI / 180.0), (float)cos(angulo * M_PI / 180.0), 0.0f, 0.0f},
				   {0.0f, 0.0f, 1.0f, 0.0f},
				   {0.0f, 0.0f, 0.0f, 1.0f}
	};
	return(RZ);
}

void Transformations::MulMatrizTransformacion(Obj &Objeto)
{
	for (int i = 0; i < Objeto.ListaV.size(); i++) 
	{
		Objeto.ListaV[i].Vertice = Objeto.MatrizTransformacion * Objeto.ListaV[i].Vertice;
	}
}

void Transformations::MulPuntoProyeccion(Vertex &V,float Zp, float dx, float dy, float dz, float q) 
{
	arma::dmat PP = {
				   {1.0f, 0.0f, - dx/dz , Zp * (dx/dz)},
				   {0.0f,1.0f, -dy/dz, Zp * (dy/dz)},
				   {0.0f, 0.0f, -Zp / (q * dz) , (pow(Zp,2) / q * dz) + Zp},
				   {0.0f, 0.0f, -1 / (q * dz), (Zp / q * dz) + 1}
	};
	V.Vertice = V.Vertice * PP;
}

#include <stdio.h>
#include "ObjectList.h"
#include <vector>
#include <GLFW/glfw3.h>
#include "Transformations.h"
#include "Bezier.h"
#include "VerticeBezier.h"
#include <armadillo>
#include <vector>
#include <GL/glut.h>
#include <stdlib.h>

void ChecaTecla(GLFWwindow* window, int key, int scancode, int action, int mods);
void ObtenPlataformaSiguiente(ObjectList Plataforma);
void DibujaRanaCurva(Obj Rana, vector<ObjectList> Plataformas);
/* Variables Globales*/
arma::drowvec eye;
arma::drowvec camera;;
arma::fvec VecC;
arma::drowvec Vn;
vector <ObjectList> Plataformas;
Transformations T;
bool banderaMovimiento;
float PosX;
float PosY;
float PosZ;
int contadorPlataforma;
int tipoCamara;

int main(int argc, char** argv) {
	tipoCamara = 1;
	eye = { 0.0,.5,2.0 };
	camera = { 0,0,0 };
	Vn = { 0,0,0 };
	Vn = { eye[0] - camera[0], eye[1] - camera[1], eye[2] - camera[2] };
	float MagnitudVn = sqrt((pow(Vn[0], 2) + pow(Vn[1], 2) + pow(Vn[2],2)));
	for (int i = 0; i < 3; i++) {
		Vn[i] = Vn[i] / MagnitudVn;
	}
	float magnitudPrueba = pow(Vn[0], 2) + pow(Vn[1], 2) + pow(Vn[2], 2);
	cout << "Magnitud Vn: " << magnitudPrueba << endl;
	contadorPlataforma = 0;
	VecC = { 0,1,0 };
	banderaMovimiento = false;
	GLFWwindow* window;
	T = Transformations();
	ObjectList Rana = ObjectList("Rana.obj");
	ObjectList Plataforma = ObjectList("Plataforma.obj");
	int contador = 1;
#pragma region
	for (int i = 0; i < Rana.ListaObjetos.size(); i++) {
		T.Escala(Rana.ListaObjetos[i], .2, .2, .2);
		T.Traslacion0(Rana.ListaObjetos[i], -Rana.ListaObjetos[0].ListaC[0].Vertices[0].getX(), -Rana.ListaObjetos[0].ListaC[0].Vertices[0].getY(), -Rana.ListaObjetos[0].ListaC[0].Vertices[0].getZ());
		T.RotacionY(Rana.ListaObjetos[i], 90);
	}
	Rana.setColor(0,255,0);
	Rana.CalculaTodo(Vn);
#pragma endregion // Cargamos la rana
#pragma region
	for (int i = 0; i < Plataforma.ListaObjetos.size(); i++) {
		T.Escala(Plataforma.ListaObjetos[i], .2, .1, .1);
		T.Traslacion0(Plataforma.ListaObjetos[i], -Plataforma.ListaObjetos[0].ListaC[0].Vertices[0].getX(), -Plataforma.ListaObjetos[0].ListaC[0].Vertices[0].getY(), -Plataforma.ListaObjetos[0].ListaC[0].Vertices[0].getZ());
		T.Traslacion0(Plataforma.ListaObjetos[i],.5,.5,-.11);
	}
	Plataforma.setColor(255, 255, 255);
	Plataforma.CalculaTodo(Vn);
	Plataformas.push_back(Plataforma);
#pragma endregion // Cargamos al inicio las plataformas
#pragma region
	VerticeBezier v1(Rana.ListaObjetos[0].ListaC[0].Vertices[0].getX(), Rana.ListaObjetos[0].ListaC[0].Vertices[1].getY(), Rana.ListaObjetos[0].ListaC[0].Vertices[0].getZ());
	VerticeBezier v2(Rana.ListaObjetos[0].ListaC[0].Vertices[0].getX() + .8 , Rana.ListaObjetos[0].ListaC[0].Vertices[0].getY() + .5, Rana.ListaObjetos[0].ListaC[0].Vertices[0].getZ());
	VerticeBezier v3(Rana.ListaObjetos[0].ListaC[0].Vertices[0].getX() + .8, Rana.ListaObjetos[0].ListaC[0].Vertices[0].getY() + .5, Rana.ListaObjetos[0].ListaC[0].Vertices[0].getZ());
	VerticeBezier v4(Plataforma.ListaObjetos[0].ListaC[0].Vertices[0].getX() + .15, Plataforma.ListaObjetos[0].ListaC[0].Vertices[0].getY() + .035, Plataforma.ListaObjetos[0].ListaC[0].Vertices[0].getZ());
	Bezier Curva(v1,v2,v3,v4);
#pragma endregion // Aqui calculamos la primera curva 
#pragma region
	
	
	if (!glfwInit())
	{
		fprintf(stderr, "Fallo al inicializar GLFW\n");
		getchar();
		return -1;
	}

	window = glfwCreateWindow(1024, 768, "Proyecto Axel López Rodríguez", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Fallo al abrir la ventana de GLFW.\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwSetKeyCallback(window, ChecaTecla);
	float conty = 0;
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glClearColor(.15,.1,.5,0);

	// Proyecciones
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	float ar = width / height;
	//Proyeccion en Paralelo
	//glViewport(0, 0, width, height);
	//glOrtho(-ar, -ar, -1.0, 1.0, 1.0, 10.0);

	/*Proyección en perspectiva*/
	glFrustum(-ar, ar, -ar, ar, 1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	
#pragma endregion // Aqui inicializamos la ventana 
#pragma region
	Rana.ListaObjetos[0].ListaC[0].Color.print("Color Rana");
	do {
		Rana.CalculaTodo(Vn);
		for (int i = 0; i < Plataformas.size(); i++) {
			Plataformas[i].CalculaTodo(Vn);
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		Vn = eye - camera;
		PosX = Rana.ListaObjetos[0].ListaC[0].Vertices[0].getX();
		PosY = Rana.ListaObjetos[0].ListaC[0].Vertices[0].getY();
		gluLookAt(eye[0], eye[1], eye[2], camera[0], camera[1], camera[2], VecC[0], VecC[1], VecC[2]);
		glBegin(GL_TRIANGLES);
		Rana.DibujaObjeto();
		for (int i = 0; i < Plataformas.size(); i++) {
			Plataformas[i].DibujaObjeto();
		}
		if (banderaMovimiento == true ) {
			Rana.CalculaTodo(Vn);
			for (int i = 0; i < Plataformas.size(); i++) {
				Plataformas[i].CalculaTodo(Vn);
			}
			v1.setV(Rana.ListaObjetos[0].ListaC[0].Vertices[0].getX(), Rana.ListaObjetos[0].ListaC[0].Vertices[1].getY(), Rana.ListaObjetos[0].ListaC[0].Vertices[0].getZ());
			v2.setV(Rana.ListaObjetos[0].ListaC[0].Vertices[0].getX() + .05, Rana.ListaObjetos[0].ListaC[0].Vertices[0].getY() + .5, Rana.ListaObjetos[0].ListaC[0].Vertices[0].getZ());
			v3.setV(Rana.ListaObjetos[0].ListaC[0].Vertices[0].getX() + .1, Rana.ListaObjetos[0].ListaC[0].Vertices[0].getY() + .5, Rana.ListaObjetos[0].ListaC[0].Vertices[0].getZ());
			v4.setV(Plataformas[contadorPlataforma].ListaObjetos[0].ListaC[0].Vertices[0].getX() + .30, Plataformas[contadorPlataforma].ListaObjetos[0].ListaC[0].Vertices[0].getY() + .035, Plataformas[contadorPlataforma].ListaObjetos[0].ListaC[0].Vertices[0].getZ());
			Curva.setVertex(v1, v2, v3, v4);
			for (int i = 0; i < Rana.ListaObjetos.size(); i++) {
				for (int j = 0; j < Curva.vcurve.size(); j++) {
					if (j - 1 >= 0) {
						T.Traslacion0(Rana.ListaObjetos[0], Curva.vcurve[j].Valores(0) - Curva.vcurve[j - 1].Valores(0), Curva.vcurve[j].Valores(1) - Curva.vcurve[j - 1].Valores(1), 0);
						DibujaRanaCurva(Rana.ListaObjetos[0], Plataformas);	
					}
				}	
			}
			cout << "Vertice Plataforma: " << contadorPlataforma + 1 << endl;
			cout << Plataformas[contadorPlataforma].ListaObjetos[0].ListaC[0].Vertices[0].Vertice[0] << endl;
			cout << Plataformas[contadorPlataforma].ListaObjetos[0].ListaC[0].Vertices[0].Vertice[1] << endl;
			cout << Plataformas[contadorPlataforma].ListaObjetos[0].ListaC[0].Vertices[0].Vertice[2] << endl;
			cout << "Vertice Rana" << endl;
			cout << Rana.ListaObjetos[0].ListaC[0].Vertices[0].Vertice[0] << endl;
			cout << Rana.ListaObjetos[0].ListaC[0].Vertices[0].Vertice[1] << endl;
			cout << Rana.ListaObjetos[0].ListaC[0].Vertices[0].Vertice[2] << endl;
			banderaMovimiento = false;
			contadorPlataforma++;
		}
		
		glEnd();
		glfwSwapBuffers(window);
		glfwPollEvents();

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);
	glfwTerminate();
#pragma endregion // Aqui hacemos todo el movimiento de la rana 
}


void ChecaTecla(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	float AuxZ = PosZ + 2.0;
	float AuxY = PosY + 2.0;
	float AY = PosY + .5;
	float AuxX = PosX;
	float MagnitudVn;
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_UP:
			/* Acciones a hacer si se presiona la tecla hacia arriba (Mover la camara hacia arriba)*/
			//cout << "Presionaste la tecla arriba" << endl;		
			tipoCamara = 2;
			eye = {PosX,AuxY,0};
			camera = { 0,0,0 };
			VecC = { 1,0,0 };
			Vn = { eye[0] - camera[0], eye[1] - camera[1], eye[2] - camera[2] };
			MagnitudVn = sqrt((pow(Vn[0], 2) + pow(Vn[1], 2) + pow(Vn[2], 2)));
			for (int i = 0; i < 3; i++) {
				Vn[i] = Vn[i] / MagnitudVn;
			}
			break;

		case GLFW_KEY_RIGHT:
			/*Mover la camara a la derecha*/
			//cout << "Presionaste la tecla derecha" << endl;
			tipoCamara = 1;
			eye = { PosX,AY, 2.0};
			camera = {PosX,PosY,0};
			VecC = {0,1,0};
			Vn = { eye[0] - camera[0], eye[1] - camera[1], eye[2] - camera[2] };
			MagnitudVn = sqrt((pow(Vn[0], 2) + pow(Vn[1], 2) + pow(Vn[2], 2)));
			for (int i = 0; i < 3; i++) {
				Vn[i] = Vn[i] / MagnitudVn;
			}
			break;

		case GLFW_KEY_W:
			//cout << "Presionaste la tecla W" << endl;
			ObtenPlataformaSiguiente(Plataformas[Plataformas.size() - 1]);
			banderaMovimiento = true;
			MagnitudVn = sqrt((pow(Vn[0], 2) + pow(Vn[1], 2) + pow(Vn[2], 2)));
			for (int i = 0; i < 3; i++) {
				Vn[i] = Vn[i] / MagnitudVn;
			}
			break;

		case GLFW_KEY_SPACE:
			switch (tipoCamara) {
			case 1: // Camara viendo a la derecha
				eye = { PosX,AY, 2.0 };
				camera = { PosX,PosY,0 };
				VecC = { 0,1,0 };
				Vn = { eye[0] - camera[0], eye[1] - camera[1], eye[2] - camera[2] };
				MagnitudVn = sqrt((pow(Vn[0], 2) + pow(Vn[1], 2) + pow(Vn[2], 2)));
				for (int i = 0; i < 3; i++) {
					Vn[i] = Vn[i] / MagnitudVn;
				}
				break;
			case 2: // Camara viendo hacia arriba
				eye = { PosX,AuxY,0 };
				camera = { 0,0,0 };
				VecC = { 1,0,0 };
				Vn = { eye[0] - camera[0], eye[1] - camera[1], eye[2] - camera[2] };
				MagnitudVn = sqrt((pow(Vn[0], 2) + pow(Vn[1], 2) + pow(Vn[2], 2)));
				for (int i = 0; i < 3; i++) {
					Vn[i] = Vn[i] / MagnitudVn;
				}
				break;
			}
		case GLFW_KEY_Z:
			switch (tipoCamara) {
			case 1: // Camara viendo a la derecha
				eye = { PosX,AY, 1.0 };
				camera = { PosX,PosY,0 };
				VecC = { 0,1,0 };
				Vn = { eye[0] - camera[0], eye[1] - camera[1], eye[2] - camera[2] };
				MagnitudVn = sqrt((pow(Vn[0], 2) + pow(Vn[1], 2) + pow(Vn[2], 2)));
				for (int i = 0; i < 3; i++) {
					Vn[i] = Vn[i] / MagnitudVn;
				}
				break;
			case 2: // Camara viendo hacia arriba
				eye = { PosX,AuxY - .5,0 };
				camera = { 0,0,0 };
				VecC = { 1,0,0 };
				Vn = { eye[0] - camera[0], eye[1] - camera[1], eye[2] - camera[2] };
				MagnitudVn = sqrt((pow(Vn[0], 2) + pow(Vn[1], 2) + pow(Vn[2], 2)));
				for (int i = 0; i < 3; i++) {
					Vn[i] = Vn[i] / MagnitudVn;
				}
				break;
			}

		}
	}
}

void ObtenPlataformaSiguiente(ObjectList Plataforma) {
	ObjectList Auxiliar = Plataforma;
	for (int i = 0; i < Auxiliar.ListaObjetos.size(); i++) {
		T.Traslacion0(Auxiliar.ListaObjetos[i], .5, .5, 0);
	}
	Auxiliar.CalculaTodo(Vn);
	Plataformas.push_back(Auxiliar);
}

void DibujaRanaCurva(Obj Rana, vector<ObjectList> Plataformas) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	Rana.DibujaObjeto();
	for (int i = 0; i < Plataformas.size(); i++) {
		Plataformas[i].DibujaObjeto();
	}
}
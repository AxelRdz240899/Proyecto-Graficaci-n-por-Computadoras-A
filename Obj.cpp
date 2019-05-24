#include "Obj.h"

Obj::Obj(string N, int ini, string nombreObjeto) {
	FileName = N;
	inicio = ini;
	CargaVertices();
	CargaCaras();
	NombreObjeto = nombreObjeto;
}

void Obj::Imprime() { // Método para imprimir todo el archivo OBJ

	ifstream Archivo;
	string Linea = "/0";
	Archivo.open(FileName);

	while (getline(Archivo, Linea)) {
		cout << Linea << endl;
	}
	Archivo.close();
}

void Obj::sImprime(string tipo) {  // Método para imprimir lo que busquemos en el archivo OBJ
	ifstream Archivo;
	string Linea = "/0";
	Archivo.open(FileName);
	if (Archivo.is_open()) {
		cout << "Archivo abierto correctamente" << endl;
		while (getline(Archivo, Linea)) {
			if (tipo[1] == ' ') {
				if (Linea[1] == ' ' && Linea[0] == tipo[0]) {
					cout << Linea << endl;
				}
			}
			else if (Linea[1] == tipo[1] && Linea[0] == tipo[0]) {
				cout << Linea << endl;
			}
		}
	}
	else {
		cout << "No se pudo abrir el archivo, intentelo de nuevo" << endl;
	}
	Archivo.close();
}

void Obj::CargaVertices() { // Método para cargar los Vertices del archivo OBJ en la lista de vertices
	ifstream Archivo;
	string tipo = "v ";
	int contador = 0, numLinea = 0, bandera = 0;
	float x, y, z;
	string Linea;
	Archivo.open(FileName); // Abrimos el Archivo
	if (Archivo.is_open()) {
		while (getline(Archivo, Linea)) {
			contador = 1;
			numLinea++;
			if (numLinea == (inicio + 1)) {
				//cout << "La bandera se activó en la linea: " << numLinea << endl;
				bandera = 1;
			}
			if (Linea[0] == 'g' || Linea[0] == 'o') {
				//cout << "La bandera se desactivó en la linea: " << numLinea << endl;
				bandera = 0;
			}
			if (bandera == 1) {
				if (tipo[1] == ' ') { // En caso de que solo sea una letra
					if (Linea[1] == ' ' && Linea[0] == tipo[0]) {
						string numero;
						for (int i = 2; i <= Linea.length(); i++) {
							if (Linea[i] != ' ' && i < Linea.length()) {
								numero += Linea[i];
							}
							else if (numero != "") {
								switch (contador) {
								case 1:
									x = stof(numero);
									numero = "";
									contador++;
									break;
								case 2:
									y = stof(numero);
									numero = "";
									contador++;
									break;
								case 3:
									z = stof(numero);
									numero = "";
									break;
								}
							}
						}
						ListaV.push_back(Vertex(x,y,z));
					}
				}
			}
		}
		int tamV = ListaV.size();
		//cout << "El tamaño de la lista de vertices es: " << tamV << endl;
		Archivo.close();
	}
	else {
		cout << "No se pudo abrir el archivo, intentelo de nuevo" << endl;
	}
}

void Obj::CargaCaras() {
	ListaC.clear();
	ifstream Archivo;
	string tipo = "f ";
	int numLinea = 0;
	int numeroCara = 1;
	int contador = 0, tipoDivision = 0, npos, numaux, bandera = 0;
	string numero;
	string Linea;
	vector <Vertex> listaVertices;
	Archivo.open(FileName);
	if (Archivo.is_open()) {
		while (getline(Archivo, Linea)) {
			numLinea++;
			if (numLinea == (inicio + 1)) {
				bandera = 1;
				//cout << "La bandera se activo en la linea: " << numLinea << endl;
			}
			if (Linea[0] == 'g' || Linea[0] == 'o') {
				bandera = 0;
				//cout << "La bandera se desactivo en la linea: " << numLinea << endl;
			}
			if (bandera == 1) {
				if (tipo[1] == ' ') { // En caso de que solo sea una letra
					if (Linea[1] == ' ' && Linea[0] == tipo[0]) {
						for (int i = 0; i <= Linea.length(); i++) {  // Determino cuantos vertices tiene cada cara
							if (Linea[i] == '/' && i < Linea.length()) {
								tipoDivision = 1; // Variable que contiene el tipo de división entre caras(1 si son Diagonales, 0 si son espacios);
							}
						}
						for (int i = 2; i <= Linea.length(); i++) {
							if (Linea[i] != ' ' && i < Linea.length()) {
								numero += Linea[i];
							}
							else if (numero != "") {
								switch (tipoDivision) {
								case 1:
									npos = numero.find("/");
									if (npos >= 0) {
										string cadenaresultante = numero.substr(0, npos);
										numaux = atoi(cadenaresultante.c_str());
										//cout << numaux << endl;
										listaVertices.push_back(ListaV[numaux - 1]);
										numero = "";
									}
									break;

								case 0:
									numaux = atoi(numero.c_str());
									//cout << numaux << endl;
									listaVertices.push_back(ListaV[numaux - 1]);
									numero = "";
									break;
								}
							}
						}
						tipoDivision = 0;
						ListaC.push_back(Face(listaVertices,numeroCara,Color));
						numeroCara++;
						listaVertices.clear();
					}
				}
			}
		}
		Archivo.close();
	}
	else {
		cout << "No se pudo abrir el archivo, intentelo de nuevo" << endl;
	}
}

void Obj::CalculaLuz(arma::drowvec Vn) {
	double Ia = .95; // Intensidad de la Luz Ambiente
	double Ka = .85; // Coeficiente de luz ambiente
	double Ip = .8; // Intensidad del foco
	double Kd = .75; // Coeficiente de reflexión Difusa
	float ResultadoVisibilidad = 0;
	arma::drowvec Arreglo[2];
	arma::drowvec Normal = { 0,0,0 };
	arma::drowvec V1 = { 0,0,0 };
	arma::drowvec VectorAuxiliar{ 0,0,0 };
	arma::drowvec Foco = { 30, -24, -21 }; // Foco
	arma::drowvec L = { 0,0,0 }; // Vector entre el foco y normal de los vertices
	for (int i = 0; i < ListaC.size(); i++) {
		V1[0] = ListaC[i].Vertices[0].getX();
		V1[1] = ListaC[i].Vertices[0].getY();
		V1[2] = ListaC[i].Vertices[0].getZ();
		VectorAuxiliar[0] = ListaC[i].Vertices[1].getX() - ListaC[i].Vertices[0].getX();
		VectorAuxiliar[1] = ListaC[i].Vertices[1].getY() - ListaC[i].Vertices[0].getY();
		VectorAuxiliar[2] = ListaC[i].Vertices[1].getZ() - ListaC[i].Vertices[0].getZ();
		Arreglo[0] = VectorAuxiliar;
		VectorAuxiliar[0] = ListaC[i].Vertices[2].getX() - ListaC[i].Vertices[0].getX();
		VectorAuxiliar[1] = ListaC[i].Vertices[2].getY() - ListaC[i].Vertices[0].getY();
		VectorAuxiliar[2] = ListaC[i].Vertices[2].getZ() - ListaC[i].Vertices[0].getZ();
		Arreglo[1] = VectorAuxiliar;
		Normal = arma::cross(Arreglo[0], Arreglo[1]);
		double Magnitud = sqrt((pow(Normal[0], 2) + pow(Normal[1], 2) + pow(Normal[2], 2)));
		for (int j = 0; j < 3; j++) {
			Normal[j] = Normal[j] / Magnitud;
		}

		float X = pow(Normal[0], 2) + pow(Normal[1], 2) + pow(Normal[2], 2);
		//cout << X << endl; //Para comprobar si la magnitud es 1(El vector Normal está Normalizado)
		//Normal.print("Vector Normal(Normalizado) ");
		ResultadoVisibilidad = arma::dot(Normal, Vn);
		if (ResultadoVisibilidad < 0) {
			ListaC[i].Visible = true;
			 L = Foco - V1;
			double MagnitudL = sqrt((pow(L[0], 2) + pow(L[1], 2) + pow(L[2], 2)));
			for (int j = 0; j < 3; j++) {
				L[j] = L[j] / MagnitudL;
			}
			float Y = pow(L[0], 2) + pow(L[1], 2) + pow(L[2], 2);
			//cout << "Magnitud L " << Y << endl;
			float I =	(Ka * Ia) + (Ip * Kd * dot(Normal, L));

			if (I >= 0 && I <= 2) {
				I = I / 2;
				float Rojo = (ListaC[i].Color[0] * I) / 255;
				float Verde = (ListaC[i].Color[1] * I) / 255;
				float Azul = (ListaC[i].Color[2] * I) / 255;
				ListaC[i].setRGB(Rojo, Verde, Azul);
				//cout << "Rojo: " << Rojo << "Verde: " << Verde << "Azul: " << Azul << endl;
			}
			
		}

	}
}
void Obj::MuestraTodo() {
	cout << "Objeto: " << NombreObjeto << endl;
	cout << endl;
	for (int i = 0; i < ListaC.size(); i++) {
		if (ListaC[i].Visible == true) {
			//ListaC[i].ToString();
		}
	}
}


void Obj::SetMatrizTransformacion(arma::dmat MT) 
{
	MatrizTransformacion = MT;
}

arma::dmat Obj::GetMatrizTransformacion() 
{
	return MatrizTransformacion;
}

void Obj::SetColor(arma::irowvec C) {
	Color = C;
	for (int i = 0; i < ListaC.size(); i++) {
		ListaC[i].SetColor(Color);
	}
}
void Obj::DibujaObjeto() 
{
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < ListaC.size(); i++) 
	{
		for (int j = 0; j < ListaC[i].Vertices.size(); j++) 
		{
			if (ListaC[i].Visible == true) {
				glColor3f(ListaC[i].R, ListaC[i].G, ListaC[i].B);
				glVertex3f(ListaC[i].Vertices[j].getX(), ListaC[i].Vertices[j].getY(), ListaC[i].Vertices[j].getZ());
			}
		}
	}
}


Obj::~Obj()
{
}



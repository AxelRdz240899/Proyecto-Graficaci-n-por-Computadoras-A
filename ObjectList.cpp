#include "ObjectList.h"

ObjectList::ObjectList(string NA) {
	NombreArchivo = NA;
	CreaObjetos();
}

void ObjectList::CreaObjetos() {
	int numerosInicio[100];
	int NumeroObjetos = 0, numLinea = 0, i = 0, aux2 = 0;
	string NombreObjetos[100];
	string Linea, nombreObj;
	ifstream Archivo;
	Archivo.open(NombreArchivo);
	if (Archivo.is_open()) {
		while (getline(Archivo, Linea)) {
			//cout << Linea << endl;
			numLinea++;
			if (Linea[0] == 'g' || Linea[0] == 'o') {
				for (int j = 2; j < Linea.length(); j++) {
					nombreObj += Linea[j];
				}
				NombreObjetos[NumeroObjetos] = nombreObj;
				nombreObj = "";
				numerosInicio[NumeroObjetos] = numLinea;
				NumeroObjetos++;
			}
		}
	}
	for (int i = 0; i < NumeroObjetos; i++) {
		ListaObjetos.push_back(Obj(NombreArchivo, numerosInicio[i], NombreObjetos[i]));
	}
	for (int i = 0; i < ListaObjetos.size(); i++) {
		cout << "Objeto creado Correctamente" << endl;
	}
}

ObjectList::~ObjectList()
{
	ListaObjetos.clear();
}

void ObjectList::DibujaObjeto() 
{
		glBegin(GL_TRIANGLES);
		for (int i = 0; i < ListaObjetos.size(); i++) {
			for (int j = 0; j <ListaObjetos[i].ListaC.size() ; j++) {
				for (int z = 0; z < ListaObjetos[i].ListaC[j].Vertices.size(); z++) {
					if (ListaObjetos[i].ListaC[j].Visible == true) {
						glColor3f(ListaObjetos[i].ListaC[j].R, ListaObjetos[i].ListaC[j].G, ListaObjetos[i].ListaC[j].B);
						glVertex3f(ListaObjetos[i].ListaC[j].Vertices[z].getX(), ListaObjetos[i].ListaC[j].Vertices[z].getY(), ListaObjetos[i].ListaC[j].Vertices[z].getZ());
					}
				}
			}	
		}
}

void ObjectList::setColor(int Rojo, int Verde, int Azul) {
	arma::irowvec Color = {Rojo,Verde,Azul};
	for (int i = 0; i < ListaObjetos.size(); i++) {
		ListaObjetos[i].SetColor(Color);
	}
}

void ObjectList::CalculaTodo(arma::drowvec Vn) {
	for (int i = 0; i < ListaObjetos.size(); i++) {
		ListaObjetos[i].CalculaLuz(Vn);
	}
}

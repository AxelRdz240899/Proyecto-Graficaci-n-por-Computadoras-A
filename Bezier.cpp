#include "Bezier.h"

void Bezier::calc_Curve() {
	vcurve.clear();
	arma::dmat Gb; 
	arma::dvec P1 = p1.GetVertice();
	arma::dvec P2 = p2.GetVertice();
	arma::dvec P3 = p3.GetVertice();
	arma::dvec P4 = p4.GetVertice();
	Gb = { {P1[0] , P1[1] , P1[2]} ,
			   {P2[0] , P2[1] ,P2[2]} ,
			   {P3[0] , P3[1] , P3[2]} ,
			   {P4[0] , P4[1] , P4[2]} };
	for (float t = 0.0f; t <= 1.0f; t += dt) {
		arma::drowvec T = { powf(t, 3.0), powf(t, 2.0), t, 1.0f };
		arma::dmat Qt = T * Mb * Gb;
		Qt.print();
		VerticeBezier vc(Qt.at(0,0),Qt.at(0,1),Qt.at(0,2));
		vcurve.push_back(vc);
	}
}

Bezier::Bezier() {
	Mb = { {-1.0, 3.0, -3.0, 1.0},
			  {3.0, -6.0, 3.0, 0.0},
			  {-3.0, 3.0, 0.0, 0.0},
			  {1.0, 0.0, 0.0, 0.0} };
}
Bezier::Bezier(VerticeBezier v1, VerticeBezier v2, VerticeBezier v3, VerticeBezier v4){
	{
		Mb = { {-1.0, 3.0, -3.0, 1.0},
			  {3.0, -6.0, 3.0, 0.0},
			  {-3.0, 3.0, 0.0, 0.0},
			  {1.0, 0.0, 0.0, 0.0} };
		p1.set_Vertice(v1.GetVertice());
		p2.set_Vertice(v2.GetVertice());
		p3.set_Vertice(v3.GetVertice());
		p4.set_Vertice(v4.GetVertice());
		calc_Curve();
	}
}

void Bezier::setVertex(VerticeBezier v1, VerticeBezier v2, VerticeBezier v3, VerticeBezier v4){
	p1.set_Vertice(v1.GetVertice());
	p2.set_Vertice(v2.GetVertice());
	p3.set_Vertice(v3.GetVertice());
	p4.set_Vertice(v4.GetVertice());
	calc_Curve();
}


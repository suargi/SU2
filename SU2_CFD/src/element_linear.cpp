/*!
 * \file element_linear.cpp
 * \brief Definition of the linear element structure
 * \author R. Sanchez
 * \version 4.0.0 "Cardinal"
 *
 * SU2 Lead Developers: Dr. Francisco Palacios (Francisco.D.Palacios@boeing.com).
 *                      Dr. Thomas D. Economon (economon@stanford.edu).
 *
 * SU2 Developers: Prof. Juan J. Alonso's group at Stanford University.
 *                 Prof. Piero Colonna's group at Delft University of Technology.
 *                 Prof. Nicolas R. Gauger's group at Kaiserslautern University of Technology.
 *                 Prof. Alberto Guardone's group at Polytechnic University of Milan.
 *                 Prof. Rafael Palacios' group at Imperial College London.
 *
 * Copyright (C) 2012-2015 SU2, the open-source CFD code.
 *
 * SU2 is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * SU2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with SU2. If not, see <http://www.gnu.org/licenses/>.
 */

#include "../include/element_structure.hpp"

CTRIA1::CTRIA1(void) : CElement() {

}

CTRIA1::CTRIA1(unsigned short val_nDim, unsigned long val_elID, CConfig *config)
: CElement(val_nDim, config) {

	unsigned short iGaussPoint=0;
	unsigned short iNode, iGauss, jNode;
	unsigned short nDimSq;

	nNodes = 3;
	nGaussPoints = 1;

	nDimSq = nDim*nDim;

	GaussPoint = new CGaussVariable*[nGaussPoints];
	for (iGauss = 0; iGauss < nGaussPoints; iGauss++) {
		GaussPoint[iGauss] = new CGaussVariable(iGauss, nDim, nNodes);
	}

	/*--- Initialize structure for current and reference configuration ---*/

	CurrentCoord = new double*[nNodes];
	for (iNode = 0; iNode < nNodes; iNode++){
		CurrentCoord [iNode] = new double[nDim];
	}

	RefCoord = new double*[nNodes];
	for (iNode = 0; iNode < nNodes; iNode++){
		RefCoord [iNode] = new double[nDim];
	}

	GaussWeight = new double [nGaussPoints];

	GaussCoord = new double*[nGaussPoints];
	for (iGauss = 0; iGauss < nGaussPoints; iGauss++){
		GaussCoord [iGauss] = new double[nDim];
	}

	GaussCoord[0][0] = 0.333333333333333;  GaussCoord[0][1] = 0.333333333333333;  GaussWeight[0] = 0.5;

	Kab = new double **[nNodes];
	for (iNode = 0; iNode < nNodes; iNode++){
		Kab [iNode] = new double*[nNodes];
		for (jNode = 0; jNode < nNodes; jNode++){
			Kab [iNode][jNode] = new double[nDimSq];
		}
	}

}

CTRIA1::~CTRIA1(void) {

  if (GaussPoint            != NULL) delete [] GaussPoint;

}

void CTRIA1::ComputeGrad_Linear(void){

}

void CTRIA1::ComputeGrad_NonLinear(void){

}


void CTRIA1::OutputGradN_X(CGeometry *geometry, CConfig *config){

}

double CTRIA1::GetGradNi_X(unsigned short iNode, unsigned short iGauss, unsigned short iDim){


	return GaussPoint[iGauss]->GetGradNi_Xj(iNode,iDim);

}





CQUAD4::CQUAD4(void) : CElement() {

}

CQUAD4::CQUAD4(unsigned short val_nDim, unsigned long val_elID, CConfig *config)
: CElement(val_nDim, config) {

	unsigned short iGaussPoint=0;
	unsigned short iNode, iGauss, jNode;
	unsigned short nDimSq;

	nNodes = 4;
	nGaussPoints = 4;

	nDimSq = nDim*nDim;

	GaussPoint = new CGaussVariable*[nGaussPoints];
	for (iGauss = 0; iGauss < nGaussPoints; iGauss++) {
		GaussPoint[iGauss] = new CGaussVariable(iGauss, nDim, nNodes);
	}

	/*--- Initialize structure for current and reference configuration ---*/

	CurrentCoord = new double*[nNodes];
	for (iNode = 0; iNode < nNodes; iNode++){
		CurrentCoord [iNode] = new double[nDim];
	}

	RefCoord = new double*[nNodes];
	for (iNode = 0; iNode < nNodes; iNode++){
		RefCoord [iNode] = new double[nDim];
	}

	GaussWeight = new double [nGaussPoints];

	GaussCoord = new double*[nGaussPoints];
	for (iGauss = 0; iGauss < nGaussPoints; iGauss++){
		GaussCoord [iGauss] = new double[nDim];
	}

	GaussCoord[0][0] = -0.577350269189626;  GaussCoord[0][1] = -0.577350269189626;  GaussWeight[0] = 1.0;
	GaussCoord[1][0] = 0.577350269189626;   GaussCoord[1][1] = -0.577350269189626;  GaussWeight[1] = 1.0;
	GaussCoord[2][0] = 0.577350269189626;   GaussCoord[2][1] = 0.577350269189626;   GaussWeight[2] = 1.0;
	GaussCoord[3][0] = -0.577350269189626;  GaussCoord[3][1] = 0.577350269189626;   GaussWeight[3] = 1.0;

	Kab = new double **[nNodes];
	for (iNode = 0; iNode < nNodes; iNode++){
		Kab [iNode] = new double*[nNodes];
		for (jNode = 0; jNode < nNodes; jNode++){
			Kab [iNode][jNode] = new double[nDimSq];
		}
	}

}

CQUAD4::~CQUAD4(void) {

  if (GaussPoint            != NULL) delete [] GaussPoint;

}

//void CQUAD4::ComputeGradN_X(CGeometry *geometry, CConfig *config){
//
//	double CoordCorn[4][2];
//	unsigned long PointCorners[4];
//	double Jacobian[2][2], dNiXj[4][2];
//	double GradNi_Xj;
//	double ad[3][3];
//	double detJac;
//	unsigned short iNode, iDim, iGauss, i, j;
//
//	unsigned short val_iGauss;
//
//	/*--- Retrieve the coordinates of the corners ---*/
//
//    for (iNode = 0; iNode < nNodes; iNode++) {
//      PointCorners[iNode] = geometry->elem[elementID]->GetNode(iNode); //Check what's the best way to retrieve this
//            for (iDim = 0; iDim < nDim; iDim++) {
//            CoordCorn[iNode][iDim] = geometry->node[PointCorners[iNode]]->GetCoord(iDim);
//      }
//    }
//
//	/*--- Compute the Jacobian matrix for each Gauss Point ---*/
//
//	for (iGauss = 0; iGauss < nGaussPoints ; iGauss++){
//
//		switch (iGauss){
//
//			case 0:
//
//				dNiXj[0][0]=-0.394337567297407; dNiXj[1][0]=0.394337567297407;  dNiXj[2][0]=0.105662432702594; dNiXj[3][0]=-0.105662432702594;
//				dNiXj[0][1]=-0.394337567297407; dNiXj[1][1]=-0.105662432702594; dNiXj[2][1]=0.105662432702594; dNiXj[3][1]=0.394337567297407;
//
//				break;
//			case 1:
//
//				dNiXj[0][0]=-0.394337567297407; dNiXj[1][0]=0.394337567297407; dNiXj[2][0]=0.105662432702594;  dNiXj[3][0]=-0.105662432702594;
//				dNiXj[0][1]=-0.105662432702594; dNiXj[1][1]=-0.394337567297407; dNiXj[2][1]=0.394337567297407; dNiXj[3][1]=0.105662432702594;
//
//				break;
//
//			case 2:
//
//				dNiXj[0][0]=-0.105662432702594; dNiXj[1][0]=0.105662432702594;  dNiXj[2][0]=0.394337567297407; dNiXj[3][0]=-0.394337567297407;
//				dNiXj[0][1]=-0.105662432702594; dNiXj[1][1]=-0.394337567297407; dNiXj[2][1]=0.394337567297407; dNiXj[3][1]=0.105662432702594;
//
//				break;
//
//			case 3:
//
//				dNiXj[0][0]=-0.105662432702594; dNiXj[1][0]=0.105662432702594;  dNiXj[2][0]=0.394337567297407; dNiXj[3][0]=-0.394337567297407;
//				dNiXj[0][1]=-0.394337567297407; dNiXj[1][1]=-0.105662432702594; dNiXj[2][1]=0.105662432702594; dNiXj[3][1]=0.394337567297407;
//
//				break;
//		}
//
//		// dXi/d(xi)
//		Jacobian[0][0] = CoordCorn[0][0]*dNiXj[0][0] + CoordCorn[1][0]*dNiXj[1][0] + CoordCorn[2][0]*dNiXj[2][0] + CoordCorn[3][0]*dNiXj[3][0];
//		Jacobian[1][0] = CoordCorn[0][1]*dNiXj[0][0] + CoordCorn[1][1]*dNiXj[1][0] + CoordCorn[2][1]*dNiXj[2][0] + CoordCorn[3][1]*dNiXj[3][0];
//
//		// dXi/d(eta)
//		Jacobian[0][1] = CoordCorn[0][0]*dNiXj[0][1]+ CoordCorn[1][0]*dNiXj[1][1] + CoordCorn[2][0]*dNiXj[2][1] + CoordCorn[3][0]*dNiXj[3][1];
//		Jacobian[1][1] = CoordCorn[0][1]*dNiXj[0][1]+ CoordCorn[1][1]*dNiXj[1][1] + CoordCorn[2][1]*dNiXj[2][1] + CoordCorn[3][1]*dNiXj[3][1];
//
//		cout << Jacobian[0][0] << " " << Jacobian[1][0] << " " << Jacobian[0][1] << " " << Jacobian[1][1] << endl;
//
//		/*--- Adjoint to Jacobian ---*/
//
//		ad[0][0] = Jacobian[1][1];
//		ad[0][1] = -Jacobian[0][1];
//		ad[1][0] = -Jacobian[1][0];
//		ad[1][1] = Jacobian[0][0];
//
//		/*--- Determinant of Jacobian ---*/
//
//		detJac = ad[0][0]*ad[1][1]-ad[0][1]*ad[1][0];
//
//		GaussPoint[iGauss]->SetJ_X(detJac);
//
//		val_iGauss = GaussPoint[iGauss]->Get_iGauss();
//
//		cout << "val_iGauss " << val_iGauss << endl;
//		/*--- Jacobian inverse ---*/
//
////		for (i = 0; i < 2; i++) {
////		    for (j = 0; j < 2; j++) {
////		      Jacobian[i][j] = ad[i][j]/detJac;
////		    }
////		  }
//
//		/*--- Jacobian inverse and transpose (need to double check this) ---*/
//
//		for (i = 0; i < 2; i++) {
//		    for (j = 0; j < 2; j++) {
//		      Jacobian[i][j] = ad[j][i]/detJac;
//		    }
//		  }
//
//		for (iNode = 0; iNode < nNodes; iNode++){
//
//			for (iDim = 0; iDim < 2; iDim++) {
//			    for (j = 0; j < 2; j++) {
//			      GradNi_Xj += Jacobian[iDim][j]*dNiXj[iNode][j];		// Check this
//			    }
//			    GaussPoint[iGauss]->SetGradNi_Xj(GradNi_Xj, iDim, iNode);
//			}
//		}
//	}
//
//	double GradN_X;
//
//	for (iNode = 0; iNode < nNodes; iNode++){
//		for (iGauss = 0; iGauss < nGaussPoints; iGauss++){
//			cout << iNode << " " << iGauss << " " ;
//			for (iDim = 0; iDim < nDim; iDim++){
//				GradN_X = GetGradNi_X(iNode, iGauss, iDim);
//				cout << GradN_X << " ";
//			}
//			cout << endl;
//		}
//	}
//}

void CQUAD4::ComputeGrad_Linear(void){

	  double Xi, Eta;
	  double Jacobian[2][2], dNiXj[4][2];
	  double detJac, GradNi_Xj;
	  double ad[2][2];
	  unsigned short iNode, iDim, jDim, iGauss;

	  for (iGauss = 0; iGauss < nGaussPoints; iGauss++){

		  Xi = GaussCoord[iGauss][0];
		  Eta = GaussCoord[iGauss][1];

		  /*--- dN/d xi, dN/d eta ---*/

		  dNiXj[0][0] = -0.25*(1.0-Eta); dNiXj[0][1] = -0.25*(1.0-Xi);
		  dNiXj[1][0] =  0.25*(1.0-Eta); dNiXj[1][1] = -0.25*(1.0+Xi);
		  dNiXj[2][0] =  0.25*(1.0+Eta); dNiXj[2][1] =  0.25*(1.0+Xi);
		  dNiXj[3][0] = -0.25*(1.0+Eta); dNiXj[3][1] =  0.25*(1.0-Xi);

		  /*--- Jacobian transformation ---*/
		  /*--- This does dX/dXi transpose ---*/

		  for (iDim = 0; iDim < 2; iDim++) {
			for (jDim = 0; jDim < 2; jDim++) {
			  Jacobian[iDim][jDim] = 0.0;
			  for (iNode = 0; iNode < 4; iNode++) {
				  Jacobian[iDim][jDim] = Jacobian[iDim][jDim]+RefCoord[iNode][jDim]*dNiXj[iNode][iDim];
			  }
			}
		  }

		  /*--- Adjoint to Jacobian ---*/

		  ad[0][0] = Jacobian[1][1];
		  ad[0][1] = -Jacobian[0][1];
		  ad[1][0] = -Jacobian[1][0];
		  ad[1][1] = Jacobian[0][0];

		  /*--- Determinant of Jacobian ---*/

		  detJac = ad[0][0]*ad[1][1]-ad[0][1]*ad[1][0];

		  GaussPoint[iGauss]->SetJ_X(detJac);

		  /*--- Jacobian inverse (it was already computed as transpose) ---*/

		  for (iDim = 0; iDim < 2; iDim++) {
			for (jDim = 0; jDim < 2; jDim++) {
			  Jacobian[iDim][jDim] = ad[iDim][jDim]/detJac;
			}
		  }

		  /*--- Derivatives with respect to global coordinates ---*/

		  for (iNode = 0; iNode < 4; iNode++) {
			  for (iDim = 0; iDim < nDim; iDim++){
				  GradNi_Xj = 0.0;
				  for (jDim = 0; jDim < nDim; jDim++){
					  GradNi_Xj += Jacobian[iDim][jDim]*dNiXj[iNode][jDim];
				  }
				  GaussPoint[iGauss]->SetGradNi_Xj(GradNi_Xj, iDim, iNode);
			  }
		  }
	  }

}

void CQUAD4::ComputeGrad_NonLinear(void){

	  double Xi, Eta;
	  double Jac_Ref[2][2], Jac_Curr[2][2], dNiXj[4][2];
	  double detJac_Ref, detJac_Curr, GradNi_Xj_Ref, GradNi_Xj_Curr;
	  double ad_Ref[2][2], ad_Curr[2][2];
	  unsigned short iNode, iDim, jDim, iGauss;

	  for (iGauss = 0; iGauss < nGaussPoints; iGauss++){

		  Xi = GaussCoord[iGauss][0];
		  Eta = GaussCoord[iGauss][1];

		  /*--- dN/d xi, dN/d eta ---*/

		  dNiXj[0][0] = -0.25*(1.0-Eta); dNiXj[0][1] = -0.25*(1.0-Xi);
		  dNiXj[1][0] =  0.25*(1.0-Eta); dNiXj[1][1] = -0.25*(1.0+Xi);
		  dNiXj[2][0] =  0.25*(1.0+Eta); dNiXj[2][1] =  0.25*(1.0+Xi);
		  dNiXj[3][0] = -0.25*(1.0+Eta); dNiXj[3][1] =  0.25*(1.0-Xi);

		  /*--- Jacobian transformation ---*/
		  /*--- This does dX/dXi transpose ---*/

		  for (iDim = 0; iDim < 2; iDim++) {
			for (jDim = 0; jDim < 2; jDim++) {
			  Jac_Ref[iDim][jDim] = 0.0;
			  Jac_Curr[iDim][jDim] = 0.0;
			  for (iNode = 0; iNode < 4; iNode++) {
				  Jac_Ref[iDim][jDim] = Jac_Ref[iDim][jDim]+RefCoord[iNode][jDim]*dNiXj[iNode][iDim];
				  Jac_Curr[iDim][jDim] = Jac_Curr[iDim][jDim]+RefCoord[iNode][jDim]*dNiXj[iNode][iDim];
			  }
			}
		  }

		  /*--- Adjoint to Jacobian ---*/

		  ad_Ref[0][0] = Jac_Ref[1][1];
		  ad_Ref[0][1] = -Jac_Ref[0][1];
		  ad_Ref[1][0] = -Jac_Ref[1][0];
		  ad_Ref[1][1] = Jac_Ref[0][0];

		  ad_Curr[0][0] = Jac_Curr[1][1];
		  ad_Curr[0][1] = -Jac_Curr[0][1];
		  ad_Curr[1][0] = -Jac_Curr[1][0];
		  ad_Curr[1][1] = Jac_Curr[0][0];

		  /*--- Determinant of Jacobian ---*/

		  detJac_Ref = ad_Ref[0][0]*ad_Ref[1][1]-ad_Ref[0][1]*ad_Ref[1][0];
		  detJac_Curr = ad_Curr[0][0]*ad_Curr[1][1]-ad_Curr[0][1]*ad_Curr[1][0];

		  GaussPoint[iGauss]->SetJ_X(detJac_Ref);
		  GaussPoint[iGauss]->SetJ_x(detJac_Curr);

		  /*--- Jacobian inverse (it was already computed as transpose) ---*/

		  for (iDim = 0; iDim < 2; iDim++) {
			for (jDim = 0; jDim < 2; jDim++) {
				Jac_Ref[iDim][jDim] = ad_Ref[iDim][jDim]/detJac_Ref;
				Jac_Curr[iDim][jDim] = ad_Curr[iDim][jDim]/detJac_Curr;
			}
		  }


		  cout << detJac_Ref << " " << detJac_Curr << endl;

		  /*--- Derivatives with respect to global coordinates ---*/

		  for (iNode = 0; iNode < 4; iNode++) {
			  for (iDim = 0; iDim < nDim; iDim++){
				  GradNi_Xj_Ref = 0.0;
				  GradNi_Xj_Curr = 0.0;
				  for (jDim = 0; jDim < nDim; jDim++){
					  GradNi_Xj_Ref += Jac_Ref[iDim][jDim]*dNiXj[iNode][jDim];
					  GradNi_Xj_Curr += Jac_Curr[iDim][jDim]*dNiXj[iNode][jDim];
				  }
				  GaussPoint[iGauss]->SetGradNi_Xj(GradNi_Xj_Ref, iDim, iNode);
				  GaussPoint[iGauss]->SetGradNi_xj(GradNi_Xj_Curr, iDim, iNode);
			  }
		  }
	  }

}

void CQUAD4::OutputGradN_X(CGeometry *geometry, CConfig *config){

	unsigned short iNode, iDim, iGauss, i, j;
	double number;

//	number = GaussPoint[0]->GetGradNi_Xj(iNode,iDim);
//
//	for (iGauss = 0; iGauss < nGaussPoints ; iGauss++){
//		cout << iGauss << " ";
//		for (iNode = 0; iNode < nNodes; iNode++){
//			cout << iNode << " ";
//			for (iDim = 0; iDim < nDim; iDim++){
//				number = GaussPoint[iGauss]->GetGradNi_Xj(iNode,iDim);
//				cout << number << " ";
//			}
//			cout << endl;
//		}
//
//	}



}







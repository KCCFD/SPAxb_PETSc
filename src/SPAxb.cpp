#include <bits/stdc++.h>
#include <petsc.h> 
#include <petscsys.h>

using namespace std;


//      0  1  2  3  4  5  6  7  8  9  10  11  12  13  14  15
//
//     |-4 1  0  1  0  0  0  0  0  0  0   0   0   0   0   0|  0
//     |1 -4  1  0  1  0  0  0  0  0  0   0   0   0   0   0|  1
//     |0  1 -4  1  0  1  0  1  0  0  0   0   0   0   0   0|  2
//     |1  0  1 -4  0  0  0  0  1  0  0   0   0   0   0   0|  3
//     |0  1  0  0 -4  1  0  0  0  1  0   0   0   0   0   0|  4
//     |0  0  1  0  1 -4  1  0  0  0  1   0   0   0   0   0|  5
//     |0  0  0  0  0  1 -4  1  0  0  0   1   0   1   0   0|  6
// A = |0  0  1  0  0  0  1 -4  1  0  0   0   0   0   1   0|  7
//     |0  0  0  1  0  0  0  1 -4  0  0   0   0   0   0   1|  8
//     |0  0  0  0  1  0  0  0  0 -4  1   0   0   0   0   0|  9
//     |0  0  0  0  0  1  0  0  0  1 -4   1   0   0   0   0|  10
//     |0  0  0  0  0  0  1  0  0  0  1  -4   1   0   0   0|  11
//     |0  0  0  0  0  0  0  0  0  0  0   1  -4   1   0   0|  12
//     |0  0  0  0  0  0  1  0  0  0  0   0   1  -4   1   0|  13
//     |0  0  0  0  0  0  0  1  0  0  0   0   0   1  -4   1|  14
//     |0  0  0  0  0  0  0  0  1  0  0   0   0   0   1  -4|  15

std::vector<int> q1,q2,q3,q4; //neighbour cells
std::vector<int> COL, ROW, ROW_ptr;
std::vector<double> VAL, b, x;


int m, matsize; //matrix size
double nnz; //total no: of non-zeros in matrix

Mat Pet_A;
Vec Pet_b, Pet_x, Pet_xdump;
KSP ksp;
PC  prec;

int    f_argc;
char **f_argv;


void meshread()
{

	fstream fin;
	fin.open(f_argv[1], ios::in);
	if(fin.fail())
		cerr<<"Error!! No Grid file found!!!"<<endl;


	int a,b,c,d,e;
	string str;
	int count = 0;
	
	while(fin>>a>>b>>c>>d>>e)
	{
		q1.push_back(b);
		q2.push_back(c);
		q3.push_back(d);
		q4.push_back(e);
		count++;
	}

	m=count;

	matsize=count;
	cout<<"matrix size : "<<matsize<<endl;


}

void resize_vect()
{
	b.resize(matsize,0.0);
	x.resize(matsize,0.0);

}

void matset_COO()
{
	for(int i=0; i<m; i++)
	{
		COL.push_back(i);
		ROW.push_back(i);
		VAL.push_back(-4.0);
		if(q1[i]!=-1)
		{
			COL.push_back(q1[i]);
			ROW.push_back(i);
			VAL.push_back(1.0);
		}
		if(q2[i]!=-1)
		{
			COL.push_back(q2[i]);
			ROW.push_back(i);
			VAL.push_back(1.0);
		}
		if(q3[i]!=-1)
		{
			COL.push_back(q3[i]);
			ROW.push_back(i);
			VAL.push_back(1.0);
		}
		if(q4[i]!=-1)
		{
			COL.push_back(q4[i]);
			ROW.push_back(i);
			VAL.push_back(1.0);
		}


	}

	cout<<"Col_vector size: "<<COL.size()<<endl;

	

}


void matset_CSR()
{
	int n=1;
	ROW_ptr.push_back(0);
	for(int i=1; i<nnz; i++)
	{

		if(ROW[i]!=ROW[i-1])
		{
			ROW_ptr.push_back(i);
		n++;
		}

	}
	ROW_ptr.push_back(nnz);



	/** Arrange array in ascending order starting from left end of row **/
	// CELL-NEIGHBOUR data need to be sorted in ascending order for each row in matrix //
for(int i=0;i<n;i++)
{

int temp;
double temp1;
for(int j=ROW_ptr[i];j<=ROW_ptr[i+1]-1;j++)
{

temp=0;
temp1=0.0;
for(int k=j+1;k<=ROW_ptr[i+1]-1;k++)
{
if(COL[j]>COL[k])
{
temp=COL[j];
temp1=VAL[j];
COL[j]=COL[k];
VAL[j]=VAL[k];
COL[k]=temp;
VAL[k]=temp1;
}
}

}
}



}

void tempvector_destroy()
{
	std::vector<int>().swap(q1);
	std::vector<int>().swap(q2);
	std::vector<int>().swap(q3);
	std::vector<int>().swap(q4);
}

void vecbx_destroy()
{
	std::vector<double>().swap(x);
	std::vector<double>().swap(b);
}

void matCSR_destroy()
{
	std::vector<int>().swap(COL);
	std::vector<int>().swap(ROW);
	std::vector<int>().swap(ROW_ptr);
	std::vector<double>().swap(VAL);

}


int main(int argc, char **argv)
{

	f_argc = argc;
    	f_argv = argv;

	meshread();
	resize_vect();
	matset_COO();
	tempvector_destroy();
	nnz = COL.size(); //no. of non-zero entries
	matset_CSR();
	
	assert(COL.size()==VAL.size());

	cout <<"No. of arguments: "<<argc<<"\t Grid File path: "<<argv[1]<<endl;


PetscErrorCode ierr;
PetscMPIInt rank;
PetscInt startind, endind;
PetscInt Ii;


PetscInitialize(&argc, &argv, NULL, "Axb : \n");


ierr = MPI_Comm_rank(PETSC_COMM_WORLD, &rank);

//VecCreate//

VecCreate(PETSC_COMM_WORLD, &Pet_b);
VecSetSizes(Pet_b, PETSC_DECIDE, m);
VecSetFromOptions(Pet_b);

VecDuplicate(Pet_b, &Pet_xdump);

MatCreate(PETSC_COMM_WORLD, &Pet_A);
MatSetSizes(Pet_A, PETSC_DECIDE, PETSC_DECIDE, m, m);//PETSC_DECIDE is used for MPI sets size for each processor.
MatSetFromOptions(Pet_A);


// MatVecSetValue //

VecSet(Pet_xdump, 1.0);
VecView(Pet_xdump, PETSC_VIEWER_STDOUT_SELF);


MatSetUp(Pet_A);
MatGetOwnershipRange(Pet_A, &startind, &endind);
for(Ii=startind; Ii<endind; Ii++)
{
	
	 int nz =  ROW_ptr[Ii+1] - ROW_ptr[Ii]; //no. of non-zeros per row
	 
	 int *col = new int [nz];
	 double *val = new double [nz];
	 
	 for(int i=0; i<nz; i++)
	 {
	 	col[i]=-1;
	 	val[i]=0.0;
	 }
	 

	 for(int j=ROW_ptr[Ii]; j<=ROW_ptr[Ii+1]-1; j++)
	 {
	 	int jj = j-ROW_ptr[Ii];
	 	//cout<<"jj : "<<jj<<endl;
	 	assert(jj<nz);

	 	col[jj] = COL[j];
	 	val[jj] = VAL[j];

	 	MatSetValues(Pet_A, 1, &Ii, nz, col, val, INSERT_VALUES);

	 }

	 delete[] col;
	 delete[] val;

}


MatAssemblyBegin(Pet_A, MAT_FINAL_ASSEMBLY);
MatAssemblyEnd(Pet_A, MAT_FINAL_ASSEMBLY);

MatMult(Pet_A, Pet_xdump, Pet_b);
//VecView(Pet_b, PETSC_VIEWER_STDOUT_WORLD);

// KSP Solve Ax=b //

KSPCreate(PETSC_COMM_WORLD, &ksp);
KSPSetOperators(ksp, Pet_A, Pet_A);


KSPSetType(ksp, KSPGMRES);
KSPSetInitialGuessNonzero(ksp, PETSC_TRUE);

 
KSPGetPC(ksp, &prec);
PCSetType(prec, PCGAMG);

KSPSetFromOptions(ksp);//check for different options such as print residuals
KSPSetUp(ksp);

VecDuplicate(Pet_b, &Pet_x);

//VecZeroEntries(Pet_x);
KSPSolve(ksp, Pet_b, Pet_x);



VecView(Pet_x, PETSC_VIEWER_STDOUT_SELF);



// MatVecDestroy //

VecDestroy(&Pet_b);
VecDestroy(&Pet_x);
VecDestroy(&Pet_xdump);
MatDestroy(&Pet_A);


return PetscFinalize();

vecbx_destroy();
matCSR_destroy();


}

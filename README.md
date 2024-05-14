# SPAxb
This project shows how to develop and solve sparse Ax=b system. PETSc is utilised for the iterative solution.
Each row of matrix A has non-zero entires of the form (1,1,4,1,1) that is typical of a matrix obtained from descritized Laplacian operator on an orthogonal two dimensional mesh using conventional numerical techniques such as finite difference or finite volume method. For structured (IJK ordering) mesh, the discretization yields a banded matrix. For this project, the mesh cells are counter-clockwise ordered as given below.

  _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 
 |           |           |           |           |     
 |    (15)   |    (14)   |    (13)   |    (12)   |
 |           |           |           |           |
 |_ _ _ _ _ _|_ _ _ _ _ _| _ _ _ _ _ | _ _ _ _ _ |
 |           |           |           |           |
 |    (8)    |    (7)    |    (6)    |    (11)   |
 |           |           |           |           |
 |_ _ _ _ _ _|_ _ _ _ _ _|_ _ _ _ _ _| _ _ _ _ _ | 
 |           |           |           |           |
 |    (3)    |    (2)    |    (5)    |    (10)   |
 |           |           |           |           |
 |_ _ _ _ _ _|_ _ _ _ _ _|_ _ _ _ _ _| _ _ _ _ _ |   
 |           |           |           |           |
 |    (0)    |    (1)    |    (4)    |    (9)    |
 |           |           |           |           |
 |_ _ _ _ _ _|_ _ _ _ _ _|_ _ _ _ _ _| _ _ _ _ _ | 

 
The resulting matrix size is 16x16. The above cell ordering results in a sparse matrix with increasing bandwidth with cell number. Each cell corresponds to a matrix entry typical to that of cell-based finite volume/finite difference discretization.

A grid file is provided "grid.out" that shows the cell-cell connectivity. For interior cells (2,5,6,7) there are 4 neighbours, hence the number of non-zero entries are 5 including the parent cell number. For boundary cells (0,1,3,4,8,9,10,11,12,13,14,15) the number of neighbouring cells are less than 4, hence the non-zero entries in the corresponding rows are less than 5. In the grid file "grid.dat", the corresponding entries of the boundary cells where neighbours are absent are labelled '-1'.

After reading the cell connectivity data from the grid file the matrix entries are first stored in the CO-Ordinate (COO) format with entires stored in column-index (COL), row-index (ROW) and matrix value (VAL) arrays. The COO format is converted to Compressed Sparse Row (CSR) format with ROW entiries converted to row-pointer (ROW_ptr) array of size (n+1), where n is the matrix size. The no: of non-zero entries in the matrix is denoted as 'nnz'. List of arrays used for matrix storage are as follows:

Arrays         size
COL             nnz
ROW             nnz
VAL             nnz
ROW_ptr         (n+1)

Matrix system Ax=b solution:
------------------------------
- PETSc is used for the iterative solution of Ax=b with GMRES as iterative solver and GAMG as preconditioner.
- b-vector is calculated by multiplying matrix A with a dummy vector dump_x of ones.
- After Ax=b solve, the resulting x-vector should be returned as ones of dimensions 'nx1'.

Code execution
------------------------------
- The code utilizes PETSc and hence the execution follows PETSc procedure. CMake is used for compilation. For linking PETSc using CMake, the procedure given in the following link may be used:
  ```
  https://github.com/KCCFD/Linking-PETSc-using-CMake-MPI-HelloWorld
  ```
- The file path to grid file should be given as the second (2nd) command line argument. The grid file "grid.dat" is stored in "/include/" folder.  eg:
  ```
  $PETSC_DIR/$PETSC_ARCH/bin/mpirun -n 1 ./SPAxb "path to grid file <grid.dat>"
  ```                                                
  
NOTE: The code gives a rough idea of how matrix systems are formed for unstructured cell-based finite volume formulation. The code handles any type of mesh cell ordering and is not restricted to the one used for the project provided the cell-cell connectivity follows the same format as given in the grid file "grid.dat".

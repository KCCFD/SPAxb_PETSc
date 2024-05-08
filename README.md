# SPAxb
This project shows how to develop and solve sparse Ax=b system. PETSc is utilised for the iterative solution.
Each row of matrix A has non-zero entires of the form (1,1,4,1,1) that is typical of a matrix obtained from descritized Laplacian operator on an orthogonal two dimensional mesh using conventional numerical techniques such as finite difference or finite volume method. For structured mesh, the discretization yields a banded matrix.

# SPAxb
This project shows how to develop and solve sparse Ax=b system. PETSc is utilised for the iterative solution.
Each row of matrix A has non-zero entires of the form (1,1,4,1,1) that is typical of a matrix obtained from descritized Laplacian operator on an orthogonal two dimensional mesh using conventional numerical techniques such as finite difference or finite volume method. For structured (IJK ordering) mesh, the discretization yields a banded matrix. For this project, the mesh cells are anti-clockwise ordered as given below.

  _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 
 |           |           |           |           |     
 |    (15)   |    (14)   |    (13)   |    (12)   |
 |           |           |           |           |
 |_ _ _ _ _ _|_ _ _ _ _ _| _ _ _ _ _ | _ _ _ _ _ |
 |           |           |           |           |
 |    (8)    |   (7)     |    (6)    |    (11)   |
 |           |           |           |           |
 |_ _ _ _ _ _|_ _ _ _ _ _|_ _ _ _ _ _| _ _ _ _ _ | 
 |           |           |           |           |
 |    (3)    |   (2)     |     (5)   |    (10)   |
 |           |           |           |           |
 |_ _ _ _ _ _|_ _ _ _ _ _|_ _ _ _ _ _| _ _ _ _ _ |   
 |           |           |           |           |
 |    (0)    |    (1)    |     (4)   |    (9)    |
 |           |           |           |           |
 |_ _ _ _ _ _|_ _ _ _ _ _|_ _ _ _ _ _| _ _ _ _ _ | 

 
The resulting matrix size is 16x16. The above cell ordering results in a sparse matrix with increasing bandwidth with cell number. Each cell corresponds to a matrix entry typical to that of finite volume discretization.

# SPAxb
This project shows how to develop and solve sparse Ax=b system. PETSc is utilised for the iterative solution.
Each row of matrix A has non-zero entires of the form (1,1,4,1,1) that is typical of a matrix obtained from descritized Laplacian operator on an orthogonal two dimensional mesh using conventional numerical techniques such as finite difference or finite volume method. For structured (IJK ordering) mesh, the discretization yields a banded matrix. For this project, the mesh cells anti-clockwise ordered as given below.

 _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 
 |           |           |           |           |     
 |    (16)   |    (15)   |    (14)   |    (13)   |
 |           |           |           |           |
 |_ _ _ _ _ _|_ _ _ _ _ _| _ _ _ _ _ | _ _ _ _ _ |
 |           |           |           |           |
 |    (9)    |   (8)     |    (7)    |    (12)   |
 |           |           |           |           |
 |_ _ _ _ _ _|_ _ _ _ _ _|_ _ _ _ _ _| _ _ _ _ _ | 
 |           |           |           |           |
 |    (4)    |   (3)     |     (6)   |    (11)   |
 |           |           |           |           |
 |_ _ _ _ _ _|_ _ _ _ _ _|_ _ _ _ _ _| _ _ _ _ _ |   
 |           |           |           |           |
 |    (1)    |    (2)    |     (5)   |    (10)   |
 |           |           |           |           |
 |_ _ _ _ _ _|_ _ _ _ _ _|_ _ _ _ _ _| _ _ _ _ _ | 

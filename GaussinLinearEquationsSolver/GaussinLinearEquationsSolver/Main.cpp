#include <iostream>


class GaussianMatrixSolver
{
public:

	GaussianMatrixSolver(int size)
	{
		this->MATRIX_SIZE = size;
	}

	void gaussianElimination(double** matrix)
	{
		/* reduction into r.e.f. */
		int singular_flag = forwardElim(matrix);

		/* if matrix is singular */
		if (singular_flag != -1)
		{
			std::cout << "Singular Matrix.\n";

			/* if the RHS of equation corresponding to
			   zero row  is 0, * system has infinitely
			   many solutions, else inconsistent*/
			if (matrix[singular_flag][MATRIX_SIZE])
			{
				std::cout << "Inconsistent System.";
			}
			else
			{
				std::cout << "May have infinitely many " 
					<<"solutions.";
			}

			return;
		}

		/* get solution to system and print it using
		   backward substitution */
		backSub(matrix);
	}

	// function for elementary operation of swapping two rows 
	void swap_row(double** mat, int i, int j)
	{
		//printf("Swapped rows %d and %d\n", i, j); 

		for (int k = 0; k <= MATRIX_SIZE; k++)
		{
			double temp = mat[i][k];
			mat[i][k] = mat[j][k];
			mat[j][k] = temp;
		}
	}

	// function to print matrix content at any stage 
	void print(double** mat)
	{
		for (int i = 0; i < MATRIX_SIZE; i++, std::cout << " \n")
		{
			for (int j = 0; j <= MATRIX_SIZE; j++)
			{
				if (j == MATRIX_SIZE)
				{
					std::cout << "| ";
				}
				std::cout << mat[i][j] << "   ";
			}
		}
		std::cout << "" << std::endl;
	}
private:
	// function to reduce matrix to r.e.f. 
	int forwardElim(double** mat)
	{
		for (int k = 0; k < MATRIX_SIZE; k++)
		{
			// Initialize maximum value and index for pivot 
			int i_max = k;
			int v_max = mat[i_max][k];

			/* find greater amplitude for pivot if any */
			for (int i = k + 1; i < MATRIX_SIZE; i++)
			{
				if (abs(mat[i][k]) > v_max)
				{
					v_max = mat[i][k], i_max = i;
				}
			}
			/* if a prinicipal diagonal element  is zero,
			 * it denotes that matrix is singular, and
			 * will lead to a division-by-zero later. */
			if (!mat[k][i_max])
			{
				return k; // Matrix is singular 
			}
			/* Swap the greatest value row with current row */
			if (i_max != k)
			{
				swap_row(mat, k, i_max);
			}

			for (int i = k + 1; i < MATRIX_SIZE; i++)
			{
				/* factor f to set current row kth element to 0,
				 * and subsequently remaining kth column to 0 */
				double f = mat[i][k] / mat[k][k];

				/* subtract fth multiple of corresponding kth
				   row element*/
				for (int j = k + 1; j <= MATRIX_SIZE; j++)
				{
					mat[i][j] -= mat[k][j] * f;
				}
				/* filling lower triangular matrix with zeros*/
				mat[i][k] = 0;
			}

			//print(mat);        //for matrix state 
		}
		//print(mat);            //for matrix state 
		return -1;
	}

	// function to calculate the values of the unknowns 
	void backSub(double** mat)
	{
		double* x = new double[MATRIX_SIZE];  // An array to store solution 

		/* Start calculating from last equation up to the
		   first */
		for (int i = MATRIX_SIZE - 1; i >= 0; i--)
		{
			/* start with the RHS of the equation */
			x[i] = mat[i][MATRIX_SIZE];

			/* Initialize j to i+1 since matrix is upper
			   triangular*/
			for (int j = i + 1; j < MATRIX_SIZE; j++)
			{
				/* subtract all the lhs values
				 * except the coefficient of the variable
				 * whose value is being calculated */
				x[i] -= mat[i][j] * x[j];
			}

			/* divide the RHS by the coefficient of the
			   unknown being calculated */
			x[i] = x[i] / mat[i][i];
		}

		std::cout << "Solution for the system:" << std::endl;
		for (int i = 0; i < MATRIX_SIZE; i++)
		{
			std::cout <<  (double)x[i] << std::endl;
		}
	}

	int MATRIX_SIZE;
};

const int N = 5;


int main(int argc, char** argv)
{
	double* vector1 = new double[N + 1]{ 3.0, 2.0,-4.0, 3.0, 5.0, 45.0 };
	double* vector2 = new double[N + 1]{ 2.0, 3.0, 3.0, 15.0, 7.0, 21.0 };
	double* vector3 = new double[N + 1]{ 5.0, -3, 1.0, 14.0, 34.0, 12.0 };
	double* vector4 = new double[N + 1]{ 7.0, -8, 4.0, 1.0, 17.0, 7.0 };
	double* vector5 = new double[N + 1]{ 5.0, -14, 22.0, 44.0, 17.0, 2.0 };
	double** gaussian_matrix = new double*[N + 1]{vector1, vector2, vector3, vector4, vector5};
						 
	GaussianMatrixSolver* sovler = new GaussianMatrixSolver(N);
	sovler->print(gaussian_matrix);
	sovler->gaussianElimination(gaussian_matrix);
	getchar();


	return 0;
}
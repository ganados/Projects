#include <stdlib.h>
#include <stdio.h>

//display matrix
void displayMatrix(double** matrix, int size) {
	int i, j;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			printf("%10lf ", matrix[i][j]);
		}
		printf("\n");
	}
}

void displayOneDimen(double* matrix, int size) {
	int i;
	for (i = 0; i < size; i++) {
		printf("%lf\n", matrix[i]);
	}
}

//calculation of lower and upper matrix
void LUcalc(double** lowerMatrix, double** upperMatrix, double** matrixCoefficient, int size) {
	int i, j, k;
	double sumOfRows = 0;
	for (i = 0; i < size; i++) {
		for (k = i; k < size; k++) {
			for (j = 0; j < i; j++) {
				sumOfRows += (lowerMatrix[i][j] * upperMatrix[j][k]);
			}
			upperMatrix[i][k] = matrixCoefficient[i][k] - sumOfRows;
			sumOfRows = 0;
		}
		sumOfRows = 0;
		for (k = i; k < size; k++) {
			if(i==k) lowerMatrix[i][i] = 1;
			else {
				 for (j = 0; j < i; j++) {
			 		sumOfRows += (lowerMatrix[k][j] * upperMatrix[j][i]);
				 }
				 lowerMatrix[k][i] = (matrixCoefficient[k][i] - sumOfRows) / upperMatrix[i][i];
				 sumOfRows = 0;
			}
		}
	}
}

//checking the correctness of calculations
void matrixMultiplication(double** a, double** b, double** checkingMatrix, int size) {
	double sumOfRows = 0;
	int i, j, k;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			for (k = 0; k < size; k++) {
				checkingMatrix[i][j] += a[i][k] * b[k][j];
			}
		}
	}
}

//LUmethod calculation
void lowerCalc(double** lowerMatrix, double* freeWordsMatrix, double* z, int size) {
	int i, j; double trash = 0;
	z[0] = freeWordsMatrix[0] / lowerMatrix[0][0];
	for (i = 1; i < size; i++) {
		trash = 0;
		for (j = 0; j < i; j++) {
			trash += lowerMatrix[i][j] * z[j];
		}
		z[i] = freeWordsMatrix[i] - trash;
	}
}

void upperCalc(double** upperMatrix, double* z, double* x, int size) {
	int i, j;
	double trash=0;
	for (i = size-1; i >= 0; i--) {
		trash = 0;
		for (j = i + 1; j < size; j++) {
			trash += upperMatrix[i][j] * x[j];
		}
		x[i] = (z[i] - trash) / upperMatrix[i][i];
	}
}




int main() {
	
	int size;
	printf("\nType size of matrix: ");
	scanf_s("%d", &size);


	//memory allocation
	double* matrixOfX = (double*)malloc(size * 8);
	double* freeWordsMatrix = (double**)malloc(size * 8);

	double** checkingMatrix = (double**)malloc(size * 8);
	double** matrixCoefficient = (double**)malloc(size * 8);
	double** lowerMatrix = (double**)malloc(size * 8);
	double** upperMatrix = (double**)malloc(size * 8);
	
	int i, j;
	if (lowerMatrix[0] == NULL || upperMatrix[0] == NULL || matrixCoefficient[0] == NULL || checkingMatrix[0] == NULL) {
		perror("");
	}
	else {
		for (i = 0; i < size; i++) {
			lowerMatrix[i] = (double*)malloc(size * 8);
			upperMatrix[i] = (double*)malloc(size * 8);
			matrixCoefficient[i] = (double*)malloc(size * 8);
			checkingMatrix[i] = (double*)malloc(size * 8);
		}
		for (i = 0; i < size; i++) {
			for (j = 0; j < size; j++) {
				lowerMatrix[i][j] = 0;
				upperMatrix[i][j] = 0;
				matrixCoefficient[i][j] = 0;
				checkingMatrix[i][j] = 0;
			}
			freeWordsMatrix[i] = 0;
		}

		//data entry
		for (i = 0; i < size; i++) {
			for (j = 0; j < size; j++) {
				matrixCoefficient[i][j] = (double)(rand() % 10) + 1.0;	
			}
			freeWordsMatrix[i] = (double)(rand() % 10) + 1.0;
		}

		printf("\nMAIN matrix\n");
		displayMatrix(matrixCoefficient, size);
		LUcalc(lowerMatrix, upperMatrix, matrixCoefficient, size);
		printf("\nLOWER matrix\n");
		displayMatrix(lowerMatrix, size);
		printf("\nUPPER matrix\n");
		displayMatrix(upperMatrix, size);
		printf("\nCHECKING matrix   L*U == main\n");
		matrixMultiplication(lowerMatrix, upperMatrix, checkingMatrix, size);
		displayMatrix(checkingMatrix, size);
		printf("\nFREE WORDS MATRIX\n");
		for (i = 0; i < size; i++) {
				printf("%lf\n", freeWordsMatrix[i]);
		}

	
	printf("\nRESULT\n\n");

	double* z = (double*)malloc(size * 8);
	double* x = (double*)malloc(size * 8);
	lowerCalc(lowerMatrix, freeWordsMatrix, z, size);
	upperCalc(upperMatrix, z, x, size);
	displayOneDimen(x, size);
	free(z);
	free(x);
	}


	//memory release
	for (i = 0; i < size; i++) {
			free(lowerMatrix[i]);
			free(upperMatrix[i]);
			free(matrixCoefficient[i]);
			free(checkingMatrix[i]);
		}
	free(lowerMatrix);
	free(upperMatrix);
	free(matrixCoefficient);
	free(checkingMatrix);
	free(freeWordsMatrix);
	
	return 0;
}
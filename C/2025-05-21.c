void setZeroes(int** matrix, int matrixSize, int* matrixColSize) {
  // use first row and column as the boolean value for said row/column
  bool first_row_zero = false;
  bool first_col_zero = false;

  for (int i = 0; i < matrixSize; i++){
    if (matrix[i][0] == 0) first_col_zero = true;
  }

  for (int i = 0; i < matrixColSize[0]; i++){
    if (matrix[0][i] == 0) first_row_zero = true;
  }

  for (int i = 1; i < matrixSize; i++){
    for (int j = 1; j < matrixColSize[0]; j++){
      if (matrix[i][j] == 0){
	matrix[i][0] = 0;
	matrix[0][j] = 0;
      }
    }
  }

  for (int i = 1; i < matrixSize; i++){
    for (int j = 1; j < matrixColSize[0]; j++){
      if (matrix[i][0] == 0){
	matrix[i][j] = 0;
      }
      if (matrix[0][j] == 0){
	matrix[i][j] = 0;
      }
    }
  }

  if (first_col_zero){
    for (int i = 0; i < matrixSize; i++){
      matrix[i][0] = 0;
    }
  }

  if (first_row_zero){
    for (int i = 0; i < matrixColSize[0]; i++){
      matrix[0][i] = 0;
    }
  }
}

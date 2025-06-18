int cmp(const void *a, const void *b) {
  return (*(int*)a - *(int*)b);
}

int **divideArray(int *nums, int numsSize, int k, int *returnSize, int **returnColumnSizes) {
  qsort(nums, numsSize, sizeof(int), cmp);
  int numRows = numsSize / 3;
  *returnSize = numRows;
  int** result = malloc(numRows * sizeof(int*));
  for (int i = 0; i < numRows; i++) {
    result[i] = malloc(3 * sizeof(int));
  }
  *returnColumnSizes = malloc(numRows * sizeof(int));
  for (int i = 0; i < numRows; i++) {
    (*returnColumnSizes)[i] = 3;
  }
  int colDex = 0, dex = 0;
  for (int i = 0; i < numsSize; i++) {
    if (dex == 0) result[colDex][dex++] = nums[i];
    else if (abs(result[colDex][0] - nums[i]) > k) {
      *returnSize = 0;
      return result;
    } else {
      result[colDex][dex++] = nums[i];
    }
    if (dex == 3) {
      dex = 0;
      colDex++;
    }
  }  
  return result;  
}

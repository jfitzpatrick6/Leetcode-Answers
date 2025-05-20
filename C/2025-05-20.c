bool isZeroArray(int* nums, int numsSize, int** queries, int queriesSize, int* queriesColSize) {
  int* diff = (int*)calloc(numsSize + 1, sizeof(int));
  for (int i = 0; i < queriesSize; i++){
    int l = queries[i][0];
    int r = queries[i][1];
    diff[l]++;
    diff[r + 1]--;
  }
  int *maxDec = (int*)malloc(numsSize * sizeof(int));
  int cur = 0;
  for (int i = 0; i < numsSize; i++){
    cur += diff[i];
    maxDec[i] = cur;
  }
  for (int i = 0; i < numsSize; i++){
    if (nums[i] > maxDec[i]){
      free(diff);
      free(maxDec);
      return false;
    }
  }
  return true;
}

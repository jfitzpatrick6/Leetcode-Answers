int maximumDifference(int *nums, int numsSize) {
  int max = -1;
  for (int i = 0; i < numsSize; i++) {
    for (int j = i + 1; j < numsSize; j++) {
      if (nums[j] > nums[i]) {
	int new = nums[j] - nums[i];
	max = new > max ? new : max;
      }
    }
  }
  return max;
}

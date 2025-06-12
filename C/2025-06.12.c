int maxAdjacentDistance(int *nums, int numsSize) {
  int maxDiff = 0;
  for (int i = 0; i < numsSize; i++) {
    if (i == 0) {
      int diff = abs(nums[i] - nums[numsSize - 1]);
      maxDiff = maxDiff < diff ? diff : maxDiff;
    } else if (i == numsSize - 1) {
      int diff = abs(nums[i] - nums[0]);
      maxDiff = maxDiff < diff ? diff : maxDiff;
    } else {
      int diff = abs(nums[i] - nums[i + 1]);
      maxDiff = maxDiff < diff ? diff : maxDiff;
      diff = abs(nums[i] - nums[i - 1]);
      maxDiff = maxDiff < diff ? diff : maxDiff;
    }
  }
  return maxDiff;
}

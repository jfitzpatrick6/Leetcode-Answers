long long maximumValueSum(int* nums, int numsSize, int k, int** edges, int edgesSize, int* edgesColSize) {
  int swapn = 0, min = -1, max = 1, existmirror = 0;
  long long maximumValueSum = 0;
  for (int i = 0; i < numsSize; i++) {
    if ((nums[i] ^ k) == nums[i]) existmirror = 1;
    else if ((nums[i] ^ k) > nums[i]) {
      swapn++;
      if ((nums[i] ^ k) - nums[i] < min | min == -1) min = (nums[i] ^ k) - nums[i];
      nums[i] = (nums[i] ^ k);
    } else if ((nums[i] ^ k) - nums[i] > max | max == 1)
      max = (nums[i] ^ k) - nums[i];
  }

  for (int i = 0; i < numsSize; i++)
    maximumValueSum += nums[i];
  if (existmirror == 0 && swapn % 2 == 1)
    if (max + min > 0 && max != 1) maximumValueSum += max;
    else
      maximumValueSum -= min;
  return maximumValueSum;
}

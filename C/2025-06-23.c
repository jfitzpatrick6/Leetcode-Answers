long long int power(int base, int exp) {
  long long int result = 1;
  while (exp > 0) {
    if (exp % 2 == 1) result *= base;
    base *= base;
    exp /= 2;
  }
  return result;
}

bool checkPalindrome_baseK(long long int num, int k) {
  int *converted = malloc(sizeof(int) * 30);
  int index = 0;
  while (num > 0) {
    int rem = num % k;
    converted[index++] = rem;
    num /= k;
  }
  int start = 0, end = index - 1;
  while (start < end) {
    if (converted[start++] != converted[end--]) return false;
  }
  free(converted);
  return true;
}

long long kMirror(int k, int n) {
  long long sum = 0;
  int digit = 1;
  while (n > 0) {
    for (long int i = power(10, (digit - 1) / 2); i < power(10, (digit - 1) / 2 + 1); i++) {
      long int palin = i, inversed = i;
      if (digit % 2) inversed /= 10;
      while (inversed > 0) {
	palin = 10 * palin + inversed % 10;
	inversed /= 10;
      }
      if (checkPalindrome_baseK(palin, k)) {
	sum += palin; n--;
	if (n == 0) return sum;
      }
    }
    digit++;
  }
  return sum;
}

long long distributeCandies(int n, int limit) {
  // cant write three for loops because of constraints
  if (limit * 3 < n) return 0;
  long long distributions = 0;
  for (int i  = 0; i < (n < limit ? n + 1 : limit + 1); i++){
    int candies_left = n - i;
    if (limit >= candies_left) distributions += candies_left + 1;
    else {
      int count = limit - (candies_left - limit) + 1;
      distributions += count > 0 ? count : 0;
    }
  }
  return distributions;
}

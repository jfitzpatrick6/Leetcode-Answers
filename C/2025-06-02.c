int candy(int* ratings, int N) {
  int* indegree = calloc(N, sizeof(int));
  int* ans = calloc(N, sizeof(int));
  int* queue = malloc(N * sizeof(int));
  int front = 0, back = 0;

  for (int i = 0; i < N; i ++) {
    if (i - 1 >= 0 && ratings[i - 1] < ratings[i]) indegree[i]++;
    if (i + 1 < N && ratings[i + 1] < ratings[i]) indegree[i]++;
  }

  for (int i = 0; i < N; i++) {
    if (indegree[i] == 0) {
      queue[back++] = i;
    }
  }

  while (front < back) {
    int current = queue[front++];
    int candies = 1;
    if (current - 1 >= 0 && ratings[current - 1] < ratings[current]) {
      if (ans[current - 1] + 1 > candies) candies = ans[current - 1] + 1;
    }
    if (current + 1 < N && ratings[current + 1] < ratings[current]) {
      if (ans[current + 1] + 1 > candies) candies = ans[current + 1] + 1;
    }
    ans[current] = candies;
    if (current - 1 >= 0 && ratings[current - 1] > ratings[current]) {
      indegree[current - 1]--;
      if (indegree[current - 1] == 0) queue[back++] = current - 1;
    }
    if (current + 1 < N && ratings[current + 1] > ratings[current]) {
      indegree[current + 1]--;
      if (indegree[current + 1] == 0) queue[back++] = current + 1;
    }
  }

  int total = 0;
  for (int i = 0; i < N; i++) {
    total += ans[i];
  }

  free(indegree);
  free(ans);
  free(queue);

  return total;
}

#include <string.h>

#define INF 1000000000
#define MAX_LEN 100005

typedef struct {
  int ca[MAX_LEN];
  int cb[MAX_LEN];
  int prefix[MAX_LEN];
  int front, back;
} Deque;

void initDeque(Deque *dq) {
  dq->front = 0;
  dq->back = 0;
}

void pushBack(Deque *dq, int a, int b, int p) {
  dq->ca[dq->back] = a;
  dq->cb[dq->back] = b;
  dq->prefix[dq->back] = p;
  dq->back++;
}

void popFront(Deque *dq) {
  dq->front++;
}

int size(Deque *dq) {
  return dq->back - dq->front;
}

int calc(char a, char b, char *s, int k) {
  int ca = 0, cb = 0, prefix = 0;
  int best[2][2];
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++)
      best[i][j] = INF;

  Deque dq;
  initDeque(&dq);
  pushBack(&dq, 0, 0, 0);
  int highest = -INF;
  int n = strlen(s);
  for (int i = 0; i < n; i++) {
    char x = s[i];
    if (x == a) {
      ca += 1;
      prefix += 1;
    } else if (x == b) {
      cb += 1;
      prefix -= 1;
    }
    pushBack(&dq, ca, cb, prefix);
    while (size(&dq) > k) {
      int f = dq.front;
      if (dq.cb[f] == cb) break;
      int qa = dq.ca[f], qb = dq.cb[f], p = dq.prefix[f];
      int par_a = qa % 2, par_b = qb % 2;
      if (p < best[par_a][par_b]) best[par_a][par_b] = p;
      popFront(&dq);
    }
    int want_par = (1 - ca % 2 + 2) % 2;
    if (prefix - best[want_par][cb % 2] > highest)
      highest = prefix - best[want_par][cb % 2];
  }
  return highest;
}

int maxDifference(char* s, int k) {
  int bestOverall = -INF, n = strlen(s);
  int present[5] = {0}; // only digits '0' to '4'

  for (int i = 0; i < n; i++) {
    if (s[i] >= '0' && s[i] <= '4')
      present[s[i] - '0'] = 1;
  }

  for (int i = 0; i < 5; i++) {
    if (!present[i]) continue;
    for (int j = 0; j < 5; j++) {
      if (!present[j] || i == j) continue;
      int result = calc('0' + i, '0' + j, s, k);
      if (result > bestOverall)
        bestOverall = result;
    }
  }
  return bestOverall;
}

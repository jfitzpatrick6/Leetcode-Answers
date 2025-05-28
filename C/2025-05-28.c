/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#define INF 1000000000

typedef struct {
  int *data;
  int size;
  int capacity;
} Vector;

void initVector(Vector *v){
  v->capacity = 4;
  v->size = 0;
  v->data = malloc(sizeof(int) * v->capacity);
}

void pushVector(Vector *v, int value){
  if (v->size == v->capacity){
    v->capacity *= 2;
    v->data = realloc(v->data, sizeof(int) * v->capacity);
  }
  v->data[v->size++] = value;
}

void freeVector(Vector *v){
  free(v->data);
}

typedef struct {
  int *data;
  int front, back, size, capacity;
} Queue;

void initQueue(Queue *q, int capacity) {
  q->data = malloc(sizeof(int) * capacity);
  q->front = q->back = 0;
  q->size = 0;
  q->capacity = capacity;
}

void enqueue(Queue *q, int value){
  if (q->size == q->capacity) return;
  q->data[q->back++] = value;
  if (q->back == q->capacity) q->back = 0;
  q->size++;
}

int dequeue(Queue *q) {
  int val = q->data[q->front++];
  if (q->front == q->capacity) q->front = 0;
  q->size--;
  return val;
}

int isEmpty(Queue *q){
  return q->size == 0;
}

void freeQueue(Queue *q) {
  free(q->data);
}

int calculate(int N, Vector *adj, int node, int k){
  int *dist = malloc(sizeof(int) * N);
  for (int i = 0; i < N; i++) dist[i] = INF;
  dist[node] = 0;

  Queue q;
  initQueue(&q, N);
  enqueue(&q, node);

  while (!isEmpty(&q)) {
    int curr = dequeue(&q);
    if (dist[curr] > k) continue;
    for (int i = 0; i < adj[curr].size; i++){
      int neighbor = adj[curr].data[i];
      if (dist[neighbor] > dist[curr] + 1) {
	dist[neighbor] = dist[curr] + 1;
	enqueue(&q, neighbor);
      }
    }
  }
  int count = 0;
  for (int i = 0; i < N; i++) {
    if (dist[i] <= k) count++;
  }
  free(dist);
  freeQueue(&q);
  return count;
}

int* maxTargetNodes(int** edges1, int edges1Size, int* edges1ColSize, int** edges2, int edges2Size, int* edges2ColSize, int k, int* returnSize) {
  int N1 = edges1Size + 1;
  int N2 = edges2Size + 1;

  Vector *e1 = malloc(sizeof(Vector) * N1);
  Vector *e2 = malloc(sizeof(Vector) * N2);

  for (int i = 0; i < N1; i++) initVector(&e1[i]);
  for (int i = 0; i < N2; i++) initVector(&e2[i]);

  for (int i = 0; i < edges1Size; i++) {
    int u = edges1[i][0];
    int v = edges1[i][1];
    pushVector(&e1[u], v);
    pushVector(&e1[v], u);
  }

  for (int i = 0; i < edges2Size; i++) {
    int u = edges2[i][0];
    int v = edges2[i][1];
    pushVector(&e2[u], v);
    pushVector(&e2[v], u);
  }

  int best2 = 0;
  for (int node = 0; node < N2; node++) {
    int val = calculate(N2, e2, node, k - 1);
    if (val > best2) best2 = val;
  }

  int *answer = malloc(sizeof(int) * N1);
  for (int node = 0; node < N1; node++) {
    answer[node] = calculate(N1, e1, node, k) + best2;
  }

  for (int i = 0; i < N1; i++) freeVector(&e1[i]);
  for (int i = 0; i < N2; i++) freeVector(&e2[i]);
  free(e1);
  free(e2);
  
  *returnSize = N1;
  return answer;
}

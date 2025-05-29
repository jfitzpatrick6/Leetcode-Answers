/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

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

int isEmpty(Queue *q) {
  return q->size == 0;
}

void freeQueue(Queue *q) {
  free(q->data);
}

void calculateColors(int** edges, int edgesSize, Vector* adjlist, int* colors) {
  int N = edgesSize + 1;
  for (int i = 0; i < edgesSize; i++) {
    int u = edges[i][0];
    int v = edges[i][1];
    pushVector(&adjlist[u], v);
    pushVector(&adjlist[v], u);
  }
  Queue q;
  initQueue(&q, N);
  colors[0] = 0;
  enqueue(&q, 0);

  while (!isEmpty(&q)) {
    int current = dequeue(&q);
    for (int i = 0; i < adjlist[current].size; i++) {
      int neighbor = adjlist[current].data[i];
      if (colors[neighbor] == -1) {
	colors[neighbor] = (colors[current] + 1) % 2;
	enqueue(&q, neighbor);
      }
    }
  }
  freeQueue(&q);
}

int* maxTargetNodes(int** edges1, int edges1Size, int* edges1ColSize, int** edges2, int edges2Size, int* edges2ColSize, int* returnSize) {
  int N1 = edges1Size + 1;
  int N2 = edges2Size + 1;

  Vector* e1 = malloc(sizeof(Vector) * N1);
  Vector* e2 = malloc(sizeof(Vector) * N2);
  for (int i = 0; i < N1; i++) initVector(&e1[i]);
  for (int i = 0; i < N2; i++) initVector(&e2[i]);
  
  int* g1 = malloc(sizeof(int) * N1);
  int* g2 = malloc(sizeof(int) * N2);
  for (int i = 0; i < N1; i++) g1[i] = -1;
  for (int i = 0; i < N2; i++) g2[i] = -1;
  
  calculateColors(edges1, edges1Size, e1, g1);
  calculateColors(edges2, edges2Size, e2, g2);
  int count1[2] = {0};
  int count2[2] = {0};
  for (int i = 0; i < N1; i++) count1[g1[i]]++;
  for (int i = 0; i < N2; i++) count2[g2[i]]++;

  int maxGroup2 = count2[0] > count2[1] ? count2[0] : count2[1];

  int* answer = malloc(sizeof(int) * N1);
  for (int i = 0; i < N1; i++) {
    answer[i] = count1[g1[i]] + maxGroup2;
  }
  
  for (int i = 0; i < N1; i++) freeVector(&e1[i]);
  for (int i = 0; i < N2; i++) freeVector(&e2[i]);
  free(e1); free(e2);
  free(g1); free(g2);

  *returnSize = N1;
  return answer;
}

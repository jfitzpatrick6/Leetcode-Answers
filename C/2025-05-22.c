#include <stdlib.h>

typedef struct pq {
#ifndef PQ_DATA_TYPE
#define PQ_DATA_TYPE int
#endif
  int cap;            // pq capacity
  int len;            // pq current length
  PQ_DATA_TYPE *data; // queue data, 1-indexed
} pq;

pq *pq_new() {
  pq *ins = (pq *)malloc(sizeof(pq));
  *ins = (pq){32, 0, (PQ_DATA_TYPE *)malloc(32 * sizeof(PQ_DATA_TYPE))};
  return ins;
}

void pq_swap(PQ_DATA_TYPE *a, PQ_DATA_TYPE *b) {
  PQ_DATA_TYPE tmp = *a;
  *a = *b;
  *b = tmp;
}

void pq_free(pq *ins) {
  free(ins->data);
  free(ins);
}

void pq_max_heapify(PQ_DATA_TYPE *list, int len, int iCurr) {
  int iMax = iCurr;
  int iLC = iCurr * 2;
  int iRC = iLC + 1;
  if (iLC <= len && list[iMax] < list[iLC])
    iMax = iLC;
  if (iRC <= len && list[iMax] < list[iRC])
    iMax = iRC;
  if (iMax != iCurr) {
    pq_swap(&list[iCurr], &list[iMax]);
    pq_max_heapify(list, len, iMax);
  }
}

void pq_max_push(pq *ins, PQ_DATA_TYPE val) {
  if (++ins->len == ins->cap) {
    ins->cap *= 2;
    ins->data = realloc(ins->data, ins->cap * sizeof(PQ_DATA_TYPE));
  }
  ins->data[ins->len] = val;
  int i = ins->len; 
  int iF = i / 2;
  while (iF > 0 && ins->data[iF] < ins->data[i]) {
    pq_swap(&ins->data[iF], &ins->data[i]);
    i = i / 2;
    iF = i / 2;
  }
}

PQ_DATA_TYPE pq_max_pop(pq *ins) {
  PQ_DATA_TYPE root = ins->data[1];
  ins->data[1] = ins->data[ins->len];
  ins->len--;
  pq_max_heapify(ins->data, ins->len, 1);
  return root;
}

int cmpAsc(const void *a, const void *b) {
  return (*(int **)a)[0] - (*(int **)b)[0];
}

int maxRemoval(int *nums, int numsSize, int **queries, int queriesSize,
               int *queriesColSize) {
  qsort(queries, queriesSize, sizeof(int *), cmpAsc);
  int *preDifs = calloc(numsSize + 1, sizeof(int));
  pq *maxPQ_rb = pq_new(); // max root heap for right boundries
  int rs = -1;

  for (int i = 0, j = 0, curr = 0; i < numsSize; i++) {
    while (j < queriesSize && queries[j][0] == i) {
      pq_max_push(maxPQ_rb, queries[j][1]);
      j++;
    }

    curr += preDifs[i];
    while (curr < nums[i] && maxPQ_rb->len && maxPQ_rb->data[1] >= i) {
      preDifs[pq_max_pop(maxPQ_rb) + 1]--;
      curr++;
    }

    if (curr < nums[i])
      goto RETURN;
  }

  rs = maxPQ_rb->len;
RETURN:
  free(preDifs);
  pq_free(maxPQ_rb);
  return rs;
}

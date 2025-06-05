int find (int *parent, int x) {
  if (parent[x] != x) parent[x] = find(parent, parent[x]);
  return parent[x];
}

void unite(int *parent, int x, int y) {
  int rootX = find(parent, x);
  int rootY = find(parent, y);
  if (rootX ==  rootY) return;

  if (rootX < rootY) parent[rootY] = rootX;
  else parent[rootX] = rootY;
}

char* smallestEquivalentString(char *s1, char* s2, char* baseStr) {
  int len = strlen(s1);
  int parent[26];
  for (int i = 0; i < 26; i++) {
    parent[i] = i;
  }
  
  for (int i = 0; i < len; i++) {
    int u = s1[i] - 'a';
    int v = s2[i] - 'a';
    unite(parent, u, v);
  }

  int baseLen = strlen(baseStr);
  char *result = malloc(sizeof(char) * baseLen + 1);
  for (int i = 0; i < baseLen; i++) {
    int root = find(parent, baseStr[i] - 'a');
    result[i] = root + 'a';	       
  }
}

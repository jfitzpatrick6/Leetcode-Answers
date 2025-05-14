#define MOD 1000000007

typedef long long Matrix[26][26];

void matrix_multiply(const Matrix a, const Matrix b, Matrix result){
  Matrix temp = {{0}};
  for (int i = 0; i < 26; i++){
    for (int k = 0; k < 26; k++){
      if (a[i][k] == 0) continue;
      for (int j = 0; j < 26; j++){
	temp[i][j] = (temp[i][j] + a[i][k] * b[k][j]) % MOD;
      }
    }
  }
  memcpy(result, temp, sizeof(temp));
}

void matrix_power(const Matrix base, int power, Matrix result){
  Matrix current;
  memcpy(current, base, sizeof(current));
  Matrix identity = {{0}};
  for (int i = 0; i < 26; i++){
    identity[i][i] = 1;
  }
  while (power > 0) {
    if (power & 1){
      Matrix tmp;
      matrix_multiply(identity, current, tmp);
      memcpy(identity, tmp, sizeof(tmp));
    }
    Matrix sq;
    matrix_multiply(current, current, sq);
    memcpy(current, sq, sizeof(sq));
    power >>= 1;
  }
  memcpy(result, identity, sizeof(identity));
}

int lengthAfterTransformations(char* s, int t, int* nums, int numsSize) {
  (void)numsSize;
  long long char_counts[26] = {0};
  for (char* p = s; *p; p++){
    char_counts[*p - 'a']++;
  }
  Matrix transform = {{0}};
  for (int i = 0; i < 26; i++){
    for (int step = 1; step <= nums[i]; step++){
      transform[i][(i + step) % 26]++;
    }
  }
  Matrix powered;
  matrix_power(transform, t, powered);
  long long answer = 0;
  for (int src = 0; src < 26; src++){
    if (!char_counts[src]) continue;
    for (int dst = 0; dst < 26; dst++){
      answer = (answer + char_counts[src] * powered[src][dst]) % MOD;
    }
  }
  return (int)answer;
}

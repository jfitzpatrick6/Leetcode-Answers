#define MOD 1000000007

int lengthAfterTransformations(char *s, int t){
  int freq[26] = {0};
  for (int i = 0; s[i] != '\0'; i++){
    freq[s[i] - 'a']++;
  }
  for (int i = 0; i < t; i++){
    int zPointer = 25 - (i % 26);
    int val = freq[zPointer];
    if (val > 0){
      int behind = (zPointer + 1) % 26;
      freq[behind] = (val + freq[behind]) % MOD;
    }
  }
  int count = 0;
  for (int i = 0; i < 26; i++){
    count = (count + freq[i]) % MOD;
  }
  return count;
}

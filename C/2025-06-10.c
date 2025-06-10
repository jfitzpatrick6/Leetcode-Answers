int maxDifference(char* s) {
  int *freq = malloc(sizeof(int) * 27);
  for (int i = 0; i < 27; i++) freq[i] = 0;
  int i = 0;
  while (s[i] != '\0') {
    freq[s[i++] - 'a']++;
  }
  int maxDifference = -1;
  int evenDex = -1, oddDex = -1;
  for (int i = 0; i < 27; i++) {
    printf("%d\n", i);
    if (freq[i] == 0) continue;
    // want a large oddDex, low evendex
    if ((oddDex == - 1 || freq[i] > freq[oddDex]) && freq[i] % 2 != 0) {
      oddDex = i;
    }
    if ((evenDex == - 1 || freq[i] < freq[evenDex]) && freq[i] % 2 == 0) {
      evenDex = i;
    }
  }
  maxDifference = freq[oddDex] - freq[evenDex];
  free(freq);
  return maxDifference;
}

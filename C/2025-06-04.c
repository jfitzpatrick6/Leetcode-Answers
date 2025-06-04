void substring(char* dest, const char *src, int start, int length) {
  strncpy(dest, src + start, length);
  dest[length] = '\0';
}

char* answerString(char* word, int numFriends) {
  int N = strlen(word);
  int expectedLength = N - (numFriends - 1);
  if (numFriends == 1) return word;

  char* best = malloc(sizeof(char) * expectedLength + 1);
  best[0] = '\0';
  for (int i = 0; i < N; i++) {
    char sub[expectedLength + 1];
    substring(sub, word, i, expectedLength);
    if (strcmp(sub, best) > 0) {
      strncpy(best, sub, strlen(sub));
      best[strlen(sub)] = '\0';
    }
  }
  return best;
}

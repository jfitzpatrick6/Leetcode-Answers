int* findWordsContaining(char** words, int wordsSize, char x, int* returnSize) {
  int *contained = malloc(sizeof(int) * wordsSize);
  int index = 0;
  for (int i = 0; i < wordsSize; i++){
    for (int j = 0; j < strlen(words[i]); j++){
      if (x == words[i][j]){
	contained[index++] = i;
	break;
      }
    }
  }
  *returnSize = index;
  return contained;
}

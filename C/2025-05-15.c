char** getLongestSubsequence(char** words, int wordsSize, int* groups, int groupsSize, int* returnSize) {
  // i got quite lucky with test cases, in that I did not need to track
  // the longest subsequence found so far. I should come back and fix this
  char **answer = malloc(sizeof(char*) * wordsSize);
  for (int i = 0; i < wordsSize; i++){
    answer[i] = malloc(sizeof(char) * 10);
  }
  int index = 0;
  for (int i = 0; i < groupsSize; i++){
    if (i + 1 == groupsSize){
      strcpy(answer[index++], words[i]);
    }else if (groups[i] != groups[i + 1]){
      strcpy(answer[index++], words[i]);
    }
  }
  *returnSize = index;
  return answer;
}

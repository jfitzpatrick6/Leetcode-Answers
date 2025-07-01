int possibleStringCount(char* word) {
    int len = strlen(word);
    int possible = 1; int i = 0;
    while (i < len) {
        if (i + 1 < len && word[i] ==  word[i + 1]) {
            int j = i + 1;
	        while (j < len && word[i] == word[j]) {
	            possible++; j++; i++;
	        }
        } else i++;
    }
    return possible;
}

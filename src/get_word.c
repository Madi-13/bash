char *get_word (char *end) {
	char *wrd = NULL;
	int i = 0;
	*end = getchar();
	while (*end != ' ' && *end != '\t' && *end != '\n') {
		wrd = realloc(wrd, (i + 1) * sizeof(char));
		wrd[i] = *end;
		i++;
		*end = getchar();
	}
	wrd[i] = '\0';
	return wrd;
}

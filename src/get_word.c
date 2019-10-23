char *get_word(char *end)
{
	if (*end == '\n') {
		return NULL;
	}
	int i = 0;
	char ch, *word = NULL, *check = NULL;
	do {
		ch = getchar();
		while (!i && (ch == ' ' || ch == '\t')) {
			ch = getchar();
			if (ch == '\n') {
				return NULL;
			}
		}
		check = (char *)realloc(word, (i + 1) * sizeof(char));
		if (check == NULL) {
			err(1, NULL);
		}
		word = check;
		word[i] = ch;
		i++;
	} while (ch != ' ' && ch != '\t' && ch != '\n');
	word[i - 1] = '\0';
	*end = ch;
	return word;
}

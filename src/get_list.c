char **get_list () {
	char **list = NULL, last_sym = '\0';
	int i = 0;
	do {
		list = realloc(list, (i + 1) * sizeof(char *));
		list[i] = get_word(&last_sym);
		i++;
	}
	while (last_sym != '\n');
	list = realloc(list, (i + 1) * sizeof(char *));
	list[i] = NULL;
	return list;
}

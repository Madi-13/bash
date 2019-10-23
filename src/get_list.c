char **get_list(void)
{
	char end = 0, **list = NULL, **ch = NULL;
	int i = 0;
	do {
		ch = (char **)realloc(list, (i + 1) * sizeof(char *));
		if (ch == NULL) {
			free_list(list);
			err(1, NULL);
		}
		list = ch;
		list[i] = get_word(&end);
		i++;
	} while (list[i - 1] != NULL);
	return list;
}

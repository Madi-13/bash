int sym_search (char **list, char *sym_ptr) {
	if (list) {
		for (int i = 0; list[i]; i++) {
			if (!strcmp(list[i], ">")) {
				*sym_ptr = '>';
				return i;
			}
			if (!strcmp(list[i], "<")) {
				*sym_ptr = '<';
				return i;
			}
		}
	}
	*sym_ptr = '\0';
	return 0;


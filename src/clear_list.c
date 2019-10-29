void clear_list(char **list) {
    if (list) {
        for (int i = 0; list[i]; i++)
            free(list[i]);
        free(list);
    }
}


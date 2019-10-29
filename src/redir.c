int redir(char **list, char sym, int sym_pos) {
	char *tmp;
	int fd;
	if (sym == '>') {
            tmp = list[sym_pos];
            list[sym_pos] = NULL;
            fd = open(list[sym_pos + 1], O_WRONLY | O_CREAT | O_TRUNC,
                        S_IRUSR | S_IWUSR);
            if (fd < 0) {
                warnx("%s: something went wrong\n", list[sym_pos + 1]);
            } else {
                if (fork() > 0) {
                    wait();
                } else {
                    dup2(fd, 1);
                    if (execvp(list[0], list) < 0) {
                        perror("exec failed");
                        return 1;
                    }
                }
                close(fd);
            }
            list[sym_pos] = tmp;
        } else if (sym == '<') {
            tmp = list[sym_pos];
            list[sym_pos] = NULL;
            fd = open(list[sym_pos + 1], O_RDONLY);
            if (fd < 0) {
                warnx("%s: something went wrong\n", list[sym_pos + 1]);
            } else {
                if (fork() > 0) {
                    wait();
                } else {
                    dup2(fd, 0);
                    if (execvp(list[0], list) < 0) {
                        perror("exec failed");
                        return 1;
                    }
                }
                close(fd);
            }
            list[sym_pos] = tmp;
        }
}

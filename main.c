#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
int main (void) {
	char **list, *tmp, sym;
	int fd, sym_pos;
	int i = 0;
	list = get_list();
	sym_pos = sym_search(list, &sym);
	while (list && strcmp(list[0], "exit") && strcmp(list[0], "quit")) {
		if (!sym) {
			if (fork() > 0) {
				wait();
			} else {
				if (execvp(list[0], list) < 0) {
					perror("exec trouble");
					return 1;
				}
			}
		}
		else {
			redir(list, sym, sym_pos);
		}
		clear_list(list);
		list = get_list();
		sym_pos = sym_search(list, &sym);
	}
	clear_list(list);
	return 0;
}

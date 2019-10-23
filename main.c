#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <err.h>
#include <fcntl.h>

int main(void) {
	char cmd[10];
	ssize_t fd = open ( "file.txt ", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR );
	while (1) {
		fgets(cmd, 10, stdin);
		cmd[strlen(cmd) - 1] = '\0';
		if (!strcmp(cmd, "exit") || !strcmp(cmd, "quit")) {
			return 0;
		}
		pid_t pid = fork();
		if (pid == 0) {
			dup2(fd, 1);
			if (execlp(cmd, cmd, NULL) < 0) {
				err(STDOUT_FILENO, NULL);
				return 1;
			}
			return 0;
		}
		wait(NULL);
	}
	close(fd);
	return 0;
}

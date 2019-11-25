#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

#define ANSI_COLOR_YELLOW  "\x1b[33;1m"
#define ANSI_COLOR_BLUE    "\x1b[34;1m"
#define ANSI_COLOR_RED     "\x1b[31;1m"
#define ANSI_COLOR_GREEN   "\x1b[32;1m"
#define ANSI_COLOR_MAGENTA "\x1b[35;1m"
#define ANSI_COLOR_CYAN    "\x1b[36;1m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void print() {
  const char* pwd = getenv("PWD");
  const char* user = getenv("USER");
  char host[256];
  gethostname(host, 256);
  printf(ANSI_COLOR_GREEN "%s@%s" ANSI_COLOR_RESET ":" ANSI_COLOR_BLUE "%s" ANSI_COLOR_RESET "$ ", user, host, pwd);
  fflush(stdout);
}

char *get_word(char *end) {
    char *word = NULL;
    int i = 0, j = 0;
    if (*end == '&') {
        ampers = 1;
        read(0, end, 1);
        return word;
    }
    if (*end == '|') {
      return word;
    }   
    if (*end == '>' || *end == '<') {
        word = (char *)realloc(word, 2);
        if (word == NULL) {
            perror("realloc");
            return NULL;
        }
        word[0] = *end;
        word[1] = '\0';
        if (read(0, end, 1) < 0) {
            perror("read");
            free(word);
            return NULL;
        }
        return word;
    }
    if (*end == '"') {
            j = 2;
            if (read(0, end, 1) < 0) {
                perror("read");
                free(word);
                return NULL;
            }
            if (*end == '"') {
                word = (char *)realloc(word, sizeof(char));
                if (word == NULL) {
                    perror("realloc");
                    return NULL;
                }
                *end = ' ';
                word[0] = '\0';
                return word;
            }
    }
    while (1) {
        if ((*end == ' ' || *end == '\n' || *end == '\t') && (j != 2)) {
            break;
        }
        if (*end == '"' && j == 2) {
            *end = ' ';
            break;
        }
        if (*end == '<' || *end == '>' || *end == '|') {
            break;
        }
        word = (char *)realloc(word, (i + 2) * sizeof(char));
        if (word == NULL) {
            perror("realloc");
            return NULL;
        }
        word[i] = *end;
        if (read(0, end, 1) < 0) {
            perror("read");
            free(word);
            return NULL;
        }
        i++;
    }
    word[i] = '\0';
    return word;        
}


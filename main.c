#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include  <sys/types.h>
#include  <sys/wait.h>

#include  <unistd.h>
#include <malloc.h>

char **str_split(char *a_str, const char a_delim) {
    char **result = 0;
    size_t count = 0;
    char *tmp = a_str;
    char *last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp) {
        if (a_delim == *tmp) {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
    knows where the list of returned strings ends. */
    count++;

    result =(char **) malloc(sizeof(char *) * count);

    if (result) {
        size_t idx = 0;
        char *token = strtok(a_str, delim);

        while (token) {

            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        *(result + idx) = NULL;

    }

    return result;
}

char *cli_read_line(void)
{
    char *line = NULL;
    size_t bufsize = 0;
    getline(&line, &bufsize, stdin);
    return line;
}
int main() {
    printf("cmd> ");
    char* input = cli_read_line();

    char **argv = str_split(input, ' ');
    free(input);

    pid_t  pid;

    pid = fork();

    if (pid == 0)
        execv(argv[0], argv);
    else {

        int x, i = 0;
        waitpid(pid, &x, 0);
        while(argv[i]){
            free(argv[i++]);
        }
        free(argv);

    }

    return 0;
}
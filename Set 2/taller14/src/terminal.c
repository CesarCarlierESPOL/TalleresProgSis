#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define INPUT_SIZE 255
#define EXITCMD "exit"

int main(void) {
  for (;;)
  {
    char input[INPUT_SIZE + 1] = { 0x0 };
    char *ptr = input;
    char *args[12] = { NULL };
    int wstatus;

    // prompt
    printf("$ ");
    fgets(input, INPUT_SIZE, stdin);

    // Ignora input vacío
    if (*ptr == '\n') continue;

    // Procesa la entrada
    for (int i = 0; i < sizeof(args) && *ptr; ptr++) {
      if (*ptr == ' ') {
        continue;
      }
      if (*ptr == '\n'){
        break;
      }
      for (args[i++] = ptr; *ptr && *ptr != ' ' && *ptr != '\n'; ptr++);
      *ptr = '\0';
    }

    if (strcmp(EXITCMD, args[0]) == 0){
      return 0;
    }

    // Hace fork y ejecuta programa
    signal(SIGINT, SIG_DFL);
    if (fork() == 0){
      exit(execvp(args[0], args));
    }
    signal(SIGINT, SIG_IGN);

    // Espera que programa termine e imprime estado
    wait(&wstatus);
    if (WIFEXITED(wstatus)){
      printf("<%d>\n", WEXITSTATUS(wstatus));
    }
  }
}

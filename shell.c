#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#define MaxInput 1000
#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"
#define RESET "\033[0m"
/*int lsh_launch(char **args)
{
  pid_t pid, wpid;
  int status;

  pid = fork();
  if (pid == 0) {
    // Child process
    if (execvp(args[0], args) == -1) {
      perror("lsh");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    // Error forking
    perror("lsh");
  } else {
    // Parent process
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

*/
char* inputs(){
    int Max=MaxInput;
	char* input=malloc(sizeof(char)*Max);
	//int index=0;

//char *line = NULL;
//  ssize_t bufsize = 0; // have getline allocate a buffer for us
  getline(&input, &Max, stdin);

//	char *token = strtok (input, " |");
//while(token != NULL){
//	printf("Hasil strtok() : %s\n",token);
//	token = strtok (NULL, "|");
//}
//printf("%s\n",input);
return input;
}
char **splitToToken(char* input){
    int Max=MaxInput;
    int index=0;
    char *token;
    char **tokens=malloc(sizeof(char)*Max);
    token = strtok (input,"\n \t\r\a");
    while(token!=NULL){
        tokens[index]=token;
        index++;
   //     token++;
  //      puts(tokens[index]);
  token=strtok(NULL,"\n \t\r\a");
    }
    return tokens;

}
int main(){
  char *input;
  char **args;
  int status;
    while(1){
        printf(KBLU "%s#" KYEL "%s " KGRN "> $ " RESET,getenv("USER"),getenv("GDMSESSION"));
        input=inputs();
        args=splitToToken(input);
   //    printf("Input : ");puts(input);
//puts(args[2]);
      free(input);
      free(args);

    }
 //     puts(args[1]);
//printf("%s\n",inputs());
//execve("/bin/ls", argv, envp);
//	execve("/bin/ls", argv,NULL);
    return 0;
}


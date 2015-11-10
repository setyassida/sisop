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

void signal_handler(int signo) // Fungsi penangkap sinyal
{
  if (signo == SIGTSTP){
        signal(SIGTSTP, signal_handler);
    }
 else if (signo == SIGINT){
        signal(SIGINT, signal_handler);
    }
}

char* inputs(){ // Fungsi untuk menerima inputan user
    int Max=MaxInput;
	char* input=malloc(sizeof(char)*Max);

    getline(&input, &Max, stdin);
    return input;
}
char **splitToToken(char* input){ // Fungsi untuk memecah inputan user
    int Max=MaxInput;
    int index=0;
    char *token; // Inputan utuh
    char **tokens=malloc(sizeof(char)*Max); // tokens untuk menampung pecahan2 token
    token = strtok (input,"\n \t\r\a");
    while(token!=NULL){
        tokens[index]=token;
        index++;
        token=strtok(NULL,"\n \t\r\a");
    }
    return tokens;
}
void execute(char**args){ //Fungsi membuat proses dr inputan user
    pid_t process,wpid;
    int status;
    process=fork();
    if(process==0){
        execvp(args[0], args); // Eksekusi Inputan user
    }else{
        do {
            wpid = waitpid(process, &status, WUNTRACED); // MEnunggu proses anak
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}
void chdirss(char **args) //Fungsi untuk berpindah direktori
{
    chdir(args[1]); //arg[1] menunjukan direktori setelah user mengetik cd
}
int main(){
    char *input;
    char **args;
    char *pwd; // *char menunjuk pwd sekarang
    char buff[100]; //Buff pwd
    while(1){
        pwd=getcwd(buff, sizeof(buff)); // Mengecek pwd terkini
        printf(KBLU "%s#" KYEL "%s%s" KGRN " > $ " RESET,getenv("USER"),getenv("GDMSESSION"         ),pwd); //Template inputan user

        input=inputs();
        args=splitToToken(input);

        if(strcmp(args[0],"Exit")==0 || strcmp(args[0],"exit")==0){
            break;
        }else if (strcmp(args[0],"cd")==0){
            chdirss(args);
        }else{
            execute(args);
        }
        signal(SIGINT, signal_handler); //Untuk signal ctrl-c
        signal(SIGTSTP, signal_handler); //Untuk signal ctrl-z
    }
    free(input);
    free(args);
    return 0;
}


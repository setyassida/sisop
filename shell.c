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
   // char* end=(char*)EOF;

    //char *exits;
    //exits=end;
    getline(&input, &Max, stdin);
    //puts(input);
    //if(input==end){
      // exit(1);
   //}
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
int isBackgroundProcess(char**args){
    int i=0;
    int Max=MaxInput;
    for(i=0;i<MaxInput;i++){
        if(args[i]==NULL){
            return 0;
        }else if(strcmp(args[i],"&")==0){
            return i;
        }
    }
}
void process(char**args){ //Fungsi membuat proses dr inputan user
    pid_t process,wpid;
    int status;
    process=fork();
    if(process==0){
        if (strcmp(args[0],"cd")==0){
            chdir(args[1]); //arg[1] menunjukan direktori setelah user mengetik cd
        }else{
            execvp(args[0], args); // Eksekusi Inputan user
        }

    }else{
        do {
            wpid = waitpid(process, &status, WUNTRACED); // MEnunggu proses anak
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}
void backgroundprocess(char**args){ //Fungsi membuat proses dr inputan user
    pid_t process,sid;
    int status;
    process=fork();
    if(process>0){
        return ;
    }else{
        umask(0);
sid = setsid();
       if (strcmp(args[0],"cd")==0){
            chdir(args[1]); //arg[1] menunjukan direktori setelah user mengetik cd
        }else{
            execvp(args[0], args); // Eksekusi Inputan user
        }

    }
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
        }

        if(!isBackgroundProcess(args)){
            process(args);
        }else{
            int index_apersand= isBackgroundProcess(args);
            args[index_apersand]=NULL;
            backgroundprocess(args);
        }


        signal(SIGINT, signal_handler); //Untuk signal ctrl-c
        signal(SIGTSTP, signal_handler); //Untuk signal ctrl-z
    }
    free(input);
    free(args);
    return 0;
}


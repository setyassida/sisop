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
	printf("\n");
 	main();      
        signal(SIGTSTP, SIG_IGN); //Untuk signal ctrl-z
    }
 else if (signo == SIGINT){
	printf("\n");
	main();
        signal(SIGINT, SIG_IGN); //Untuk signal ctrl-c
    }
}/*
char* inputs(){ // Fungsi untuk menerima inputan user
   int bufsize = MaxInput;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;

  if (!buffer) {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  while (1) {
    // Read a character
    c = getchar();

    // If we hit EOF, replace it with a null character and return.
    if (c == EOF || c == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;

    // If we have exceeded the buffer, reallocate.
    if (position >= bufsize) {
      bufsize += MaxInput;
      buffer = realloc(buffer, bufsize);
      if (!buffer) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}*/
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
//void ctrlD(int* buff){
//	if(buff<0){
//		printf("awoawkaowk\n");
//	}
//}
int main(){
   char *input;
    char **args;
    char *pwd; // *char menunjuk pwd sekarang
    char buff[100]; //Buff pwd
//	int* eo;
    while(1){
        pwd=getcwd(buff, sizeof(buff)); // Mengecek pwd terkini
        printf(KBLU "%s#" KYEL "%s%s" KGRN " > $ " RESET,getenv("USER"),getenv("GDMSESSION"         ),pwd); //Template inputan user

//        input=inputs();
//printf("%d",(int)input);	
//sscanf(input, "%d",eo);
	//ctrlD(eo);        
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
//char *e=EOF;
//printf("%d",e);
//int a;
//while(1){
//e=inputs();
//sscanf(e, "%d", a);
//printf("%d\n",a);
//if(e==EOF){break;};
//	sleep(1);
//}
    return 0;
}


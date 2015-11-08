#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"
#define RESET "\033[0m"
int main(){

char input[78];
printf(KBLU "%s#" KYEL "%s " KGRN "> $ " RESET,getenv("USER"),getenv("GDMSESSION"));

scanf("%[^\n]",input);
char *token = strtok (input, " ,|");
while(token != NULL){
	printf("Hasil strtok() : %s\n",token);
	token = strtok (NULL, "|");
}
/*
    char input[];
    printf("Masukkan string : ");
    scanf("%[^\n]",input); //agar berhenti scan saat ketemu enter      
    printf("%s\n",input);
	char *substr = strstr(input , "o");
	printf("Hasil strtstr() :%s \n ",substr);
	char *token = strtok (input,  " ");
while(token != NULL){
	printf("Hasil strtok() : %s\n",token);
	token = strtok (NULL, " ");
}	
		
	//char *token = strtok (input,  "o");
//	printf("Hasil strtok() : %s\n",token);
//	token = strtok (NULL, "o");
//	printf("Hasil strtok() : %s\n",token);
*/
    return 0;
}

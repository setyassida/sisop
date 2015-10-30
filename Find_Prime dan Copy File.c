#include<stdio.h>
#include <pthread.h>
#include <unistd.h>
void *find_prime(void *args) {
	int input,i,j,k;
	printf("Input some number : ");scanf("%d",&input);
	printf("The Prime's number less equal than %d : ",input);
	for(i=0; i<=input;i++){
		if(i==2){
			printf("%d ",i);
		}
		for(j=2;j<i;j++){
			if(i%j==0){
	   			 break;
			}else if(j==(i-1)){
				printf("%d ",i);
			}else{
				continue;
			}
		}
    	}
	printf("\n");
}
void *copy1(void *args) {
	 //char *arg[] = {"/bin/ls", "-r", "-t", "-l", (char *) 0 };
	//execv("/bin/ls", arg);
	execl( "/bin/ls", "-r", "-t", "-l", (char *) 0);
}
//void *copy2(void *args) {

//}
void main () {
	int input;
//	while(1){
//		printf("1. ")
//	}
	pthread_t t1;
//	pthread_create(&t1, NULL, find_prime, NULL);
	pthread_create(&t1, NULL, find_prime, NULL);
//	pthread_create(&t1, NULL, copy1, NULL);
	pthread_join(t1, NULL); // For calling find prime thread
}

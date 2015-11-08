#include<stdio.h>
#include <stdlib.h>
#include <pthread.h>
void *find_prime(void *args) {
  int maks= (int)args;
  int count;
	if(maks==2){
	 	return (void *)maks;
	}
	for(count=2;count<maks;count++){
		if(maks%count==0){
		   	break;
		}else if(count==(maks-1)){
			return (void*)maks;
		}else{
			continue;
		}
	}
  	pthread_exit(NULL); // Kalau tidak ada ini, jika maks-nya 2 maka return nya 2 kali
}
void *copy1(void *args) {
	 //char *arg[] = {"/bin/ls", "-r", "-t", "-l", (char *) 0 };
	//execv("/bin/ls", arg);
	execl( "/bin/ls", "-r", "-t", "-l", (char *) 0);
}
//void *copy2(void *args) {

//}
void main () {
	int input,i=1,banyak_bilprim =0;
	printf("Input some number : ");scanf("%d",&input);	
	pthread_t t1[input];
	void* bilprim;
	while(i <= input)
    	{
        	pthread_create(&(t1[i]), NULL, find_prime, (void*)i);
		pthread_join(t1[i], &bilprim);
		if(bilprim!=0){
			printf("%d ",(int)bilprim);       
			banyak_bilprim++;
		}		

		i++;
	}
	printf("\nTerdapat %d bilangan prima \n",banyak_bilprim);
}

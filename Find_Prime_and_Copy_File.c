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

void main () {
	int input,i=1,j=0,banyak_bilprim =0;
	printf("Input some number : ");scanf("%d",&input);
	pthread_t t1[input];
	void* bilprim;
	while(i <= input){
        pthread_create(&(t1[i]), NULL, find_prime, (void*)i);
		i++;
	}
	while(j <= input){
        pthread_join(t1[j], &bilprim);
		if(bilprim!=0){
			printf("%d ",(int)bilprim);
			banyak_bilprim++;
        }
        j++;
	}

	printf("\nTerdapat %d bilangan prima \n",banyak_bilprim);

}

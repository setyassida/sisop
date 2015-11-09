#include <stdio.h>
#include <pthread.h>

void *func1()
{
	FILE *rf, *wf;
	char c;
	rf=fopen("file1.txt", "r");
	wf=fopen("file2.txt", "w");
	while((c=fgetc(rf))!=EOF)
	{
		fprintf(wf, "%c", c);
	}
	fclose(rf);
	fclose(wf);
	//return 0;
}

void *func2()
{
	FILE *rf, *wf;
	char c;
	rf=fopen("file2.txt", "r");
	wf=fopen("file3.txt", "w");
	while((c=fgetc(rf))!=EOF)
	{
		fprintf(wf, "%c", c);
	}
	fclose(rf);
	fclose(wf);
	//return 0;
}

void main(){
	pthread_t t1, t2;
	pthread_create(&t1, NULL, func1, NULL);
	pthread_create(&t2, NULL, func2, NULL);

	pthread_join(&t1, NULL);
	/*int i=0;
	for(i=1;i<30;i++) printf("Main : %d\n", i);
	*/
	pthread_join(&t2, NULL);
	//return 0;
}

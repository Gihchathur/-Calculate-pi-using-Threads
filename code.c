#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int NumOfTerms=0;
#define NumOfThreads 1
#define PartOfThread NumOfTerms/NumOfThreads

#define handle_error_en(en, msg) \
        do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

pthread_t *threads;	
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
long TotalCount = 0;

void *CalculationOfPi(void *thread_ID) {

	time_t t;
 	srand((unsigned) time(&t));
	
	long i;							
	int a = (int) thread_ID;		
	long incircle_thread = 0; 		
	unsigned int rand_state = rand(); 
	

	for (i = 0; i < PartOfThread; i++) {
		
		double x = rand_r(&rand_state) / ((double)RAND_MAX + 1) * 2.0 - 1.0;
		double y = rand_r(&rand_state) / ((double)RAND_MAX + 1) * 2.0 - 1.0;
	
		if (x * x + y * y < 1) {
			incircle_thread++;
			}

		}

	
	float Pi = (4. * (double)incircle_thread) / 
				((double)PartOfThread * 1);

		pthread_mutex_lock(&mutex);
		TotalCount += incircle_thread;
		pthread_mutex_unlock(&mutex);
return NULL;

}



void joinThreads(){

	int i,s; 
	for (i = 0; i < NumOfThreads; i++) {
		s = pthread_join(threads[i], NULL);
		 if (s != 0){
			handle_error_en(s, "pthread_join");
		 }
	}

	pthread_mutex_destroy(&mutex);
	free(threads);
}




int main()
{

FILE *file = fopen("outputValues.txt", "w");
FILE *file2 = fopen("outputValues2.txt", "w");
for(int num=0; num<2000; num++)
{

TotalCount = 0;
 time_t t;
 srand((unsigned) time(&t));
unsigned int rand_state = rand();

int i, s; 
threads = malloc(NumOfThreads * sizeof(pthread_t));
pthread_attr_t varThread; 
pthread_attr_init(&varThread);

for (i = 0; i < NumOfThreads; i++) {
		
		
		s = pthread_create(&threads[i], &varThread, CalculationOfPi,  (void *) i);
		 if (s != 0){
			handle_error_en(s, "pthread_create");
		 
		}
}

joinThreads();
	
	double Pi = (4. * (double)TotalCount) / ((double)PartOfThread * NumOfThreads);
	
	printf("%d - Estimation Pi: %f\n\n",num, Pi);
	

	fprintf(file, "%d\n", NumOfTerms);
	fprintf(file2, "%f\n", Pi);

NumOfTerms+=10;
}
return 0;


}

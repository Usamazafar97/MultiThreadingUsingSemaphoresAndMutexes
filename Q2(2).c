#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

char stringArray[12][100];//we assume there are only 12 lines in the input.txt as discussed in the 3rd Question

pthread_mutex_t lock;

void* Capitalize(void* arg) 
{ 
	char* s = (char*) arg;
	 int c = 0;
   
   while (s[c] != '\0') {
      if (s[c] >= 'a' && s[c] <= 'z') {
         s[c] = s[c] - 32;
      }
      c++;
   }   

FILE *fptr;
  char ch;
  fptr = fopen("output1.txt", "a");
  
 /* 
  for(int i=0 ; s[i] != '\0';i++){
    // write character ch in file
	ch = s[i];
    putc(ch, fptr);
	i++;
  }
  */
   pthread_mutex_lock(&lock);
   fprintf(fptr,"%s",s);  
    pthread_mutex_unlock(&lock);
  // close the file
  fclose(fptr);  
  
    
  printf("%s",s);   
}
  

int main() 
{ 
     
	 int count = 0;
	 
	 if(pthread_mutex_init(&lock,NULL) != 0)
	 {
		 printf("initialization of mutex is failed\n");
		 return 1;
	 }
	 
	FILE *ptr2;
		ptr2 = fopen("input.txt","r");
		if(ptr2==NULL)
			{
				printf("File not found!!!!");
				//return(1);
			}
		char stringPerWord[100];//the length of the stringPerWord isalmost 100 characters
		while(fgets(stringPerWord,99,ptr2) != NULL)
			{
				
				for(int i=0 ; stringPerWord[i] != '\0';i++)
			{				
				//printf("%c",stringPerWord[i]);
				stringArray[count][i]=stringPerWord[i];
			}
			//printf("%d",count);
		
				count++;
			}
			
		fclose(ptr2);
		//printf("ok1");
		
		 // declaring 12 threads 
    pthread_t threads[12]; 
	// Creating 12 threads, each thread will do its own functio
	//printf("ok2");
    for (int i = 0; i < 12; i++)
	{ 	
		//printf("ok%d",i);
         pthread_create(&threads[i], NULL, Capitalize, (void*)(stringArray[i])); 
    } 
		// joining and waiting for all threads to complete 
    for (int i = 0; i < 12; i++)  		
			pthread_join(threads[i], NULL); 		
			
    return 0; 
}

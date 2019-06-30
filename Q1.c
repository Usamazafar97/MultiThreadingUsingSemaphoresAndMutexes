#include <stdio.h>
#include <pthread.h>  
  
int matrixA[3][3]; 
int matrixB[3][3]; 
int matrixC[3][3]; 
int count = 0; 
  
void* multi(void* arg) 
{ 

    int ind = count++;   
    // Each thread computes 1/3rd of matrix multiplication 
    for (int i = ind * 3 * 3; i < (ind + 1) * 3 * 3; i++)  
        for (int j = 0; j < 3; j++)  
            for (int k = 0; k < 3; k++)  
                matrixC[i][j] += matrixA[i][k] * matrixB[k][j]; 
} 
int main() 
{ 
    // Input the values in matA and matB 
    for (int i = 0; i < 3; i++)
	{ 
         for (int j = 0; j < 3; j++) 
		 { 
			printf("Please enter the value in first matrix");
            scanf("%d",&matrixA[i][j] ); 
			printf("Please enter the value in second matrix");
            scanf("%d",&matrixB[i][j] );
         } 
    }   
    // Displaying matA 
	printf("\n Matrix A \n");
    for (int i = 0; i < 3; i++) 
	{ 
        for (int j = 0; j < 3; j++)  
			printf("%d ",matrixA[i][j] );
        printf("\n"); 
    }  
     // Displaying matB
	printf("\n Matrix B \n");
    for (int i = 0; i < 3; i++) { 
        for (int j = 0; j < 3; j++)  
			printf("%d  ",matrixB[i][j] );
        printf("\n"); 
    }   
    // declaring 9 threads 
    pthread_t threads[9]; 
  
    // Creating 9 threads, each thread will do its own multiplication
    for (int i = 0; i < 9; i++)
	{ 
        int* p; 
        pthread_create(&threads[i], NULL, multi, (void*)(p)); 
    }   
    // joining and waiting for all threads to complete 
    for (int i = 0; i < 9; i++)  
        pthread_join(threads[i], NULL);       
    // Displaying the result matrix 
	printf("\n Multiplication of A and B is = \n");
    for (int i = 0; i < 3; i++) 
	{ 
        for (int j = 0; j < 3; j++)  
			printf("%d ",matrixC[i][j] );
        printf("\n"); 
    }
    return 0; 
}
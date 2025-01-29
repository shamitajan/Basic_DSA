#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#define size 5

typedef struct {
    int row;
    int column;
    int nonzero;	
} element;

void inputMatrix(int matrix[size][size]) {
    printf("Enter your matrix elements:\n");
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            printf("Element at row %d, column %d: ", i+1, j+1);
            scanf("%d", &matrix[i][j]);
        }
    }
}
bool isSparseMatrix(int matrix[size][size], element sm[], int *count) {
    *count = 0;
    int total = size * size;
    bool sparse = false;
    
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if(matrix[i][j] > 0) {
                sm[*count].row = i + 1;
                sm[*count].column = j + 1;
                sm[*count].nonzero = matrix[i][j];
                (*count)++;
            }
        }
    }
    if(*count <= total / 2) {
        sparse = true;
    }
    return sparse;
}
void outputMatrix(int matrix[size][size]) {
    printf("\nYour matrix is:\n");
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void outputSparseMatrix(element sm[], int count) {
    printf("\nRow\tColumn\tElement\n");
    for(int i = 0; i < count; i++) {
        printf("%d\t%d\t%d\n", sm[i].row, sm[i].column, sm[i].nonzero);
    }
}

void transpose(element sm[], int *count) {
    for(int i = 0; i < *count; i++) {
        int temp = sm[i].row;
        sm[i].row = sm[i].column;
        sm[i].column = temp;
    }
}
int main() {
    element sm[size*size];
    int matrix[size][size];
    int count = 0;
    
    clock_t start_time, end_time;
    double cpu_time_used;
    
    start_time = clock();
    inputMatrix(matrix);
    outputMatrix(matrix);    
    if(isSparseMatrix(matrix, sm, &count)) {
        printf("\nThis is a sparse matrix.\n");
        outputSparseMatrix(sm, count);
    } else {
        printf("\nThis is not a sparse matrix.\n");
    }
    end_time = clock();
    cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    
    printf("\nExecution time: %f seconds\n", cpu_time_used);
    printf("\nThe time complexity of this program is O(n^2).\n");
    printf("\nNow transposing the matrix...\n");
    transpose(sm, &count);
    printf("\nTransposed sparse matrix:\n");
    outputSparseMatrix(sm, count);
       return 0;
} 

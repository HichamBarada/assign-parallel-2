#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define M 3
#define N 3
#define P 3

int A[M][N] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
int B[N][P] = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
int C[M][P];

typedef struct {
    int row;
    int col;
} thread_data;

void *multiply(void *arg) {
    thread_data *data = (thread_data *)arg;
    int row = data->row;
    int col = data->col;

    C[row][col] = 0;
    for (int k = 0; k < N; k++) {
        C[row][col] += A[row][k] * B[k][col];
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[M][P];
    thread_data threadArgs[M][P];

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) {
            threadArgs[i][j].row = i;
            threadArgs[i][j].col = j;
            pthread_create(&threads[i][j], NULL, multiply, (void *)&threadArgs[i][j]);
        }
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) {
            pthread_join(threads[i][j], NULL);
        }
    }

    // Print the result matrix C
    printf("Result Matrix C:\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}
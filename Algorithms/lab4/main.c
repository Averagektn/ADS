#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

void fillPrices(int size, int adj[size][size], int prices[size][size]){
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            if (adj[i][j]) {
                printf("Enter price for %d->%d\n", i, j);
                int tmp;
                scanf_s("%d", &tmp);
                prices[i][j] = tmp;
            }
            if (i == j){
                prices[i][j] = 0;
            }
        }
    }
}

void floyd(int size, int adj[size][size]){
    int c[size][size], a[size][size];
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++) {
            c[i][j] = INT_MAX;
        }
    }
    fillPrices(size, adj, c);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++){
            a[i][j] = c[i][j];
        }
    }
    for (int k = 0; k < size; k++){
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                if (a[i][k] + a[k][j] < a[i][j])
                    a[i][j] = a[i][k]+ a[k][j];
    }

    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            printf("%3d ",a[i][j]);
        }
        printf("\n");
    }
}

//10 30 100 50 10 20 60
int main() {
    int size;
    int adjMatrix[5][5];

    printf("Enter size\n");
    size = 5;
    for (int i = 0; i < size; i++) {
        memset(adjMatrix[i], FALSE, size * sizeof(int));
    }

    adjMatrix[0][1] = TRUE;
    adjMatrix[0][3] = TRUE;
    adjMatrix[0][4] = TRUE;

    adjMatrix[1][2] = TRUE;

    adjMatrix[2][4] = TRUE;

    adjMatrix[3][2] = TRUE;
    adjMatrix[3][4] = TRUE;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++){
            printf("%d ", adjMatrix[i][j]);
        }
        printf("\n");
    }

    floyd(size, adjMatrix);
    return 0;
}

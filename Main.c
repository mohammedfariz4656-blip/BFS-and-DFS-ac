#include <stdio.h>
#include <string.h>

#define MAX 20
#define NAME_LEN 30

char files[MAX][NAME_LEN];
int graph[MAX][MAX];
int visited[MAX];
int n;

/* Breadth-First Search */
void BFS(int start, const char target[]) {
    int queue[MAX];
    int front = 0, rear = 0;
    int found = 0;

    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }

    queue[rear++] = start;
    visited[start] = 1;

    printf("\nBFS Traversal: ");

    while (front < rear) {
        int current = queue[front++];
        printf("%s ", files[current]);

        if (strcmp(files[current], target) == 0) {
            found = 1;
        }

        for (int i = 0; i < n; i++) {
            if (graph[current][i] == 1 && visited[i] == 0) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
    }

    if (found) {
        printf("\nFile found using BFS!\n");
    } else {
        printf("\nFile not found using BFS!\n");
    }
}

/* Depth-First Search */
void DFS(int current, const char target[], int *found) {
    visited[current] = 1;
    printf("%s ", files[current]);

    if (strcmp(files[current], target) == 0) {
        *found = 1;
    }

    for (int i = 0; i < n; i++) {
        if (graph[current][i] == 1 && visited[i] == 0) {
            DFS(i, target, found);
        }
    }
}

int main(void) {
    int start;
    char target[NAME_LEN];

    printf("Enter number of files/directories (1-%d): ", MAX);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid number of files/directories.\n");
        return 1;
    }

    printf("\nEnter file/directory names (one word each):\n");
    for (int i = 0; i < n; i++) {
        if (scanf("%29s", files[i]) != 1) {
            printf("Invalid file name.\n");
            return 1;
        }
    }

    printf("\nEnter the %d x %d adjacency matrix (0 or 1):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (scanf("%d", &graph[i][j]) != 1 ||
                (graph[i][j] != 0 && graph[i][j] != 1)) {
                printf("Invalid matrix value. Enter only 0 or 1.\n");
                return 1;
            }
        }
    }

    printf("\nEnter starting node number (1-%d): ", n);
    if (scanf("%d", &start) != 1 || start < 1 || start > n) {
        printf("Invalid starting node.\n");
        return 1;
    }
    start--; /* Convert to zero-based index. */

    printf("Enter file name to search: ");
    if (scanf("%29s", target) != 1) {
        printf("Invalid search name.\n");
        return 1;
    }

    BFS(start, target);

    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }

    int found = 0;
    printf("\nDFS Traversal: ");
    DFS(start, target, &found);

    if (found) {
        printf("\nFile found using DFS!\n");
    } else {
        printf("\nFile not found using DFS!\n");
    }

    return 0;
}

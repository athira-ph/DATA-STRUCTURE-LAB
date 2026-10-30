#include <stdio.h>
#define MAX 100
int parent[MAX], rank[MAX];
// Initialize each element as a separate set
void makeSet(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}
// Find with Path Compression
int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}
// Union by Rank
void unionSet(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX == rootY) {
        printf("Already connected\n");
        return;
    }
    if (rank[rootX] < rank[rootY]) {
        parent[rootX] = rootY;
    }
    else if (rank[rootX] > rank[rootY]) {
        parent[rootY] = rootX;
    }
    else {
        parent[rootY] = rootX;
        rank[rootX]++;
    }
    printf("Union successful\n");
}
// Check connectivity
void connected(int x, int y) {
    if (find(x) == find(y))
        printf("Connected\n");
    else
        printf("Not Connected\n");
}
int main() {
    int n, choice, x, y;
    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    if (n < 1 || n > MAX) {
        printf("Invalid number of elements\n");
        return 1;
    }
    makeSet(n);
    while (1) {
        printf("\n1. Union");
        printf("\n2. Find");
        printf("\n3. Check Connectivity");
        printf("\n4. Exit");
        printf("\nEnter choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input\n");
            return 1;
        }

        if (choice == 4)
            break;
        if (choice < 1 || choice > 3) {
            printf("Invalid choice\n");
            continue;
        }
        if (choice == 2) {
            printf("Enter element: ");
            if (scanf("%d", &x) != 1) {
                printf("Invalid input\n");
                return 1;
            }
            if (x < 0 || x >= n) {
                printf("Invalid element\n");
                continue;
            }
            printf("Root = %d\n", find(x));
        }
        else {
            printf("Enter two elements: ");
            if (scanf("%d %d", &x, &y) != 2) {
                printf("Invalid input\n");
                return 1;
            }
            if (x < 0 || x >= n || y < 0 || y >= n) {
                printf("Invalid elements\n");
                continue;
            }
            if (choice == 1)
                unionSet(x, y);
            else
                connected(x, y);
        }
    }
    return 0;
}
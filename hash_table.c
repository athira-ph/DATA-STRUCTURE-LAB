#include <stdio.h>
#include <stdlib.h>
#define N 10

struct Node {
    int k, v;
    struct Node *next;
} *chain[N];

int key[N], val[N], status[N];

int hash(int k) { return (k % N + N) % N; }

void insert(int k, int v, int m) {
    int i = hash(k), j, x;

    if (m == 1) {
        struct Node *p = chain[i];
        while (p) {
            if (p->k == k) { p->v = v; return; }
            p = p->next;
        }
        p = malloc(sizeof(*p));
        if (!p) return;
        p->k = k; p->v = v;
        p->next = chain[i];
        chain[i] = p;
    } else {
        int empty = -1;
        for (j = 0; j < N; j++) {
            x = (i + j) % N;
            if (status[x] == 1 && key[x] == k) {
                val[x] = v; return;
            }
            if (status[x] == 2 && empty == -1) empty = x;
            if (status[x] == 0) {
                if (empty == -1) empty = x;
                break;
            }
        }
        if (empty == -1) { printf("Full\n"); return; }
        key[empty] = k; val[empty] = v; status[empty] = 1;
    }
}

void search(int k) {
    int i = hash(k);
    for (int j = 0; j < N; j++) {
        int x = (i + j) % N;
        if (status[x] == 0) break;
        if (status[x] == 1 && key[x] == k) {
            printf("Found %d\n", val[x]); return;
        }
    }
    for (struct Node *p = chain[i]; p; p = p->next)
        if (p->k == k) {
            printf("Found %d\n", p->v); return;
        }
    printf("Not Found\n");
}

void del(int k) {
    int i = hash(k);
    for (int j = 0; j < N; j++) {
        int x = (i + j) % N;
        if (status[x] == 0) break;
        if (status[x] == 1 && key[x] == k) {
            status[x] = 2;
            printf("Deleted\n"); return;
        }
    }
    struct Node **p = &chain[i], *t;
    while (*p) {
        if ((*p)->k == k) {
            t = *p; *p = t->next; free(t);
            printf("Deleted\n"); return;
        }
        p = &(*p)->next;
    }
    printf("Not Found\n");
}

void display() {
    printf("Open:\n");
    for (int i = 0; i < N; i++)
        if (status[i] == 1)
            printf("%d: %d %d\n", i, key[i], val[i]);

    printf("Chain:\n");
    for (int i = 0; i < N; i++) {
        printf("%d: ", i);
        for (struct Node *p = chain[i]; p; p = p->next)
            printf("(%d,%d)->", p->k, p->v);
        printf("NULL\n");
    }
}

int main() {
    int ch, k, v, m;
    while (1) {
        printf("\n1.Insert 2.Search 3.Delete 4.Display 5.Exit\n");
        if (scanf("%d", &ch) != 1) break;
        switch (ch) {
        case 1:
            printf("Key Value Method(1.Chain 2.Open): ");
            scanf("%d%d%d", &k, &v, &m);
            if (m == 1 || m == 2) insert(k, v, m);
            break;
        case 2:
            printf("Key: "); scanf("%d", &k);
            search(k); break;
        case 3:
            printf("Key: "); scanf("%d", &k);
            del(k); break;
        case 4:
            display(); break;
        case 5:
            return 0;
        }
    }
    return 0;
}
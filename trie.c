#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 99

struct Trie {
    struct Trie *child[26];
    int end;
};

struct Trie* create() {
    return calloc(1, sizeof(struct Trie));
}

int isValidWord(const char *s) {
    if (*s == '\0' || strlen(s) > MAX_WORD_LENGTH)
        return 0;
    while (*s) {
        if (*s < 'a' || *s > 'z')
            return 0;
        s++;
    }
    return 1;
}

int readWord(char *s) {
    if (scanf("%99s", s) != 1)
        return 0;

    int ch = getchar();
    if (ch != EOF && !isspace((unsigned char)ch)) {
        while (ch != EOF && !isspace((unsigned char)ch))
            ch = getchar();
        return -1;
    }
    return 1;
}

int insert(struct Trie *r, const char *s) {
    if (!isValidWord(s))
        return 0;

    while (*s) {
        int i = *s++ - 'a';
        if (!r->child[i]) {
            r->child[i] = create();
            if (!r->child[i])
                return 0;
        }
        r = r->child[i];
    }
    r->end = 1;
    return 1;
}

int search(struct Trie *r, const char *s) {
    if (!isValidWord(s))
        return 0;

    while (*s) {
        int i = *s++ - 'a';
        if (!r->child[i]) return 0;
        r = r->child[i];
    }
    return r->end;
}

void display(struct Trie *r, char *s, int n) {
    if (r->end) {
        s[n] = '\0';
        printf("%s\n", s);
    }
    for (int i = 0; i < 26; i++)
        if (r->child[i]) {
            s[n] = i + 'a';
            display(r->child[i], s, n + 1);
        }
}

void autocomplete(struct Trie *r, const char *s) {
    if (!isValidWord(s)) {
        printf("Invalid word or prefix; use lowercase letters a-z (maximum %d characters)\n", MAX_WORD_LENGTH);
        return;
    }

    char word[MAX_WORD_LENGTH + 1];
    strcpy(word, s);
    int n = strlen(s);
    while (*s) {
        int i = *s++ - 'a';
        if (!r->child[i]) {
            printf("No suggestions found\n");
            return;
        }
        r = r->child[i];
    }
    printf("Suggestions:\n");
    display(r, word, n);
}

int main() {
    struct Trie *root = create();
    if (!root) {
        printf("Memory allocation failed\n");
        return 1;
    }

    int ch;
    char s[MAX_WORD_LENGTH + 1];
    while (1) {
        printf("\n1. Insert\n2. Search\n3. Autocomplete\n4. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &ch) != 1) {
            printf("Invalid input\n");
            return 1;
        }
        if (ch == 4) break;
        if (ch < 1 || ch > 3) {
            printf("Invalid choice\n");
            continue;
        }
        printf("Enter word/prefix: ");
        int wordStatus = readWord(s);
        if (wordStatus == 0) {
            printf("Invalid input\n");
            return 1;
        }
        if (wordStatus == -1) {
            printf("Word or prefix exceeds maximum length of %d characters\n", MAX_WORD_LENGTH);
            continue;
        }
        if (!isValidWord(s)) {
            printf("Invalid word or prefix; use lowercase letters a-z\n");
            continue;
        }

        if (ch == 1) {
            if (insert(root, s))
                printf("Word inserted\n");
            else {
                printf("Memory allocation failed\n");
                return 1;
            }
        } else if (ch == 2)
            printf(search(root, s) ? "Word found\n" : "Word not found\n");
        else
            autocomplete(root, s);
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
    int key, height;
    struct Node *left, *right;
} Node;
int max(int a, int b) {
    return a > b ? a : b;
}
int height(Node *n) {
    return n ? n->height : 0;
}
int balance(Node *n) {
    return n ? height(n->left) - height(n->right) : 0;
}
Node *create(int key) {
    Node *n = malloc(sizeof(Node));
    if (!n) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    n->key = key;
    n->height = 1;
    n->left = n->right = NULL;
    return n;
}
// Right Rotation
Node *rightRotate(Node *y) {
    Node *x = y->left;
    y->left = x->right;
    x->right = y;
    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));
    return x;
}
// Left Rotation
Node *leftRotate(Node *x) {
    Node *y = x->right;
    x->right = y->left;
    y->left = x;
    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));
    return y;
}
// Balance AVL Tree
Node *rebalance(Node *root) {
    if (!root) return NULL;
    root->height = 1 + max(height(root->left), height(root->right));
    if (balance(root) > 1) {
        if (balance(root->left) < 0)
            root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance(root) < -1) {
        if (balance(root->right) > 0)
            root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}
// Insertion
Node *insert(Node *root, int key) {
    if (!root) return create(key);
    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else {
        printf("Duplicate key!\n");
        return root;
    }
    return rebalance(root);
}
// Find minimum node
Node *minNode(Node *root) {
    while (root->left)
        root = root->left;
    return root;
}
// Deletion
Node *deleteNode(Node *root, int key) {
    if (!root) return NULL;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (!root->left || !root->right) {
            Node *temp = root->left ? root->left : root->right;
            free(root);
            return temp;
        }
        Node *temp = minNode(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }

    return rebalance(root);
}
// Search
Node *search(Node *root, int key) {
    if (!root || root->key == key) return root;
    if (key < root->key) return search(root->left, key);
    return search(root->right, key);
}
// Traversals
void inorder(Node *root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}
void preorder(Node *root) {
    if (root) {
        printf("%d ", root->key);
        preorder(root->left);
        preorder(root->right);
    }
}

void freeTree(Node *root) {
    if (root) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int readInt(const char *prompt, int *value) {
    printf("%s", prompt);
    if (scanf("%d", value) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 0;
    }
    return 1;
}

int main() {
    Node *root = NULL;
    int choice, key;
    while (1) {
        printf("\n1.Insert  2.Delete  3.Search");
        printf("\n4.Inorder  5.Preorder  6.Exit");
        printf("\n");
        if (!readInt("Enter choice: ", &choice)) {
            freeTree(root);
            return EXIT_FAILURE;
        }
        switch (choice) {
            case 1:
                if (!readInt("Enter key: ", &key)) {
                    freeTree(root);
                    return EXIT_FAILURE;
                }
                root = insert(root, key);
                break;
            case 2:
                if (!readInt("Enter key: ", &key)) {
                    freeTree(root);
                    return EXIT_FAILURE;
                }
                root = deleteNode(root, key);
                break;
            case 3:
                if (!readInt("Enter key: ", &key)) {
                    freeTree(root);
                    return EXIT_FAILURE;
                }
                printf(search(root, key) ? "Key Found\n" : "Not Found\n");
                break;

            case 4:
                inorder(root);
                printf("\n");
                break;

            case 5:
                preorder(root);
                printf("\n");
                break;
            case 6:
                freeTree(root);
                return 0;
            default:
                printf("Invalid choice\n");
        }
    }
}
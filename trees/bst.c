#include <stdio.h>
#include <stdlib.h>

struct bst {
    int data;
    struct bst *left, *right;
};

typedef struct bst node;
node *root = NULL;

node *create() {
    node *temp;
    temp = (node *)malloc(sizeof(node));
    printf("Enter the data item: ");
    scanf("%d",&temp->data);
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

void insert() {
    node *temp = create();
    if (root==NULL) {
        root = temp;
    }
    else {
        node *temp1 = root;
        while (temp1!=NULL) {
            if (temp->data < temp1->data) {
                if (temp1->left==NULL) {
                    temp1->left = temp;
                    break;
                }
                temp1 = temp1->left;
            }
            else {
                if (temp1->right==NULL) {
                    temp1->right = temp;
                    break;
                }
                temp1 = temp1->right;
            }
        }
    }
    printf("item %d inserted\n",temp->data);
}

int findmin(node *root) {
    if (root==NULL) return -1;
    if (root->left!=NULL)
        return findmin(root->left);
    return root->data;
}

node *delete(node *root, int data) {
    node *temp;
    int min;
    if (root==NULL) return NULL;
    if (data < root->data) 
        root->left = delete(root->left,data);
    else if (data > root->data)
        root->right = delete(root->right,data);
    else {
        if (root->left==NULL && root->right==NULL) {
            free(root);
            root = NULL;
        }
        else if (root->left==NULL) {
            temp = root;
            root = root->right;
            free(temp);
        }
        else if (root->right==NULL) {
            temp = root;
            root = root->left;
            free(temp);
        }
        else {
            min = findmin(root->right);
            root->data = min;
            root->right = delete(root->right,min);
        }
    }
    return root;
}

void display(node *temp) {
    if (temp!=NULL) {
        display(temp->left);
        display(temp->right);
        printf("%d\t",temp->data);
    }
}

void main() {
    int ch,data;
    printf("1.insert  2.delete  3.display  4.exit\n");
    while (1) {
        printf("Enter choice: ");
        scanf("%d",&ch);
        switch (ch) {
            case 1: insert(); break;
            case 2:
                printf("Enter data item: ");
                scanf("%d",&data);
                root = delete(root, data);
                break;
            case 3: display(root); printf("\n"); break;
            case 4: printf("goodbye\n"); exit(0);
            default: printf("invalid choice\n");
        }
    }
}
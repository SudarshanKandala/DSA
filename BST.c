#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    struct node *left;
    struct node *right;
};

void inorder(struct node *root){
    if(root->left!=NULL)
        inorder(root->left);
    printf("%d ",root->data);
    if(root->right!=NULL)
        inorder(root->right);
}

void preorder(struct node *root){
    printf("%d ",root->data);
    if(root->left!=NULL)
        preorder(root->left);
    if(root->right!=NULL)
        preorder(root->right);
}

void postorder(struct node *root){
    if(root->left!=NULL)
        postorder(root->left);
    if(root->right!=NULL)
        postorder(root->right);
    printf("%d ",root->data);
}

void Insert(struct node *root,struct node *new){
    if(root->left==NULL && new->data<root->data)
        root->left=new;
    else if(root->right==NULL && new->data>root->data)
        root->right=new;
    else if((root->left!=NULL && new->data<root->data))
        Insert(root->left,new);
    else if(root->right!=NULL && new->data>root->data)
        Insert(root->right,new);
}

int height(struct node *root){
    int hl=0,hr=0;
    if(root->left==NULL && root->right==NULL)
        return 1;
    if(root->left!=NULL){
        hl=height(root->left);
        hl++;
    }
    if(root->right!=NULL){
        hr=height(root->right);
        hr++;
    }
    if(hl>hr)
    return hl;
    else if(hr>=hl)
    return hr;
}

int main(){
    struct node *root;
    int data;
    printf("Enter data: ");
    scanf("%d",&root->data);
    root->left=NULL;
    root->right=NULL;
    int exit;
    while(1){
        printf("Enter data: ");
        scanf("%d",&data);
        struct node *ptr=malloc(sizeof(struct node));
        ptr->data=data;
        ptr->left=NULL;
        ptr->right=NULL;
        Insert(root,ptr);
        printf("Want to exit: ");
        scanf("%d",&exit);
        if(exit==1)
            break;
    }
    printf("Inorder traversal will be: ");
    inorder(root);
    printf("\n");
    printf("preorder traversal will be: ");
    preorder(root);
    printf("\n");
    printf("postorder traversal will be: ");
    postorder(root);
    int h=height(root);
    printf("\n");
    printf("The height of tree is: %d",h-1);
    return 0;
}
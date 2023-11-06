#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 100

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

// struct node* serch(struct node *root,struct node *ptr){
//     if(root->left->left==ptr || root->left->right==ptr || root->right->left==ptr || root->right->right==ptr)
//         return root;
//     if(root->left!=NULL)
//         serch(root->left,ptr);
//     if(root->right!=NULL)
//         serch(root->right,ptr);
// }

struct node *serch(struct node *root,int data){
    if (root == NULL || root->data == data)
        return root;
    
    struct node* leftResult;
    leftResult = serch(root->left, data);
    if (leftResult != NULL) 
        return leftResult;
    
    struct node *rightresult;
    rightresult=serch(root->right,data);
    if(rightresult!=NULL)
        return rightresult;
}

struct node* Insert(int *ptr,int count){
    struct node *root=malloc(sizeof(struct node));
    struct node *pt;
    root->data=ptr[1];
    root->left=NULL;
    root->right=NULL;
    for(int i=1;i<(count/2);i++){
        pt=serch(root,ptr[i]);
        pt->left=(struct node *)malloc(sizeof(struct node));
        pt->left->data=ptr[2*i];
        pt->left->left=NULL;
        pt->left->right=NULL;
        pt->right=(struct node *)malloc(sizeof(struct node));
        pt->right->data=ptr[2*i+1];
        pt->right->left=NULL;
        pt->right->right=NULL;
    }
    return root;
}

int main(){
    int exit;
    int *ptr;
    ptr=(int *)calloc(MAX_SIZE,sizeof(int));
    printf("Enter the elements: ");
    int count=1;
    while(1){
        scanf("%d",&ptr[count]);
        count++;
        printf("Want to exit: ");
        scanf("%d",&exit);
        if(exit==1)
            break;
    }
    struct node *root=Insert(ptr,count);
    printf("Inorder traversal will be: ");
    inorder(root);
    printf("\n");
    printf("preorder traversal will be: ");
    preorder(root);
    printf("\n");
    printf("postorder traversal will be: ");
    postorder(root);
    printf("\n");
    printf("height of tree will be: %d",height(root)-1);
    return 0;
}
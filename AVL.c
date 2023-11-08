#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

struct node{
    int data;
    struct node *right;
    struct node *left;
}*root=NULL;

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

struct node *Createnode(int a){
    struct node *temp=malloc(sizeof(struct node));
    temp->data=a;
    temp->left=NULL;
    temp->right=NULL;
    return temp;
}

int height(struct node *temp){
    if(temp==NULL)
        return 0;
    if(temp->right==NULL && temp->left==NULL)
        return 1;
    int hl=0,hr=0;
    if(temp->left!=NULL){
        hl=height(temp->left);
        hl++;
    }
    if(temp->right!=NULL){
        hr=height(temp->right);
        hr++;
    }
    if(hl>hr)
        return hl;
    else if(hl<=hr)
        return hr;
}

struct node *serchfather(struct node *temp,struct node *ptr){
    if(temp==ptr)
        return NULL;
    if(temp==NULL || temp->left==ptr || temp->right==ptr)
        return temp;
    struct node *left=serchfather(temp->left,ptr);
    if(left!=NULL)
        return left;
    struct node *right=serchfather(temp->right,ptr);
    if(right!=NULL)
        return right;
}

void rotateLL(struct node *Gfather){
    if(Gfather==root){
        struct node *temp1=root;
        struct node *temp2=root->left;
        struct node *temp3=root->left->right;
        root->left=NULL;
        root=temp2;
        root->right=temp1;
        temp1->left=temp3;
    }
    else if(Gfather!=root){
        struct node *temp=serchfather(root,Gfather);
        if(temp->left==Gfather){
            struct node *temp1=Gfather;
            struct node *temp2=Gfather->left;
            struct node *temp3=Gfather->left->right;
            Gfather->left=NULL;
            temp->left=temp2;
            temp2->right=temp1;
            temp1->left=temp3;
        }
        else if(temp->right==Gfather){
            struct node *temp1=Gfather;
            struct node *temp2=Gfather->left;
            struct node *temp3=Gfather->left->right;
            Gfather->left=NULL;
            temp->right=temp2;
            temp2->right=temp1;
            temp1->left=temp3;
        }
    }
}

void rotateRR(struct node *Gfather){
    if(root==Gfather){
        struct node *temp1=root;
        struct node *temp2=root->right;
        struct node *temp3=root->right->left;
        root->right=NULL;
        root=temp2;
        root->left=temp1;
        temp1->right=temp3;
    }
    else if(root!=Gfather){
        struct node *temp=serchfather(root,Gfather);
        if(temp->left==Gfather){
            struct node *temp1=Gfather;
            struct node *temp2=Gfather->right;
            struct node *temp3=Gfather->right->left;
            Gfather->right=NULL;
            temp->left=temp2;
            temp2->left=temp1;
            temp1->right=temp3;
        }
        else if(temp->right==Gfather){
            struct node *temp1=Gfather;
            struct node *temp2=Gfather->right;
            struct node *temp3=Gfather->right->left;
            Gfather->right=NULL;
            temp->right=temp2;
            temp2->left=temp1;
            temp1->right=temp3;
        }
    }
}

void rotateLR(struct node *Gfather){
    struct node *temp1=Gfather->left;
    struct node *temp2=Gfather->left->right;
    struct node *temp3=Gfather->left->right->left;
    temp1->right=NULL;
    Gfather->left=temp2;
    Gfather->left->left=temp1;
    temp1->right=temp3;
    rotateLL(Gfather);
}

void rotateRL(struct node *Gfather){
    struct node *temp1=Gfather->right;
    struct node *temp2=Gfather->right->left;
    struct node *temp3=Gfather->right->left->right;
    temp1->left=NULL;
    Gfather->right=temp2;
    Gfather->right->right=temp1;
    temp1->left=temp3;
    rotateRR(Gfather);
}

int check(struct node *ptr){
    if(height(ptr->left)-height(ptr->right)>1)
        return 1;
    else if(height(ptr->left)-height(ptr->right)<-1)
        return -1;
    else 
        return 0;
}

void rotating(struct node *temp,struct node *ptr,struct node *tempfather){
    struct node *help;
    while(temp!=root){
        tempfather=serchfather(root,temp);
        int bal=check(tempfather);
        if(bal==1){
            if(temp->right==ptr)
                rotateLR(tempfather);
            else if(temp->left==ptr)
                rotateLL(tempfather);
        }
        else if(bal==-1){
            if(temp->left==ptr)
                rotateRL(tempfather);
            else if(temp->right==ptr)
                rotateRR(tempfather);
        }
        help=temp;
        temp=tempfather;
        ptr=help;
    }
}

void AVL(struct node *temp,struct node *ptr){
    struct node *tempfather;
    if(temp->left==NULL && temp->data>ptr->data){
        temp->left=ptr;
        if(temp!=root){
            tempfather=serchfather(root,temp);
            int bal=check(tempfather);
            if(bal==1)
                rotateLL(tempfather);
            else if(bal==-1)
                rotateRL(tempfather);
            if(tempfather!=root)
            rotating(tempfather,temp,serchfather(root,tempfather));
        }
    }
    else if(temp->right==NULL && temp->data<=ptr->data){
        temp->right=ptr;
        if(temp!=root){
            tempfather=serchfather(root,temp);
            int bal=check(tempfather);
            if(bal==1)
                rotateLR(tempfather);
            else if(bal==-1)
                rotateRR(tempfather);
            if(tempfather!=root)
            rotating(tempfather,temp,serchfather(root,tempfather));
        }
    }
    else if(temp->left!=NULL && temp->data>ptr->data)
        AVL(temp->left,ptr);
    else if(temp->right!=NULL && temp->data<ptr->data)
        AVL(temp->right,ptr);
}

int main(){
    int n;
    printf("Enter the number of elements: ");
    scanf("%d",&n);
    struct node *temp;
    int a;
    while(n--){
        scanf("%d",&a);
        if(root==NULL){
            root=Createnode(a);
        }
        else{
            temp=Createnode(a);
            AVL(root,temp);
        }
    }
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
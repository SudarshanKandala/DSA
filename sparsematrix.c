// transpose, addition, multiplication

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

struct node{
    int row;
    int col;
    int data;
    struct node *right;
    struct node *down;
};

void display(struct node *root){
    struct node *temp=root->down;
    int count=0;
    struct node *temp1;
    count=0;
    temp=root->right;
    while(temp!=NULL){
        count++;
        temp=temp->right;
    }
    printf("The number of columns are: %d\n",count);
    int count1=0;
    temp=root->down;
    while(temp!=NULL){
        count1++;
        temp=temp->down;
    }
    printf("The number of rows are: %d\n",count1);
    printf("\n\n");
    temp=root->down;
    while(temp!=NULL){
        temp1=temp;
        int prev=0;
        int curr=0;
        if(temp1->right!=NULL){
            do{
                temp1=temp1->right;
                curr=temp1->col;
                for(int i=0;i<curr-prev-1;i++)
                    printf("0\t");
                prev=curr;
                printf("%d\t",temp1->data);
            }while(temp1->right!=temp);
            for(int i=0;i<count-prev;i++)
                printf("0\t");
        }
        else{
            for(int i=0;i<count;i++)
                printf("0\t");
        }
        printf("\n\n\n");
        temp=temp->down;
    }
}

void CreateMatrix(int row,int col,int data,struct node *root){
    struct node *temp;
    int count=0;
    // Creating rows and column nodes
    // if down and right pointers of root are equal to NULL

    if(root->right==NULL && root->down==NULL){
        temp=root;
        for(int i=0;i<row;i++){
            temp->down=(struct node*)malloc(sizeof(struct node));
            temp=temp->down;
            temp->col=0;
            temp->row=i+1;
            temp->down=NULL;
            temp->right=NULL;
        }
        temp=root;
        for(int i=0;i<col;i++){
            temp->right=(struct node*)malloc(sizeof(struct node));
            temp=temp->right;
            temp->col=i+1;
            temp->row=0;
            temp->down=NULL;
            temp->right=NULL;
        }
    }

    // if down and right pointers of root are not equal to NULL

    else{
        int count=0;
        temp=root;
        while(temp->right!=NULL){
            count++;
            temp=temp->right;
        }
        if(count<col){
            for(int i=1;i<=col-count;i++){
                temp->right=(struct node*)malloc(sizeof(struct node));
                temp=temp->right;
                temp->col=count+i;
                temp->row=0;
                temp->down=NULL;
                temp->right=NULL;
            }
        }
        count=0;
        temp=root;
        while(temp->down!=NULL){
            count++;
            temp=temp->down;
        }
        if(count<row){
            for(int i=1;i<=row-count;i++){
                temp->down=(struct node*)malloc(sizeof(struct node));
                temp=temp->down;
                temp->col=0;
                temp->row=count+i;
                temp->right=NULL;
                temp->down=NULL;
            }
        }
    }

    // creating node for data

    struct node *temp1=NULL;
    struct node *temp2=NULL;
    struct node *temp3;
    struct node *temp4;
    temp1=root;
    temp2=root;
    for(int i=0;i<row;i++)
        temp1=temp1->down;
    for(int i=0;i<col;i++)
        temp2=temp2->right;
    struct node *new=(struct node*)malloc(sizeof(struct node));
    new->col=col;
    new->row=row;
    new->data=data;
    if(temp1->right==NULL && temp2->down==NULL){
        temp1->right=new;
        temp2->down=new;
        new->right=temp1;
        new->down=temp2;
    }
    else if(temp1->right==NULL && temp2->down!=NULL){
        temp3=temp2;
        do{
            if(temp3->row<row && temp3->down->row>row){
                temp4=temp3->down;
                temp3->down=new;
                new->down=temp4;
                temp1->right=new;
                new->right=temp1;
                break;
            }
            else if(temp3->row<row && temp3->down->row==0){
                temp4=temp3->down;
                temp3->down=new;
                new->down=temp4;
                temp1->right=new;
                new->right=temp1;
                break;
            }
            temp3=temp3->down;
        }while(temp3!=temp2);
    }
    else if(temp1->right!=NULL && temp2->down==NULL){
        temp3=temp1;
        do{
            if(temp3->col<col && temp3->right->col>col){
                temp4=temp3->right;
                temp3->right=new;
                new->right=temp4;
                temp2->down=new;
                new->down=temp2;
                break;
            }
            else if(temp3->col<col && temp3->right->col==0){
                temp4=temp3->right;
                temp3->right=new;
                new->right=temp4;
                temp2->down=new;
                new->down=temp2;
                break;
            }
            temp3=temp3->right;
        }while(temp3!=temp1);
    }
    else if(temp1->right!=NULL && temp2->down!=NULL){
        temp3=temp1;
        temp4=temp2;
        do{
            if(temp3->col<col && temp3->right->col>col)
                break;
            else if(temp3->col<col && temp3->right->col==0)
                break;
            temp3=temp3->right;
        }while(temp3!=temp1);
        do{
            if(temp4->row<row && temp4->down->row>row)
                break;
            else if(temp3->row<row && temp3->down->row==0)
                break;
            temp4=temp4->down;
        }while(temp4!=temp2);
        struct node *temp5,*temp6;
        temp5=temp3->right;
        temp3->right=new;
        new->right=temp5;
        temp6=temp4->down;
        temp4->down=new;
        new->down=temp6;
    }
}

int main(){
    int row,col,n,data;
    struct node *root;
    root=(struct node*)malloc(sizeof(struct node));
    root->col=-1;
    root->row=-1;
    root->down=NULL;
    root->right=NULL;
    while(1){
        printf("Enter the row number: ");
        scanf("%d",&row);
        printf("Enter the colunm number: ");
        scanf("%d",&col);
        printf("Enter the data: ");
        scanf("%d",&data);
        CreateMatrix(row,col,data,root);
        printf("If you want to exit Enter 1\n");
        scanf("%d",&n);
        if(n==1)
            break;
    }
    display(root);
}
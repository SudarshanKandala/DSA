#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    struct node *next;
};

struct node *Createnode(){
    struct node *ptr;
    ptr=(struct node*)malloc(sizeof(struct node));
    //printf("Enter the number: ");
    scanf("%d",&ptr->data);
    return ptr;
}

int main(){
    struct node *head;
    head=(struct node*)malloc(sizeof(struct node));
    struct node *temp;
    temp=head;
    int n;
    //printf("Enter the size of LL: ");
    scanf("%d",&n);
    //printf("Enter the number: ");
    scanf("%d",&head->data);
    for(int i=1;i<n;i++){
        temp->next=Createnode();
        temp=temp->next;
        if(i==n-1)
            temp->next=NULL;
    }
temp=head;
    struct node *help=NULL,*help1=NULL,*prev=head;
    for(int i=0;i<n;i++){
        temp=head;
        for(int j=0;j<n-i-1;j++){
            help=NULL;help1=NULL;
            if(temp->data>temp->next->data){
                if(temp==head){
                    help=temp;
                    help1=temp->next->next;
                    temp=temp->next;
                    temp->next=help;
                    temp->next->next=help1;
					head=temp;
                    prev=temp;
                    temp=temp->next;
                }
                else{
                    help=temp;
                    help1=temp->next->next;
                    temp=temp->next;
                    temp->next=help;
                    temp->next->next=help1;
                    prev->next=temp;
                    prev=temp;
                    temp=temp->next;
                }
            }
            else{
				prev=temp;
				temp=temp->next;
				
			}
                
        }
    }
    temp=head;
    while(temp!=NULL){
        printf("%d\n",temp->data);
        temp=temp->next;
    }    
	return 0;
}
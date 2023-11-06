#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
struct node{
    int data;
    struct node *next;
};
int i;
struct node *Create(char c){
    struct node *ptr=malloc(sizeof(struct node));
    ptr->data=c-'0';
    ptr->next=NULL;
    return ptr;
}

void display(struct node *head){
    struct node *temp=head;
    while(temp!=NULL){
        printf("%d",temp->data);
        temp=temp->next;
    }
    printf("\n");
}

struct node *rev(struct node *head){
    struct node *temp;
    struct node *temp1;
    struct node *temp2;
    struct node *prev;
    temp=head;
    int count=0;
    while(temp!=NULL){
        count++;
        temp=temp->next;
    }
    for(int i=0;i<count-1;i++){
        temp=head;prev=head;
        for(int j=0;j<count-i-1;j++){
            if(temp==head){
                temp1=temp->next->next;
                temp2=temp->next;
                temp->next=temp1;
                temp2->next=temp;
                head=temp2;
                prev=head;
            }
            else{
                temp1=temp->next;
                temp2=temp->next->next;
                prev->next=temp1;
                temp1->next=temp;
                temp->next=temp2;
                prev=temp1;    
            }
        }
    }
    return head;
}

struct node *sum(struct node *head1,struct node *head2){
    int carry=0;
    struct node *temp1,*temp2,*temp;
    temp1=head1;
    temp2=head2;
    int count1=0,count2=0;
    while (temp1!=NULL){
        count1++;
        temp1=temp1->next;
    }
    while (temp2!=NULL){
        count2++;
        temp2=temp2->next;
    }
    struct node *head;
    head=(struct node*)malloc(sizeof(struct node));
    head->data=0;
    head->next=NULL;
    temp=head;
    if(count1==count2){
        for(int i=0;i<count1;i++){
            temp->next=Create('0');
            temp=temp->next;
        }
    }
    else if(count1>count2){ 
        for(int i=0;i<count1;i++){
            temp->next=Create('0');
            temp=temp->next;
        }
        temp2=head2;
        while (temp2->next!=NULL)
        temp2=temp2->next;
        for(int i=0;i<count1-count2;i++){
            temp2->next=Create('0');
            temp2=temp2->next;
        }
    }
    else if (count1<count2){
        for(int i=0;i<count2;i++){
            temp->next=Create('0');
            temp=temp->next;
        }
        temp1=head1;
        while (temp1->next!=NULL)
        temp1=temp1->next;
        for(int i=0;i<count2-count1;i++){
            temp1->next=Create('0');
            temp1=temp1->next;
        }
    }
    temp1=head1;
    temp2=head2;
    temp=head;
    while(temp1!=NULL){
        temp->data=(temp1->data+temp2->data+carry)%10;
        carry=(temp1->data+temp2->data+carry)/10;
        temp=temp->next;
        temp1=temp1->next;
        temp2=temp2->next;
    }
    if(carry)
    temp->data=carry;
    head=rev(head);
    if(head->data==0){
        head=head->next;
        return head;
    }
    else if(head->data!=0)
    return head;
}

int main(){
    char str1[1000];
    printf("Enter first number: ");
    scanf("%s",str1);
    struct node *head1;
    head1=(struct node*)malloc(sizeof(struct node));
    head1->data=str1[0]-'0';
    struct node *temp=head1;
    for(int i=1;str1[i]!='\0';i++){
        temp->next=Create(str1[i]);
        temp=temp->next;
    }
    struct node *head3=rev(head1);
    char str2[1000];
    printf("Enter second number: ");
    scanf("%s",str2);
    struct node *head2;
    head2=(struct node*)malloc(sizeof(struct node));
    head2->data=str2[0]-'0';
    temp=head2;
    for(int i=1;str2[i]!='\0';i++){
        temp->next=Create(str2[i]);
        temp=temp->next;
    }
    struct node *head4=rev(head2);
    struct node *result=sum(head3,head4);
    printf("The final sum is: ");
    display(result);
    return 0;
}
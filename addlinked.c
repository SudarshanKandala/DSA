#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

struct node{
    int data;
    struct node *next;
    struct node *prev;
};

struct node *Createnode(){
    struct node *temp;
    temp=(struct node*)malloc(sizeof(struct node));
    temp->data=0;
    temp->next=NULL;
    temp->prev=NULL;
    return temp;
}

void display(struct node *head){
    struct node *temp=head;
    while(temp!=NULL){
        printf("%d ",temp->data);
        temp=temp->next;
    }
    printf("\n");
}

struct node *linked(char str[]){
    int a=0,b;
    int count=1;
    struct node *head=NULL;
    struct node *temp;
    for(int i=0;str[i]!='\0';i++){
        if(i%4==0)
            a=a+(str[i]-'0')*1000;
        else if(i%4==1){
            count++;
            a=a+(str[i]-'0')*100;
        }
        else if(i%4==2){
            count++;
            a=a+(str[i]-'0')*10;
        }
        else if(i%4==3){
            count++;
            a=a+(str[i]-'0');
        }
        if(str[i+1]=='\0'){
            while(1){
                int b=a%10;
                if(b>0)
                    break;
                a=a/10;
            }
        }
        if(count%4==0 || str[i+1]=='\0'){
            count=1;
            if(head==NULL){
                head=Createnode();
                head->data=a;
                temp=head;
            }
            else{
                temp->next=Createnode();
                temp->next->prev=temp;
                temp=temp->next;
                temp->data=a;
            }
            a=0;
        }
    }    
    return head;
}

int cout(int u1){
    int k1=0;
    while(1){
        if(u1==0)
        break;
        k1++;
        u1=u1/10;
    }
    return k1;
    
}

struct node *add(struct node *head1,struct node *head2){
    struct node *temp1=head1,*temp2=head2;
    struct node *head=NULL;
    int count1=0,count2=0;
    while(temp1!=NULL){
        count1++;
        temp1=temp1->next;
    }
    while(temp2!=NULL){
        count2++;
        temp2=temp2->next;
    }
    int carry=0;
    if(count1>count2){
        temp2=head2;
        while(temp2->next!=NULL)
            temp2=temp2->next;
        for(int i=0;i<count1-count2;i++){
            temp2->next=Createnode();
            temp2->next->prev=temp2;
            temp2=temp2->next;
            temp2->data=0;
        }
    }
    else if(count1<=count2){
        temp1=head1;
        while(temp1->next!=NULL)
            temp1=temp1->next;
        for(int i=0;i<count2-count1;i++){
            temp1->next=Createnode();
            temp1->next->prev=temp1;
            temp1=temp1->next;
            temp1->data=0;
        }
    }
    temp1=head1;
    temp2=head2;
    struct node *temp;
    int count;
    int a=temp1->data;
    int b=temp2->data;
    carry=0;
    int p;
    int k1=cout(temp1->data);
    int k2=cout(temp2->data);
    count=4;
    for(int i=0;i<4-k1;i++)
        a=a*10;
    for(int i=0;i<4-k2;i++)
        b=b*10;
    while(1){
        count--;
        p=1;
        for(int i=0;i<count;i++)
            p=p*10;
        if(head==NULL){
            head=Createnode();
            temp=head;
        }
        else{
            temp->next=Createnode();
            temp->next->prev=temp;
            temp=temp->next;
        }
        temp->data=(a/p+b/p+carry)%10;
        carry=(a/p+b/p)/10;
        a=a%p;
        b=b%p;
        if(count==0){
            temp1=temp1->next;
            temp2=temp2->next;
            if(temp1==NULL)
                break;
            a=temp1->data;
            b=temp2->data;
            k1=cout(temp1->data);
            k2=cout(temp2->data);
            count=4;
            for(int i=0;i<4-k1;i++)
            a=a*10;
            for(int i=0;i<4-k2;i++)
            b=b*10;
        }
    }
    if(carry==1){
        temp->next=Createnode();
        temp->next->prev=temp;
        temp=temp->next;
        temp->data=carry;
    }
    return head;
}

int main(){
    char str1[1000];
    printf("Enter the number: ");
    scanf("%s",&str1);
    int count=0;
    for(int i=0;str1[i]!='\0';i++)
        count++;
    char temp;
    for(int i=0;i<count/2;i++){
        temp=str1[i];
        str1[i]=str1[count-i-1];
        str1[count-i-1]=temp;
    }
    struct node *head1=linked(str1);
    printf("After reversing: ");
    display(head1);

    char str2[1000];
    printf("\nEnter the number: ");
    scanf("%s",&str2);
    count=0;
    for(int i=0;str2[i]!='\0';i++)
        count++;
    for(int i=0;i<count/2;i++){
        temp=str2[i];
        str2[i]=str2[count-i-1];
        str2[count-i-1]=temp;
    }
    struct node *head2=linked(str2);
    printf("After reversing: ");
    display(head2);
    struct node *head=add(head1,head2);
    struct node *tempa=head;
    while(tempa->next!=NULL)
        tempa=tempa->next;
    printf("\nSum is: ");
    while(tempa!=NULL){
        printf("%d",tempa->data);
        tempa=tempa->prev;
    }
}
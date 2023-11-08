#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

struct node{
    int coeff;
    int index;
    struct node *next;
};

struct node* newnode(){
    struct node *new;
    new=(struct node*)malloc(sizeof(struct node));
    printf("Enter coefficient: ");
    scanf("%d",&new->coeff);
    printf("Enter index: ");
    scanf("%d",&new->index);
    return new;
}

void display(struct node* head){
    int coeff=0,index=0;
    struct node *temp=head;
    while(temp!=NULL){
        coeff=temp->coeff;
        index=temp->index;
            if(coeff<0){
                printf(" - ");
                printf("%dX^",(-1)*coeff);
                printf("%d",index);
            }
            else if(coeff>0){
                if(head!=temp)
                printf(" + ");
                printf("%dX^",coeff);
                printf("%d",index);
            }
        temp=temp->next;
    }
    printf("\n");
}                                   

struct node* declaration(){
    struct node *new;
    new=(struct node*)malloc(sizeof(struct node));
    new->coeff=0;
    new->index=0;
    new->next=NULL;
    return new;
}

struct node *swap(struct node *ptr1,struct node *ptr2,struct node *head){
    struct node *temp2,*temp1,*prev1=head,*prev2=head;
    if(ptr1!=head){
    while(prev1->next!=ptr1)
    prev1=prev1->next;
    while(prev2->next!=ptr2)
    prev2=prev2->next;
    temp1=ptr1->next;
    temp2=ptr2->next;
    prev1->next=ptr2;
    prev1->next->next=temp1;
    prev2->next=ptr1;
    prev2->next->next=temp2;
    }
    else if(ptr1==head){
        temp1=ptr1->next;
    temp2=ptr2->next;
    }
    return head;
}

struct node *sort(struct node *head){
    struct node *temp=head;
    struct node *temp1=head;
    int size=0;
    while(temp!=NULL){
        size++;
        temp=temp->next;
    }
    int n=size;
    temp=head;
    struct node *help=NULL,*help1=NULL,*prev=head;
    for(int i=0;i<n;i++){
        temp=head;
        for(int j=0;j<n-i-1;j++){
            help=NULL;help1=NULL;
            if(temp->index<temp->next->index){
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
    return head;
}

struct node *reduction(struct node *head){
    struct node *temp=head;
    struct node *temp1;
    struct node *del;
    while(temp!=NULL){
        temp1=temp->next;
        while(temp1!=NULL){
            if(temp->index==temp1->index){
                temp->coeff=temp->coeff+temp1->coeff;
                del=head;
                while(del->next!=temp1)
                del=del->next;
                del->next=temp1->next;
            }
            temp1=temp1->next;
        }
        temp=temp->next;
    }
    return head;
}

struct node* add(struct node *head1,struct node *head2){
    struct node *head;
    struct node *temp1;
    struct node *temp2;
    struct node *temp;
    head=NULL;
    temp=head;
    temp1=head1;
    temp2=head2;
    while(temp1!=NULL){
        if(temp1==head1){
            temp=declaration();
            temp->coeff=temp1->coeff;
            temp->index=temp1->index;
            head=temp;
        }
        else{
            temp->next=declaration();
            temp=temp->next;
            temp->coeff=temp1->coeff;
            temp->index=temp1->index;
        }
        temp1=temp1->next;
    }

    while(temp2!=NULL){
            temp->next=declaration();
            temp=temp->next;
            temp->coeff=temp2->coeff;
            temp->index=temp2->index;
            if(temp2->next==NULL)
                temp->next=NULL;
        temp2=temp2->next;
    }
    reduction(head);
    return head;
}

struct node *Sub(struct node *head1,struct node *head2){
    struct node *head;
    struct node *temp1;
    struct node *temp2;
    struct node *temp;
    head=NULL;
    temp=head;
    temp1=head1;
    temp2=head2;
    while(temp1!=NULL){
        if(temp1==head1){
            temp=declaration();
            temp->coeff=temp1->coeff;
            temp->index=temp1->index;
            head=temp;
        }
        else{
            temp->next=declaration();
            temp=temp->next;
            temp->coeff=temp1->coeff;
            temp->index=temp1->index;
        }
        temp1=temp1->next;
    }

    while(temp2!=NULL){
            temp->next=declaration();
            temp=temp->next;
            temp->coeff=(-1)*temp2->coeff;
            temp->index=temp2->index;
            if(temp2->next==NULL)
                temp->next=NULL;
        temp2=temp2->next;
    }
    reduction(head);
    return head;
}

struct node* multiply(struct node *head1,struct node *head2){
    struct node *temp1;
    struct node *temp2;
    struct node *temp;
    struct node *new;
    temp1=head1;
    struct node *head=NULL;
    while(temp1!=NULL){
        temp2=head2;
        while(temp2!=NULL){
            new=declaration();
            new->coeff=temp1->coeff*temp2->coeff;
            new->index=temp1->index+temp2->index;

            new->next=NULL;
            if(head==NULL){
                head=new;
                temp=head;
            }
            else{
                temp->next=new;
                temp=temp->next;
            }
            temp2=temp2->next;
        }
        temp1=temp1->next;
    }
    reduction(head);
    return head;
}

void Evaluate(struct node *head){
    float ans;
    float val;
    printf("Enter the value: ");
    scanf("%f",&val);
    while(head!=NULL){
        ans=ans+head->coeff*pow(val,head->index);
        head=head->next;
    }
    printf("The final value is: %f\n",ans);
}

struct node *differentiation(struct node *head){
    struct node *temp=head;
    while(temp!=NULL){
        temp->coeff*=temp->index;
        temp->index--;
        temp=temp->next;
    }
    return head;
}

int main(){
    printf("Enter no of terms in 1st polynomial: ");
    int a;
    char s[5];
    scanf("%d",&a);
    struct node *head1;
    head1=(struct node*)malloc(sizeof(struct node));
    printf("Enter coefficient: ");
    scanf("%d",&head1->coeff);
    printf("Enter index: ");
    scanf("%d",&head1->index);
    struct node *temp1;
    temp1=head1;
    if(a==1){
        head1->next=NULL;
    }
    if(a>1){
        for(int i=1;i<a;i++){
        struct node *new=newnode();
        temp1->next=new;
        temp1=temp1->next;
        if(i==a-1)
        temp1->next=NULL;
        }
    }
    head1=reduction(head1);
    head1=sort(head1);
    display(head1);
    printf("Do you want to evaluate? \n");
    scanf("%s",s);
    if(!strcmp(s,"Yes") || !strcmp(s,"yes"))
        Evaluate(head1);

    printf("Enter no of terms in 2nd polynomial: ");
    scanf("%d",&a);
    struct node *head2;
    head2=(struct node*)malloc(sizeof(struct node));
    printf("Enter coefficient: ");
    scanf("%d",&head2->coeff);
    printf("Enter index: ");
    scanf("%d",&head2->index);
    struct node *temp2;
    temp2=head2;
    if(a==1)
    head2->next=NULL;
    else if(a>1){
        for(int i=1;i<a;i++){
        struct node *new=newnode();
        temp2->next=new;
        temp2=temp2->next;
        if(i==a-1)
        temp2->next=NULL;
        }
    }
    head2=reduction(head2);
    head2=sort(head2);
    display(head2);
    printf("Do you want to evaluate? \n");
    scanf("%s",s);
    if(!strcmp(s,"Yes") || !strcmp(s,"yes"))
        Evaluate(head2);

    char str[20];
    while(1){
    printf("Whether you want to add or subtract or multiply or differentiate?\n");
    scanf("%s",str);
    if(!strcmp(str,"Multiplication") || !strcmp(str,"multiplication") || !strcmp(str,"multiply") || !strcmp(str,"Multiply")){
        struct node *multiplyresult=multiply(head1,head2);
        multiplyresult=sort(multiplyresult);
        printf("Multiplication of two polynomials: ");
        display(multiplyresult);
        printf("Do you want to evaluate? \n");
        scanf("%s",s);
        if(!strcmp(s,"Yes") || !strcmp(s,"yes"))
            Evaluate(multiplyresult);
        break;
    }
    else if(!strcmp(str,"Addition") || !strcmp(str,"addition") || !strcmp(str,"add") || !strcmp(str,"Add")){
        struct node *addresult=add(head1,head2);
        addresult=sort(addresult);
        printf("Addition of polynomials: ");
        display(addresult);
        printf("Do you want to evaluate? \n");
        scanf("%s",s);
        if(!strcmp(s,"Yes") || !strcmp(s,"yes"))
            Evaluate(addresult);
        break;
    }
    else if(!strcmp(str,"Subtraction") || !strcmp(str,"subtraction") || !strcmp(str,"Subtract") || !strcmp(str,"subtract")){
        struct node *subresult=Sub(head1,head2);
        subresult=sort(subresult);
        printf("Subtraction of polynomials: ");
        display(subresult);
        printf("Do you want to evaluate? \n");
        scanf("%s",s);
        if(!strcmp(s,"Yes") || !strcmp(s,"yes"))
            Evaluate(subresult);
        break;
    }
    else if(!strcmp(str,"diff")){
        struct node *diff1=differentiation(head1);
        struct node *diff2=differentiation(head2);
        printf("Differentiation of polynomial 1: ");
        display(diff1);
        printf("Differentiation of polynomial 2: ");
        display(diff2);
        break;
    }
    printf("Invalid command.Please enter again\n");
    }
    return 0;
}
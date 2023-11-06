#include<stdio.h>
#include<stdlib.h>
#define maxsize 100

void swap(int *a,int *b){
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}

void check(int arr[],int i,int n){
    if(2*i>n)
        return;
    if(2*i==n && 2*i+1>n){
        if(arr[i]<arr[2*i])
            swap(&arr[i],&arr[2*i]);
        return;
    }
    if(arr[i]<arr[2*i] && arr[2*i]>arr[2*i+1]){
        swap(&arr[i],&arr[2*i]);
        check(arr,2*i,n);
    }
    else if(arr[i]<arr[2*i+1] && arr[2*i+1]>arr[2*i]){
        swap(&arr[i],&arr[2*i+1]);
        check(arr,2*i+1,n);
    }
}

void heapsort(int arr[],int n){
    for(int i=n;i>=1;i--){
        swap(&arr[1],&arr[i]);
        check(arr,1,i-1);
    }
}

void heapify(int arr[],int n){
    int temp;
    if(n%2==0){
        if(arr[n]>arr[n/2])
            swap(&arr[n],&arr[n/2]);
        for(int i=n-1;i>1;i-=2){
            if(arr[i]>arr[i-1]){
                if(arr[i]>arr[i/2])
                    swap(&arr[i],&arr[(i-1)/2]);
                check(arr,i,n); 
            }
            else if(arr[i]<=arr[i-1]){
                if(arr[i-1]>arr[i/2])
                    swap(&arr[i-1],&arr[i/2]);
                check(arr,i-1,n); 
            }
        }
    }
    else if(n%2!=0){
        for(int i=n;i>1;i-=2){
            if(arr[i]>arr[i-1]){
                if(arr[i]>arr[i/2])
                    swap(&arr[i],&arr[(i-1)/2]);
                check(arr,i,n); 
            }
            else if(arr[i]<=arr[i-1]){
                if(arr[i-1]>arr[i/2])
                    swap(&arr[i-1],&arr[i/2]);
                check(arr,i-1,n); 
            }
        }
    }
}

int main(){
    int arr[maxsize];
    int c=0,e;
    arr[0]=0;
    for(int i=1;i<maxsize;i++){
        c++;
        printf("Enter the element: ");
        scanf("%d",&arr[i]);
        printf("Want to exit: ");
        scanf("%d",&e);
        if(e==1)
            break;
    }
    for(int i=c+1;i<maxsize;i++)
        arr[i]=0;
    printf("\n");
    printf("Given binary tree: ");
    for(int i=1;i<c+1;i++)
        printf("%d ",arr[i]);
        printf("\n");
    heapify(arr,c);
    printf("Heap tree of given elements: ");
    for(int i=1;i<c+1;i++)
        printf("%d ",arr[i]);
        printf("\n");
    heapsort(arr,c);
    printf("After heap sort: ");
    for(int i=1;i<c+1;i++)
        printf("%d ",arr[i]);

}
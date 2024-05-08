#include<stdio.h>
#define MAX 100
int count[MAX],time[MAX],inframe[MAX],q[200];
void fifo(int a[],int n,int frames)
{
    int miss=0,i,c=0,j=0;
    for(i=0;i<n;i++){
        if(inframe[a[i]]==0){
            if(c<frames)
            	q[c++]=a[i];
            else
            {
                inframe[q[j]]=0;
                q[j]=a[i];
                j=(j+1)%frames;
            }
            inframe[a[i]]=1;
            miss++;
        }
    }
    printf("Page faults = %d\n",miss);
}
void main() {
	int i,n,a[MAX],frames,ch;
	printf("Enter the number of references in reference string :");
	scanf("%d",&n);
	for(i=0;i<n;i++)
		scanf("%d",&a[i]);
	printf("Enter the number of frames :");
	scanf("%d",&frames);
    for(i=0;i<n;i++)
    {   
        count[a[i]]=0;
        time[a[i]]=0;
        inframe[a[i]]=0;
    }
    printf("FIFO \n");
    fifo(a,n,frames);
}
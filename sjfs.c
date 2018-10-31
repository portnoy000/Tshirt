//#define TASKN 10
//#define AT 10
//#define ET 10
//#include<stdlib.h>
//#include<stdio.h>
#include<time.h>
#include"display.c"
int ptr=0,sum=0;
//tejkhg
double display[100][2];
int pos;

void swap(double *a,double *b){
	*a=*a+*b;
	*b=*a-*b;
	*a=*a-*b;
}
//
int check(double data[TASKN]){
	int i,count=0;
	for(i=0;i<TASKN;i++)
		if(data[i]==2)
			count++;

	if(count==TASKN-1)
	return 0;
	else return 1;

	}

int next_0(double data[TASKN]){
	int i;
	for(i=0;i<TASKN;i++)
		if(data[i]==0)
		return i;
	return -1;
	}

int find(double data[][TASKN],int num,int i,int end){
	int j;
	for(j=0;j<end;j++)
		if(num==data[i][j])
			return 1;
	return 0;
      }	

void set_mode_1(double data[][TASKN],double time){
	int i=0;
	for(i=0;i<TASKN;i++)
		if(data[2][i]<=time&&data[3][i]!=2)
			data[3][i]=1;
	}

void set_mode_2(double data[][TASKN],double *time,int exe_order[TASKN]){
int i=0,index=-1;double min=-1;
	for(i=0;i<TASKN;i++){
		if(data[3][i]==1){
			if(index==-1){index=i;min=data[1][i];}
			else if(data[1][i]<min){index=i;min=data[1][i];}
		}
	}
	if(index!=-1){
	display[pos][1]=data[0][index];
	display[pos++][0]=*time;
	*time+=min;	
	data[3][index]=2;
	exe_order[ptr++]=data[0][index];
	}
	else{
	int j;
	for(j=0;j<TASKN;j++){int k=data[3][j];
		if(k==0)
			break;}
	//printf("0 at %d",j);
	display[pos][1]=data[0][j];
	display[pos++][0]=*time;
	min=data[1][j];
	*time+=min;
	data[3][j]=2;
	exe_order[ptr++]=data[0][j];

	}
    }


void sort(double data[][TASKN]){
int i,j;
for(i=0;i<TASKN-1;i++)
	for(j=0;j<TASKN-i-1;j++)
		if(data[2][j]>data[2][j+1]){
				  swap(&data[0][j],&data[0][j+1]);
			          swap(&data[1][j],&data[1][j+1]);
		                  swap(&data[2][j],&data[2][j+1]);
					}
	}



void sjfs(){
	double data[4][TASKN];
	int i,num,exe_order[TASKN];
	
	for(i=0;i<TASKN;i++){		//task id generation
	num=rand()%TASKN;
	while(find(data,num,0,i)){
	num=rand()%TASKN;
	}
	data[0][i]=num;

	}
					//exc time generation
	for(i=0;i<TASKN;i++){
	data[1][i]=(rand()%(ET*100))*0.01;

	}

					//arrival time
	for(int i=0;i<TASKN;i++)
	data[2][i]=(rand()%(AT*100))*0.01;

						//data[3][i]  = 0-not eligible
						//1-eligible
						//2-completed

	printf("GENERATED INPUTS\n");
	printf("Task ID\tEXEXUTION TIME\t ARRIVAL TIME\n");
	for(i=0;i<TASKN;i++)
	      printf("%0.0f\t%.2f\t\t%0.2f\n",data[0][i],data[1][i],data[2][i]);

	sort(data);
	double time=0;
	time=data[2][0];

	while(check(data[3])){
	set_mode_1(data,time);
	set_mode_2(data,&time,exe_order);
	}
	
	printf("OUTPUT\n");
	printf("Task ID\tEXEXUTION TIME\t ARRIVAL TIME\n");
	for(i=0;i<TASKN;i++)
	      printf("%0.0f\t%.2f\t\t%0.2f\n",data[0][i],data[1][i],data[2][i]);

	for(i=0;i<TASKN-1;i++){
		printf("-->%d",exe_order[i]);
		sum+=exe_order[i];
		}
	printf("-->%d\n",(TASKN*(TASKN-1))/2-sum);
	display[pos][1]=(TASKN*(TASKN-1))/2-sum;
	display[pos++][0]=time;
	display[pos][0]=100;
graph(display,pos);
	
}

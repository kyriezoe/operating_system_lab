#include<stdio.h>
#include<string.h>
#include<malloc.h>
typedef struct Proc{
	char name[2];
	int time;
	int priority;
	char state;
	struct Proc *next;
}Proc;
Proc *head=NULL;
void Disp(Proc *p){
	Proc *q;
	printf("c  t  s   p\n");
	printf("%s  %d  %c   %d\n",p->name,p->time-1,p->state,p->priority);
	printf("\n");
	q=head;
	while(q!=NULL)
	{
	printf("%s  %d  %c   %d\n",q->name,q->time,q->state,q->priority);
		q=q->next;
	}
	printf("\n");
	printf("\n");
}
void InsertPrio(Proc *p){    //priority queue
	Proc *m,*q;   
	m = q = head;  
	int flag=0;
    if(head == NULL){   
		p->next = head;   
		head= p;  
		p->next =NULL;
	}   
	else{    
	   if(p->priority >= m->priority) {   
			p->next = head;   
			head= p;  
		}   
		else{   
			while(m->next != NULL){   
				q = m;   
				m = m->next; 
				if(p->priority>=m->priority){
					q ->next= p;   
					p ->next = m;
					flag=1;
				} 
				if(flag==1)
				{
					break;
				}
			}
			if(m->next == NULL&&flag==0) 
			{
				p ->next = m ->next;   
				m->next=p;   
			} 	
		} 
	}	  
}   
void creat(){
	int i;
    for(i=0;i<5;i++){
		Proc *p;
    	int time,priority;
    	char name[2];
		p=(Proc *)malloc(sizeof(Proc));
		printf("enter proc name£º\n");
		scanf("%s",name);
		printf("enter needed time£º\n");
		scanf("%d",&time);
		printf("enter priority£º\n");
		scanf("%d",&priority);
		strcpy(p->name,name);
		p->time=time;
		p->priority=priority;
		p->state='R';
		p->next =NULL;	
		InsertPrio(p);	
	}
	printf("\n\n\n"); 
    printf("**************************************************\n");  
	printf("                 processing info                  \n"); 
	printf("            c means chosen process                \n");   
	printf("               t means time needed                   \n"); 
	printf("                  s means state                         \n"); 
	printf("                p means priority                      \n"); 
	printf("**************************************************\n");
}
void run(){
	Proc *p;
	p=head;
	head=head->next;
	Disp(p);
	p->priority=p->priority-1;
	p->time=p->time-1;
	if(p->time<=0){
		p->state='E';
		printf("proc %s exit£¬state£º%c\n",p->name,p->state);
	}
	else{
		InsertPrio(p);
	}
}
void work(){
	while(head!=NULL)
	{
		run();
	}
	free(head);}
int main(){
	  creat();
	  work();
	  system("pause"); 
	  return 0;
}

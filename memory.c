#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
const int CANUSE = 1;
const int CANTUSE = 0;
const int MSIZE = 128;

struct MZone
{
    int begin_addr; 
    int length;       
    int state;
    char task_name[32];    
    struct MZone *next;    
};

struct MZone * Mhead = NULL;

//display memory allocation
void showmemory()
{
     struct MZone *Mpoint = Mhead;
     
     printf("memory allocation\n");
     printf("beginaddr\tlength\tstate\t  task\n"); 
     
     while( NULL!=Mpoint)
     {
         printf("%dk\t\t",Mpoint->begin_addr);
         printf("%dk\t",Mpoint->length);
         Mpoint->state?printf("CAN_USE\t"):printf("CANNOT_USE\t");
         printf("%s\n",Mpoint->task_name);
         Mpoint = Mpoint->next;
     } 
    system("pause");
     
}

//insert task into memory
int Minsert(struct MZone* Mnew)
{
     struct MZone *Zinsert = Mhead;
     //flag indicates that if Zinsert comes to NULL£¬no memory to allot 
     int flag = 1;   
     while( Zinsert->length<Mnew->length || !Zinsert->state)
     {
             if( NULL!=Zinsert->next )
             {
                Zinsert = Zinsert->next;
             }
             else
             {   
                 Zinsert = Zinsert->next;
                 break;
             }   
     }
     if( NULL==Zinsert ) 
     {
         return 0;
     }
     if( MSIZE == Zinsert->begin_addr+Mnew->length )
     {
          Zinsert->state = CANTUSE;
          strcpy(Zinsert->task_name , Mnew->task_name);
          Zinsert->next = NULL;
          return 1;
     }
     else
     {
         struct MZone *Ztail = (struct MZone *)malloc(sizeof(struct MZone));
         Zinsert->state = CANTUSE;
         strcpy(Zinsert->task_name , Mnew->task_name);
         Zinsert->length = Mnew->length;
         Zinsert->next = Ztail;
         
         memset( Ztail, 0, sizeof(char)*32 );
         Ztail->begin_addr = Zinsert->begin_addr + Mnew->length;
         Ztail->state = CANUSE;
         Ztail->length = MSIZE - Ztail->begin_addr;
         Ztail->next = NULL;
         
         return 1;
     }
}


//allot memory
void memoallocate(void)
{
     struct MZone *Mnew = (struct MZone*)malloc(sizeof(struct MZone));
     printf("enter memory needed(kb):\n");
     scanf("%d",&Mnew->length);
     printf("enter taskname:\n");
     scanf("%s",&Mnew->task_name);
     Minsert(Mnew)?printf("allot successful\n"):printf("allot failed\n"); 
     system("pause");
     free(Mnew);
}

//recycle memory
int Mreturn(char taskname[])
{
    struct MZone *front = NULL;
    struct MZone *position = Mhead;
    struct MZone *tail = Mhead->next;
    
    while( 0!=strcmp(position->task_name,taskname) ) 
    {
           front = position;
           if( NULL!=position->next )
           {
               position = position->next;
           }
           else
           {
               position = NULL;
               break;
           }
           tail = position->next;
    }
    if( NULL==position )
    {
        printf("No such task in memory");   
    }
    else
    {
      //CANNOTUSE 
      if( NULL!=tail&&NULL!=front )
       {
    
            if( front->state&&tail->state )
            {
                front->length = front->length + position->length + tail->length;
                front->next = tail->next;
                free(position);
                free(tail);
            }
            else if( front->state&&!tail->state )
            {
                front->length = front->length + position->length;
                front->next = position->next;
                free(position);
            }
            else if( !front->state&&tail->state )
            {
                position->length = position->length + tail->length;
                memset( position->task_name, 0, sizeof(char)*32 );
                position->next = tail->next;
                position->state = CANUSE;
                free(tail);
            }
            else if( !front->state&&!tail->state )
            {
                memset( position->task_name, 0, sizeof(char)*32 );
                position->state = CANUSE;   
            }
       }
       else if( NULL!=tail&&NULL==front )
       {
         if( !tail->state )
          {
             memset( position->task_name, 0, sizeof(char)*32 );
             position->state = CANUSE;
          }
          else
          {
             position->length = position->length + tail->length;
             position->next = NULL;
             free(tail);
          }
       } 
       else if( NULL==tail&&NULL!=front )
       {
         if(front->state)
          { 
              front->length = front->length + position->length;
              front->next = NULL;
              free(position);
          }
          else
          {
              memset( position->task_name, 0, sizeof(char)*32 );
              position->state = CANUSE;
          }
       }
       else if( NULL==tail&&NULL==front )
       {
            memset( position->task_name, 0, sizeof(char)*32 );
            position->state = CANUSE; 
       }
    printf("recycle successful\n");
   }
	return 0;
}
void memoreturn(void)
{
     char tname[32];
     printf("enter taskname to be recycled\n");
     scanf("%s",tname);
     Mreturn(tname); 
     system("pause"); 
} 

int main(void)
{
     int func_ = 0;
     Mhead = (struct MZone*)malloc(sizeof(struct MZone));
     Mhead->begin_addr = 0;
     Mhead->length = MSIZE;
     Mhead->state = CANUSE;
     memset(Mhead->task_name, 0, sizeof(char)*32 );
     Mhead->next = NULL;
     while( 1 )
     {
           printf("******************FF algorithm to implement memory allocation and recycle***************\n");
           printf("|1:check memory allocation\n");
           printf("|2:ask for memory allot\n");
           printf("|3:ask for memory recycle\n");
           printf("|4:exit\n");
           printf("********************************************************************************");
           scanf("%d",&func_);
           switch( func_ )
           {
                   case 1 :showmemory();break;
                   case 2 :memoallocate();break;
                   case 3 :memoreturn();break; 
                   case 4 :return 1;
           }
           system("cls");
     }       
}

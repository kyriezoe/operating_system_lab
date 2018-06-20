#include <stdio.h>
#include <stdlib.h>
#define NUM 128
typedef struct                    
{   int zm_no;              
    int cd_no;              
    int jl_no;             
}disk;

void disp(int m[])
{
     int i;
     printf("bitmap£º\n"); 
     for(i=0;i<NUM;i++)
        {if(i%8==0)
            printf("\n");
            printf("%d\t",m[i]);
        }
	printf("\n");
}
     
void creat(int m[])
{   int j=0; 
    int usable=0;
    while(j<NUM)
    {   if(m[j]==0)
        {   usable=1;                        
            m[j]=1;                        
            disk a;
            a.zm_no=j/8;
            a.cd_no=(j%8)/4;
            a.jl_no=(j%8)%4;
            printf("zm\tcd\tjl\n");
            printf("%d\t%d\t%d\n",a.zm_no,a.cd_no,a.jl_no);
            break;
        }
        else j++;
    }
    if(usable==0)                            
    {   printf("No space!\n");
        printf("\n");
    }
}
     
void del(int m[])
{   disk b;
    int zm_no,cd_no,jl_no,j;
    printf("enter zm, cd, jl number£º");
    scanf("%d%d%d",&b.zm_no,&b.cd_no,&b.jl_no);
    j=8*b.zm_no+4*b.cd_no+b.jl_no;    
    if(m[j]==0)
        printf("Already empty£¡\n");
    else
    {   m[j]=0;
        disp(m);
    }    
}

int main()
{
    int i; 
    int input=1;
    int m[NUM]={     0,0,1,0,0,0,0,0,           
                     0,0,0,0,0,0,0,0,
                     0,0,0,0,0,1,1,1,
                     1,1,0,0,0,0,0,0,
                     0,0,0,0,0,0,0,0,
                     0,0,0,0,1,1,1,1,
                     0,0,0,0,0,0,0,0,
                     0,0,0,0,0,1,1,1,
                     0,0,1,0,0,0,0,0,           
                     0,0,0,0,0,0,0,0,
                     0,0,0,0,1,1,1,0,
                     1,1,0,0,0,0,0,0,
                     0,0,0,0,0,0,0,0,
                     0,0,0,0,0,1,1,1,
                     0,0,0,0,0,0,0,0,
                     0,0,0,0,0,0,1,1};
                     
    while(input!=0)
    {   printf("Disk allocation and recycle using bitmap\n"); 
	    printf("1.current state 2.apply 3.recycle 0.exit\n");
        scanf("%d",&input);
        switch(input)
        {   case 1: disp(m);break;
            case 2: creat(m);break;
            case 3: del(m);break;
            default:break;
        }
    }
    system("pause");
}

#include<stdio.h>
#include<stdlib.h>

#define NEW 0
#define READY 1
#define WAITING 2
#define RUNNING 3
#define EXIT 4
#define SRT 0
#define RR 1

int nowtime=0,time_since_last_ct=0,ALLEXIT=0,CT=1,n,CURRMODE=RR,ALREADYRUNNING=0,TimeQuantum,i,j;
struct Process_Struct 
{
	int pid;
	int state;
	int timeleft;
	int at;
	int wt,tat,ct,exect,qno;
	struct Process_Struct *prev;
	struct Process_Struct *next;
} *pa;
struct Queue
{
	struct Process_Struct *front ,*rear;
}*ReadyQueue1,*ReadyQueue2;

void enqueuep(struct Process_Struct *p)
{
	if(ReadyQueue1->front==NULL)
	{
		ReadyQueue1->front=p;
		ReadyQueue1->rear=p;
		p->next=NULL;
	}
        
	else
	{
		if(p->timeleft<ReadyQueue1->front->timeleft)
		{
			p->next=ReadyQueue1->front;
			ReadyQueue1->front->prev=p;
			ReadyQueue1->front=p;
		}
               else if(p->timeleft==ReadyQueue1->front->timeleft)
		{
			p->next=ReadyQueue1->front->next;
			p->prev=ReadyQueue1->front;
			ReadyQueue1->front->next=p;
                        if(p->next!=NULL)
                      {
                        p->next->prev=p;
		      }
                }
		else if(p->timeleft>ReadyQueue1->rear->timeleft)
		{
			p->next=NULL;
			ReadyQueue1->rear->next=p;
			p->prev=ReadyQueue1->rear;
			ReadyQueue1->rear=p;
		}
		else
		{
                   struct Process_Struct *start=ReadyQueue1->front->next;
		   while(start->timeleft<p->timeleft)
		   {
			   start=start->next;
		   }
                   if(start!=NULL&& p->timeleft==start->timeleft)
                   {
                          p->next=start->next;
                          start->next=p;
                          p->prev=start;
                      
                   }
                  else
               {
		   (start->prev)->next=p;
		   p->next=start;
		   p->prev=start->prev;
		   start->prev=p;
                }

		}
	}
}
struct Process_Struct *  deQueuep()
{
     if(ReadyQueue1->front==NULL)
     {
	     return NULL;
     }
     struct Process_Struct * temp=ReadyQueue1->front;
     ReadyQueue1->front=ReadyQueue1->front->next;
     temp->next=NULL;
     if(ReadyQueue1->front==NULL)
     {
	     ReadyQueue1->rear=NULL;
     }
     return temp;
}

void enqueue(struct Process_Struct *p)
{
      if(ReadyQueue2->front==NULL)
      { 
         p->prev=NULL;

         p->next=NULL;
         ReadyQueue2->front=p;           
         ReadyQueue2->rear=p;
         return;
      }
     p->prev=ReadyQueue2->rear;
     ReadyQueue2->rear->next=p;
     ReadyQueue2->rear=p;
}
struct Process_Struct * deQueue()
{
if(ReadyQueue2->front==NULL)
     {
	     return NULL;
     }
     struct Process_Struct * temp=ReadyQueue2->front;
     ReadyQueue2->front=ReadyQueue2->front->next;
     temp->next=NULL;
     if(ReadyQueue2->front==NULL)
     {
	     ReadyQueue2->rear=NULL;
     }
     return temp;
}
void updateQueue()
{
           int count=0;
           for(i=0;i<n;i++)
	   {
                   
		   if(pa[i].state == NEW && nowtime>=pa[i].at)
		   {      
			   if(pa[i].qno==1)
                           {
			       enqueuep(&pa[i]);
			       pa[i].state=READY;
			   }
                           else if(pa[i].qno==2)
                          {
                                enqueue(&pa[i]);
                                pa[i].state=READY;
                          }
                    }
                  if(pa[i].state==EXIT)
                  {
                    count++;
			}
	   }
	   if(count==n)
	   {
		  ALLEXIT=1; 
		  
	   }
}
int main()
{
        ReadyQueue1 =(struct Queue*) malloc(sizeof(struct Queue));
        ReadyQueue2 =(struct Queue*) malloc(sizeof(struct Queue));
	printf("\t\tPlease enter No of Persons =>");
	scanf("%d",&n);
	pa=(struct Process_Struct *)malloc(sizeof(struct Process_Struct)*n);
	for(i=0;i<n;i++)
	{
             printf("\n\n\t\tEnter Person Id For %d Person =>",(i+1));
	     scanf("%d",&(pa[i].pid));
	     printf("\n\t\tEnter arrival time For %d Person  =>",(i+1));
	     scanf("%d",&(pa[i].at));
	    
	     pa[i].timeleft=1; 

	     printf("\n\t\tEnter Type For %d Person--[1] Teacher [2] Student =>",(i+1));
	     scanf("%d",&(pa[i].qno)); 
           
             pa[i].exect=pa[i].timeleft;
	    pa[i].state=NEW;
	        
	}
           struct Process_Struct key; 
   
    for (i = 1; i < n; i++) { 
        key = pa[i]; 
        j = i - 1; 
  
        while (j >= 0 && pa[j].at > key.at) { 
            pa[j + 1] = pa[j]; 
            j = j - 1; 
        } 
        pa[j + 1] = key; 
    } 
       
        struct Process_Struct *pr=NULL;
	struct Process_Struct *prev;
      printf("\nGannt Chart :::::::::::::::::\n--------------------------------------------------------------------------------------------------------------------------------------------------\n");
       while(1)
       {
            updateQueue();
            if(ALLEXIT)
            {
                  break;
            }
           if(ReadyQueue1->front!=NULL &&  ALREADYRUNNING==0)
           {
                    if(pr!=NULL && pr->qno==2)
                    {
                        enqueue(pr);
                        pr->state=READY;
                        pr=NULL;
                     }
                      
		    CURRMODE=SRT;
                     time_since_last_ct=1;
		     prev=pr;
	     	     pr=deQueuep();
		     if(prev!=pr)
		     {
			     printf("%d | Person%d [Teacher]|",nowtime,pr->pid);
		     }
             	     pr->state=RUNNING;
             	     pr->timeleft--;
	             nowtime++;
                    if(time_since_last_ct==pr->exect)
                    {
                  	CT=1;
                        ALREADYRUNNING =0;
                  	pr->state=EXIT;
                  	pr->ct=nowtime;
                  	pr->tat=nowtime-pr->at;
                        pr->wt=pr->tat-pr->exect;
                        pr=NULL;
           
                    }
                    else
                    {
                       CT=0;
                       ALREADYRUNNING=1;
                     }
            }
          else if(ReadyQueue2->front!=NULL&& ReadyQueue1->front==NULL && pr==NULL && CT==1)
         {
                     CURRMODE=RR;
                     time_since_last_ct=1;
		     prev=pr;
	     	     pr=deQueue();
             	     if(prev!=pr)
		     {
			     printf("%d | Person%d [Student]|",nowtime,pr->pid);
		     }
             	      pr->state=RUNNING;
             	     pr->timeleft--;
	             nowtime++;
                    if(time_since_last_ct==pr->exect)
                    {
                  	CT=1;
                  	pr->state=EXIT;
                  	pr->ct=nowtime;
                  	pr->tat=nowtime-pr->at;
                        pr->wt=pr->tat-pr->exect;
                        pr=NULL;
           
                    }
                    else
                    {
                       CT=0;
                     }                 
         }
         else if(pr!=NULL && pr->qno==1 && CT==0&&pr->state==RUNNING)
         {
                  
                     if(pr->timeleft==0)
             {
                  CT=1;
                  ALREADYRUNNING=0;
                  pr->state=EXIT;
                  pr->ct=nowtime;
                  pr->tat=nowtime-(pr->at);
                  pr->wt=(pr->tat)-(pr->exect);
                  pr=NULL;
                  continue;
             }  
         
		if(ReadyQueue1->front!=NULL)
             {
               if(pr->timeleft>ReadyQueue1->front->timeleft)
               {
                pr->state=READY;
                enqueuep(pr);
                ALREADYRUNNING=0;
                pr=NULL;
                CT=1;
               continue;
               }
             }    
             time_since_last_ct++;
             pr->timeleft--;
            nowtime++;

             if(pr->timeleft==0)
             {
                  CT=1;
                  ALREADYRUNNING=0;
                  pr->state=EXIT;
                  pr->ct=nowtime;
                  pr->tat=nowtime-(pr->at);
                  pr->wt=(pr->tat)-(pr->exect);
                  pr=NULL;
             }            
             else if(ReadyQueue1->front!=NULL)
             {
               if(pr->timeleft>ReadyQueue1->front->timeleft)
               {
                pr->state=READY;
                enqueuep(pr);
                ALREADYRUNNING=0;
                pr=NULL;
                CT=1;
               }
               else
               {
                  CT=0;
                 ALREADYRUNNING=1;
               }
              }
            else
          { 
              CT=0;
             ALREADYRUNNING=1;
	  }            
         }
         else if(pr!=NULL && pr->qno==2&& pr->state==RUNNING && CT==0)
         {
               if(pr->timeleft==0)
             {
                  CT=1;
                  pr->state=EXIT;
                  pr->ct=nowtime;
                  pr->tat=nowtime-(pr->at);
                  pr->wt=(pr->tat)-(pr->exect);
		  pr=NULL;
                  continue;
             }      
             time_since_last_ct++;
             pr->timeleft--;
            nowtime++;

             if(pr->timeleft==0)
             {
                  CT=1;
                  pr->state=EXIT;
                  pr->ct=nowtime;
                  pr->tat=nowtime-(pr->at);
                  pr->wt=(pr->tat)-(pr->exect);
	 	  pr=NULL;
             }            
             
            else
          { 
              CT=0;
	  }
         }
        else
        {
         printf("%d | IDLE |",nowtime);
          nowtime++;

         }
                 
       }
       printf("%d\n",nowtime);
       printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
      int sumwt=0,sumtat=0;
printf("\n\n\tPID\t\tAT\t\tbt\t\tCT\t\tTAT\t\tWT\t\t[1] Teacher [2] Student\n");
printf("==========================================================================================================================\n");
for(i=0;i<n;i++)
	{
           printf("\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",pa[i].pid,pa[i].at,pa[i].exect,pa[i].ct,pa[i].tat,pa[i].wt,pa[i].qno);
           sumwt+=pa[i].wt;
           sumtat+=pa[i].tat;
           
	}
printf("\n\n Avergae TAT=%f \n Average WT=%f\n",(sumtat/(n*1.0)),(sumwt/(n*1.0)));
}


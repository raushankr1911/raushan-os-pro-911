#include<stdio.h>
struct Student
{
 	int pen ;
	int paper ;
	int question_paper ;
	int completed ;
};
int main()
{
	int n=3;
	struct Student  s[n];
	s[0].pen=1;		
	s[0].paper = 0;
	s[0].question_paper = 0;
	s[0].completed= 0;
	s[1].pen=0;		
	s[1].paper = 1;
	s[1].question_paper = 0;
	s[1].completed = 0;
	s[2].pen=0;		
	s[2].paper = 0;
	s[2].question_paper = 1;
	s[2].completed = 0	;
	while(s[0].completed==0||s[1].completed==0||s[2].completed==0)
	{
		int ch1,ch2;
		printf("\nResources:\n1.pen\n2.paper\n3.question paper\n Enter the two things which is to be placed on the shared table: ");
		scanf("%d%d",&ch1,&ch2);
		if(ch1==1 && ch2==2 && s[2].completed==0)
		{
			s[2].completed=1 ;
			printf("Third Student has completed the task\n");
		}
		if(ch1==2 && ch2==3 && s[0].completed==0)
		{
			s[0].completed=1;
			printf("First Student has completed the task\n");
		}
		if(ch1==1 && ch2==3 && s[1].completed==0)
		{
			s[1].completed=1;
			printf("Second Student has completed the task\n");
		}
	}
	printf("All the students now have completed their respective tasks succesfully\n");
	return 0;
}

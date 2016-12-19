#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<signal.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#define SNOOZE 10
using namespace std;
void playalrm (int);
void snooze (int);
void totalexit (int);
void itsok (int);
int
main (int argc, char **argv)
{


  int pid = fork ();
  if (pid > 0)
    {
      //signal (SIGQUIT, totalexit);
      signal (SIGINT, itsok);
      int *status;
      if (argc != 2)
	{
	  cout << "usage...<./alarm> <time hr:min:sec>\n";
	  // cout<<"<./alarm> t <timer_seconds>\n";
	  kill (pid, SIGQUIT);
	  exit (0);
	}
	
      char *p;
      int i, alarm = 0, msg = 0;
      char r = '\0';
     char greeting[25]= {'\0'};
      time_t timv = time (0);
      p = ctime (&timv);
      r = *(p + 18);
     /* int message = (argv[1][1]-'0')*10 +(argv[1][0]-'0');
     if(message < 12 && message >= 0)
        strcpy(greeting,"good morning");
  else if(message >=12 && message < 16)
        strcpy(greeting,"good afternoon");
else if(message >= 16 && message < 21)
        strcpy(greeting,"good evening");*/
//(message >= 21 && message < 23)
        strcpy(greeting,"have a nice day..!!");
      while (1)
	{
	  timv = time (0);
	  p = ctime (&timv);

	  if (*(p + 18) != r)
	    {
	      system ("clear");
	      cout << "\ntime = ";

	      for (i = 0; i < 8; i++)
		cout << *(p + i + 11);
	      cout << endl;
	      cout << "settime = " << argv[1] << endl;
	      if (msg)
		{cout << "\n\t\tpress CTRL-C to SNOOZE;CTRL-\\ to STOP\n";
			cout<<"\t\t"<<greeting<<endl;}
	      r = *(p + 18);
	      for (i = 0; i < 8; i++)
		{
		  if (*(p + i + 11) == argv[1][i])
		    alarm = 1;
		  else
		    {
		      alarm = 0;
		      break;
		    }
		}
	      if (alarm)
		{
		  msg = 1;
		  kill (pid, 30);

		}




	    }


	}
// wait(&status);
      printf ("print something\n");
    }
  else
    {
      signal (SIGQUIT, totalexit);
      signal (SIGINT, snooze);
      signal (30, playalrm);
      signal (SIGALRM, playalrm);

      for (;;);
    }

}

void
playalrm (int i)
{

  system ("cvlc 3.mp3 --repeat");
  kill (getpid (), SIGINT);
}

void
snooze (int i)
{


  printf ("received ctrl-c\n");

  sleep (SNOOZE);
  if (getppid () == 1){//system("banner THANK YOU");
    exit (0);}
  kill (getpid (), SIGALRM);
}

void
itsok (int i)
{
  printf ("received ctrl-c\n");
}

void
totalexit (int i)
{
  system("banner THANK YOU");
  exit (0);
}

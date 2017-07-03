/* ctime example */
#include <stdio.h>      /* printf */
#include <time.h>       /* time_t, time, ctime */
#include <iostream>

#define LIMA (+19)
using namespace std;
int main ()
{
  time_t rawtime;
  struct tm * ptm;

  time ( &rawtime );

  ptm = gmtime ( &rawtime );

  puts ("Current time around the World:");
  printf ("Lima :  %2d:%02d\n", (ptm->tm_hour+LIMA)%24, ptm->tm_min);
  int hr=((ptm->tm_hour+LIMA)%24)*100+ptm->tm_min;
  cout<<hr;
  return 0;
}
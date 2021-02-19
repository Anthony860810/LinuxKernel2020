#include <stdio.h>
#include <string.h>
#include <linux/kernel.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#if __GLIBC__ == 2 && __GLIBC_MINOR__ < 30
#define gettid() syscall(SYS_gettid) // workaround for glibc older than 2.30
#endif

void main() {
  int random_num;
  int ttid, count;
  char str[300];
  char filename[64];

  if(system("pidof -x ./enter_queue > /dev/null") != 0) {
    sleep(20);
  }

  struct timeval t1, t2;
  gettimeofday(&t1, NULL);
  ttid = gettid();
  count = 0;

  srand( time(NULL) );
  FILE *out;
  sprintf(filename, "file_%d.txt", ttid);
  out = fopen(filename, "w");

  printf("pid is %d\n", getpid());
  while(1) {
    gettimeofday(&t2, NULL);

    if( t2.tv_sec - t1.tv_sec >= 180 ){
      break;
    }
    else {
      random_num = (rand()%3) + 1;

      sprintf(str, "process %d is added into wait queue project2_queue_%d the %d th time at time %ld\n", ttid, random_num, count++, t2.tv_sec);
      fwrite(str, 1, strlen(str) + 1, out);

      syscall(351, random_num);
    }

  }
  fclose(out);
  printf("process %d completes!\n", ttid);
}
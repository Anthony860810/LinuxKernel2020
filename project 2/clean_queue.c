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
  int random_num1, random_num2;
  int ttid, count;
  char str[300];

  srand( time(NULL) );
  sleep(10);
  struct timeval t1, t2;
  gettimeofday(&t1, NULL);
  ttid=gettid();
  count = 0;

  char filename[64];

  FILE *out;
  sprintf(filename, "file_%d.txt", ttid);
  out = fopen(filename, "w");

  printf("pid is %d\n", getpid());
  while(1) {
    gettimeofday(&t2, NULL);

    if( t2.tv_sec - t1.tv_sec > 300 ){
      break;
    }
    else {
      random_num1 = (rand()%3) + 1;
      random_num2 = (rand()%60);
      sleep(random_num2);

      sprintf(str, "Wake up all processes in wait queue project2_queue_%d at time %ld\n", random_num1, t2.tv_sec);
      fwrite(str, 1, strlen(str) + 1, out);


      syscall(352, random_num1);
    }
  }

  syscall(352, 1);
  sprintf(str, "Wake up all processes in wait queue project2_queue_1 at time %ld\n", t2.tv_sec);
  fwrite(str, 1, strlen(str) + 1, out);
  
  syscall(352, 2);
  sprintf(str, "Wake up all processes in wait queue project2_queue_2 at time %ld\n", t2.tv_sec);
  fwrite(str, 1, strlen(str) + 1, out);

  syscall(352, 3);
  sprintf(str, "Wake up all processes in wait queue project2_queue_3 at time %ld\n", t2.tv_sec);
  fwrite(str, 1, strlen(str) + 1, out);

  fclose(out);
  printf("process %d completes!\n", ttid);
}
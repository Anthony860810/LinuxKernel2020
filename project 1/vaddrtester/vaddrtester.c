#include <stdio.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <linux/kernel.h>
#include <unistd.h>
#include <stdlib.h>

int main () {
  // struct pid *pid = getpid()
  long int result = syscall(352, getpid());
  printf("System call vaddr2paddr returned %ld\n", result);
  return 0;
}
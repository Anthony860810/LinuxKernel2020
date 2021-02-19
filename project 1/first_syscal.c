#include <linux/kernel.h>

asmlinkage long sys_hello(void){
  printk("The winter is coming\n");
  return 0;
}
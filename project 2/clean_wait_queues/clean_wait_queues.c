#include <linux/linkage.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/time.h>
#include <linux/delay.h>
#include <linux/workqueue.h>

extern wait_queue_head_t project2_queue_1;
extern wait_queue_head_t project2_queue_2;
extern wait_queue_head_t project2_queue_3;

asmlinkage void sys_clean_wait_queues(int x) {
  switch (x)
  {
  case 1:
    printk("wake up process in queue 1\n");
    wake_up_interruptible(&project2_queue_1);
    break;

  case 2:
    printk("wake up process in queue 2\n");
    wake_up_interruptible(&project2_queue_2);
    break;

  case 3:
    printk("wake up process in queue 3\n");
    wake_up_interruptible(&project2_queue_3);
    break;
  
  default:
    printk("Failed to wake up\n");
    break;
  }
}
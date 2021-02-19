#include <linux/linkage.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/time.h>
#include <linux/delay.h>
#include <linux/workqueue.h>

wait_queue_head_t project2_queue_1 = __WAIT_QUEUE_HEAD_INITIALIZER(project2_queue_1);
wait_queue_head_t project2_queue_2 = __WAIT_QUEUE_HEAD_INITIALIZER(project2_queue_2);
wait_queue_head_t project2_queue_3 = __WAIT_QUEUE_HEAD_INITIALIZER(project2_queue_3);

asmlinkage void sys_enter_wait_queue(int x) {

  switch (x)
  {
  case 1:
    printk("wait queue 1 address at %p\n", &project2_queue_1);
    interruptible_sleep_on(&project2_queue_1);
    break;

  case 2:
    printk("wait queue 2 address at %p\n", &project2_queue_2);
    interruptible_sleep_on(&project2_queue_2);
    break;

  case 3:
    printk("wait queue 3 address at %p\n", &project2_queue_3);
    interruptible_sleep_on(&project2_queue_3);
    break;

  default:
    printk("Failed\n");
    break;
  }

}
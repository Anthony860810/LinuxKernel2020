#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/moduleparam.h>

MODULE_LICENSE("GPL");

static char *ptr;
int alloc_size = 1024;

module_param(alloc_size, int, 0);

static int test_hello_init(void)
{
    ptr = kmalloc(alloc_size,GFP_ATOMIC);
    if(!ptr) {
        /* handle error */
        pr_err("memory allocation failed\n");
        return -ENOMEM;
    } else {
        printk("Memory allocated successfully:%px\t%px\n", ptr, ptr+100);
        printk("Physical address:%llx\t %llx\n", virt_to_phys(ptr), virt_to_phys(ptr+100));
    }

    return 0;
}

static void test_hello_exit(void)
{
    kfree(ptr);
    pr_info("Memory freed\n");

}
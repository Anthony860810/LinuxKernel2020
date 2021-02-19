#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/mm.h>
#include <linux/mm_types.h>
#include <linux/sched.h>
#include <linux/export.h>
#include <linux/highmem.h>
#include <asm/fixmap.h>

static unsigned long vaddr = 0;

int vaddr2paddr (unsigned long vaddr) {
  
  struct task_struct *task;

  for_each_process (task) {
    
    pgd_t *pgd;
    pmd_t *pmd;
    pte_t *pte;
    unsigned long paddr = 0;
    unsigned long page_addr = 0;
    unsigned long page_offset = 0;
    
    printk("PID is %d\n", task->pid);

    if (task->mm != NULL)
    {

      pgd = pgd_offset(task->mm, vaddr);
      printk("pgd_val = 0x %lx, pgd_offset = %lx \n", pgd_val(*pgd), pgd);

      if (pgd_none(*pgd))
      {
        printk("not mapped in pgd\n");
        //return -1;
      }
      else
      {
        pmd = pmd_offset(pgd, vaddr);
        // printk("pmd_val = 0x %lx, pmd_offset = %lx \n", pmd_val(*pmd), pmd);
        if (pmd_none(*pmd))
        {
          printk("not mapped in pmd\n");
          //return -1;
        }
        else
        {
          pte = pte_offset_kernel(pmd, vaddr);
          // printk("pte_val = 0x %lx, pte_offset = %lx \n", pte_val(*pte), pte);
          if (pte_none(*pte))
          {
            printk("not mapped in pte\n");
            // return -1;
          }
          else
          {
            page_addr = pte_val(*pte) & PAGE_MASK;
            page_offset = vaddr & ~PAGE_MASK;
            paddr = page_addr | page_offset;
            printk("page_addr = %lx , page_offset = %lx\n", page_addr, page_offset);
            printk("vaddr = %lx , paddr = %lx\n\n", vaddr, paddr);
          }
        }
      }
    } //for_each_process(current){
    //printk("PID is %d\n", current->pid);}
  }

  return 0;
}

static int fixmap(void)
{
  unsigned long FIX_APIC_ADDR 0xffe00000;
	unsigned long apic_virt = fix_to_virt(FIX_APIC_BASE);
	unsigned long val;

	/* FIXMAP */
	set_fixmap_nocache(1, FIX_APIC_ADDR);

	/* Read/Write */
	val = *apic_virt;

  return val;
}

static int __init v2p_init (void) {

  unsigned long vaddr = 0xc0000000;
  int x = 0;
  printk("Module Running\n");
  //vaddr = __get_free_page(GFP_KERNEL);
  printk("get page vaddr=0x %lx \n", vaddr);
  x = vaddr2paddr(vaddr);
  x = fixmap();
  x = vaddr2paddr(vaddr);
  return 0;

}

static void __exit v2p_exit (void) {
  
  printk("Module end\n");
  //free_page(vaddr);
}

module_init(v2p_init);
module_exit(v2p_exit);
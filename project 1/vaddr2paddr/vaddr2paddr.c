#include <linux/linkage.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/mm.h>
#include <linux/export.h>
#include <linux/sched.h>
#include <linux/mm_types.h>
#include <asm/pgtable.h>
#include <asm/page.h>
#include <asm/current.h>

asmlinkage int sys_vaddr2paddr(unsigned int pid) {
  
  struct task_struct *task;
  struct mm_struct *mm;
  task = pid_task(find_vpid(pid), PIDTYPE_PID);

  if (task == NULL)
    return -1; // pid has no task_struct

  mm = task->mm;

  // mm can be NULL in some rare cases (e.g. kthreads)
  // when this happens, we should check active_mm
  if (mm == NULL) {
    mm = task->active_mm;
  }

  struct vm_area_struct *vma = 0;
  unsigned long int vaddr = 0;
  pgd_t *pgd = mm->pgd;
  pmd_t *pmd;
  pte_t *pte;
  unsigned long paddr = 0;
  unsigned long page_addr = 0;
  unsigned long page_offset = 0;
  
  vma = mm->mmap;
  vaddr = vma->vm_start;

  pgd = pgd_offset(mm, vaddr);
  if (pgd_none(*pgd)) {
    printk("not mapped in pgd\n");
    return -1;
  }
  // printk("pgd_val = 0x%lx pgd addr:0x%lx\n", (unsigned long int)pgd_val(*pgd), (unsigned long int)pgd_val(pgd));

  pmd = pmd_offset(pgd, vaddr);
  // printk("pud_val = 0x%lx \n", (unsigned long int)pmd_val(*pmd));
  if (pmd_none(*pmd)) {
    printk("not mapped in pmd\n");
    return -1;
  }
  
  pte = pte_offset_kernel(pmd, vaddr);
  // printk("pte_val = 0x%lx\n", (unsigned long int)pte_val(*pte));
  if (pte_none(*pte)) {
    printk("not mapped in pte\n");
    return -1;
  }
  

  page_addr = page_to_phys(pte_page(*pte));
  page_offset = pte_index(vaddr);
  paddr = page_addr | page_offset;

  printk("page_addr = %lx, page_offset = %lx\n", (unsigned long int)page_addr, (unsigned long int)page_offset);
  printk("vaddr = %lx , paddr = %lx\n" , (unsigned long int)vaddr , (unsigned long int)paddr);

  return 0;
}
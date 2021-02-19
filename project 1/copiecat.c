static unsigned long test_vaddr2paddr(unsigned long vaddr)
{
  pgd_t *pgd;
  pud_t *pud;
  pmd_t *pmd;
  pte_t *pte;
  unsigned long paddr = 0;
  unsigned long page_addr = 0;
  unsigned long page_offset = 0;

  /*init_mm.pgd 是内核空间的页目录，整个内核空间使用此pgd；
  每个用户进程都有自己的pgd,struct task_struct->struct mm_struct->pgd
  因为地址是在内核空间分配的，因此使用内核的pgd；*/
  //这一步是跟进pgd首地址，跟线性地址里面包含的偏移量得到下一级页表pud的物理地址，
  pgd = pgd_offset(&init_mm, vaddr);

  printk("pgd_val = 0x%lx pgd addr:0x%lx\n", (unsigned long int)pgd_val(*pgd), (unsigned long int)pgd_val(pgd));
  printk("init_mm pgd val:0x%lx,pgd addr:0x%lx\n", (unsigned long)pgd_val(*(init_mm.pgd)), pgd_val((init_mm.pgd)));
  printk("pgd_index = %ld\n", pgd_index(vaddr));
  if (pgd_none(*pgd))
  {
    printk("not mapped in pgd\n");
    return -1;
  }
  printk("\n");

  //计算pmd页表地址
  pud = pud_offset(pgd, vaddr);
  printk("pud_val = 0x%lx \n", (unsigned long int)pud_val(*pud));
  if (pud_none(*pud))
  {
    printk("not mapped in pud\n");
    return -1;
  }
  printk("\n");
  //计算pte
  pmd = pmd_offset(pud, vaddr);
  printk("pmd_val = 0x%lx\n", (unsigned long int)pmd_val(*pmd));
  printk("pmd_index = %lu\n", pmd_index(vaddr));
  if (pmd_none(*pmd))
  {
    printk("not mapped in pmd\n");
    return -1;
  }
  printk("\n");

  pte = pte_offset_kernel(pmd, vaddr);
  printk("pte_val = 0x%lx\n", (unsigned long int)pte_val(*pte));
  printk("pte_index = %lu\n", pte_index(vaddr));
  if (pte_none(*pte))
  {
    printk("not mapped in pte\n");
    return -1;
  }

  //先将pte值转换为struct page，然后在转换未物理地址
  page_addr = page_to_phys(pte_page(*pte));
  page_offset = pte_index(vaddr); //页内偏移量
  paddr = page_addr | page_offset;

  printk("page_addr = %lx, page_offset = %lx\n", page_addr, page_offset);
  printk("vaddr = %lx, paddr = %lx\n", vaddr, paddr);

  return paddr;
}

static int test_addr_convet(void)
{
  unsigned long vaddr = 0;
  vaddr = (unsigned long)vmalloc(1000 * sizeof(char));
  if (vaddr == 0)
  {
    printk("vmalloc failed..\n");
    return 0;
  }

  printk("vmalloc_vaddr=0x%lx\n", vaddr);
  test_vaddr2paddr(vaddr);

  vaddr = __get_free_page(GFP_KERNEL);
  if (vaddr == 0)
  {
    printk("__get_free_page failed..\n");
    return 0;
  }
  printk("alloc page addr:0x%lx\n", vaddr);
  test_vaddr2paddr(vaddr);

  vaddr = (unsigned long)kmalloc(4096, GFP_KERNEL);
  if (vaddr == 0)
  {
    printk(KERN_ERR "kmall fail\n");
    return 0;
  }
  printk("kmalloc addr=0x%lx\n", vaddr);
  test_vaddr2paddr(vaddr);
  printk("\n\n");

  return 0;
}
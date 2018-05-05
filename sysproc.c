#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"

struct {
  struct spinlock lock;
  struct proc proc[NPROC];
} ptable;

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_date(void)
{
  char *ptr;
  argptr(0, &ptr, sizeof(struct rtcdate*));
  // seu código aqui

  struct rtcdate *r;
  r = (struct rtcdate*)ptr;
  cmostime(r);
  return 0;
}

int
sys_virt2real(void){
  char *va;
  argstr(0, &va);
  // cprintf("%x\n",va);
  
  pde_t *pde;
  // cprintf("%x\n",pde);
  // cprintf("%x\n",*pde);

  pte_t *pgtab;

  pde = &(myproc()->pgdir[PDX(va)]);
  // cprintf("%x\n",pde);
  
  if(*pde & PTE_P){
    pgtab = (pte_t*)P2V(PTE_ADDR(*pde));
    // cprintf("%x\n",pgtab);
    return (int)(&pgtab[PTX(va)]);
  }
  

  return 0;

  //static pte_t* walkpgdir(pde_t *pgdir, const void *va, int alloc)
  // return (walkpgdir(myproc()->pgdir[PDX(va)],va,0));

}

int
sys_num_pages(void){
  return (uint)(myproc()->sz / (uint)4096);
}

int
sys_corretor(void){
  return 0;
}

int
sys_forkcow(void){
  return forkcow();
}

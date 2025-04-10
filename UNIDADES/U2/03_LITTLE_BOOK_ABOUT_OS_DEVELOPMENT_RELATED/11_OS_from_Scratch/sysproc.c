#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "tareas.h"
#include "osHeader.h"

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
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
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
    if(proc->killed){
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

char *argv1[] = { "TaskId_1", 0 };
char *argv2[] = { "TaskId_2", 0 };

int
sys_createTask(void)
{
  int iPriority,iTaskId;
  if(argint(0,&iPriority)<0)
    return -1;
  if(argint(1,&iTaskId)<0)
    return -1;
  switch(iTaskId){
    case 10:{return createTask(iPriority,iTaskId,argv1);break;}
    case 20:{return createTask(iPriority,iTaskId,argv2);break;}
    default:return -1;
  }
}

int
sys_startTask(void)
{
  int TaskId;
  if(argint(0,&TaskId)<0)
    return -1;
  return startTask(TaskId);
}

int
sys_WaitTask(void)
{
  return waitTask();
}

int
sys_Sched(void)
{
  return Sched();
}

int
sys_candprocs(void)
{
  return candprocs();
}

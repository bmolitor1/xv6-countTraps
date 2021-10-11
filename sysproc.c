#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
//#include "user.h"
//#include "ulib.c"
//#include <stdio.h>
//#include <stdlib.h>
//#include "unistd.h"
#include "syscall.h"

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


//here are the methods for getting the counts for project 2
int
sys_getforkcount(void){
	return myproc()->forkid;	
}

int
sys_getexitcount(void){
	return myproc()->exitid;	
}

int
sys_getwaitcount(void){
	return myproc()->waitid;	
}

int
sys_getpipecount(void){
	return myproc()->pipeid;	
}

int
sys_getreadcount(void){
	return myproc()->readid;	
}

int
sys_getkillcount(void){
	return myproc()->killid;	
}

int
sys_getexeccount(void){
	return myproc()->execid;	
}

int
sys_getfstatcount(void){
	return myproc()->fstatid;	
}

int
sys_getchdircount(void){
	return myproc()->chdirid;	
}

int
sys_getdupcount(void){
	return myproc()->dupid;	
}

int
sys_getgetpidcount(void){
	return myproc()->getpidid;	
}

int
sys_getsbrkcount(void){
	return myproc()->sbrkid;	
}

int
sys_getsleepcount(void){
	return myproc()->sleepid;	
}

int
sys_getuptimecount(void){
	return myproc()->uptimeid;	
}

int
sys_getopencount(void){
	return myproc()->openid;	
}

int
sys_getwritecount(void){
	return myproc()->writeid;	
}

int
sys_getmknodcount(void){
	return myproc()->mknodid;	
}

int
sys_getunlinkcount(void){
	return myproc()->unlinkid;	
}

int
sys_getlinkcount(void){
	return myproc()->linkid;	
}

int
sys_getmkdircount(void){
	return myproc()->mkdirid;	
}

int
sys_getclosecount(void){
	return myproc()->closeid;	
}
int
sys_countTraps(void){
	//printk("hello lol"); //idk man lol might have to change this to something else, like print statements?
	//can't print because this file doesn't import standard libraries smh
	//printf("hello");
	//write(14,"hello",14); can't write either how do you print from kernel like the assignment asks
	//why are you not getting pass num wtfffffffff
	
	int num;
	if(argint(0, &num) < 0)
   		 return -1;
	
	if(num==SYS_fork){
		return sys_getforkcount();
	}
	else if(num==SYS_exit){
  		return sys_getexitcount();
	}
	else if(num==SYS_wait){
  		return sys_getwaitcount();
	}
	else if(num==SYS_pipe){
  		return sys_getpipecount();
	}
	else if(num==SYS_read){
  		return sys_getreadcount();
	}
	else if(num==SYS_kill){
  		return sys_getkillcount();
	}
	else if(num==SYS_exec){
  		return sys_getexeccount();
	}
	else if(num==SYS_fstat){
  		return sys_getfstatcount();
	}
	else if(num==SYS_chdir){
  		return sys_getchdircount();
	}
	else if(num==SYS_dup){
  		return sys_getdupcount();
	}
	else if(num==SYS_getpid){
  		return sys_getgetpidcount();
	}
	else if(num==SYS_sbrk){
  		return sys_getsbrkcount();
	}
	else if(num==SYS_sleep){
  		return sys_getsleepcount();
	}
	else if(num==SYS_uptime){
  		return sys_getuptimecount();
	}
	else if(num==SYS_open){
  		return sys_getopencount();
	}
	else if(num==SYS_write){
  		return sys_getwritecount();
	}
	else if(num==SYS_mknod){
  		return sys_getmknodcount();
	}
	else if(num==SYS_unlink){
  		return sys_getunlinkcount();
	}
	else if(num==SYS_link){
  		return sys_getlinkcount();
	}
	else if(num==SYS_mkdir){
  		return sys_getmkdircount();
	}
	else if(num==SYS_close){
  		return sys_getclosecount();
	}
	else{
		return 69420;
	}
}

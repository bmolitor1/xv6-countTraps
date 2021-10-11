#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "x86.h"
#include "syscall.h"

// User code makes a system call with INT T_SYSCALL.
// System call number in %eax.
// Arguments on the stack, from the user call to the C
// library system call function. The saved user %esp points
// to a saved program counter, and then the first argument.

//global counts
	int forkid = 0;
	int exitid = 0;
	int waitid = 0;
	int pipeid = 0;
	int readid = 0;
	int killid = 0;
	int execid = 0;
	int fstatid = 0;
	int chdirid = 0;
	int dupid = 0;
	int getpidid = 0;
	int sbrkid = 0;
	int sleepid = 0;
	int uptimeid = 0;
	int openid = 0;
	int writeid = 0;
	int mknodid = 0;
	int unlinkid = 0;
	int linkid = 0;
	int mkdirid = 0;
	int closeid = 0;

// Fetch the int at addr from the current process.
int
fetchint(uint addr, int *ip)
{
  struct proc *curproc = myproc();

  if(addr >= curproc->sz || addr+4 > curproc->sz)
    return -1;
  *ip = *(int*)(addr);
  return 0;
}

// Fetch the nul-terminated string at addr from the current process.
// Doesn't actually copy the string - just sets *pp to point at it.
// Returns length of string, not including nul.
int
fetchstr(uint addr, char **pp)
{
  char *s, *ep;
  struct proc *curproc = myproc();

  if(addr >= curproc->sz)
    return -1;
  *pp = (char*)addr;
  ep = (char*)curproc->sz;
  for(s = *pp; s < ep; s++){
    if(*s == 0)
      return s - *pp;
  }
  return -1;
}

// Fetch the nth 32-bit system call argument.
int
argint(int n, int *ip)
{
  return fetchint((myproc()->tf->esp) + 4 + 4*n, ip);
}

// Fetch the nth word-sized system call argument as a pointer
// to a block of memory of size bytes.  Check that the pointer
// lies within the process address space.
int
argptr(int n, char **pp, int size)
{
  int i;
  struct proc *curproc = myproc();
 
  if(argint(n, &i) < 0)
    return -1;
  if(size < 0 || (uint)i >= curproc->sz || (uint)i+size > curproc->sz)
    return -1;
  *pp = (char*)i;
  return 0;
}

// Fetch the nth word-sized system call argument as a string pointer.
// Check that the pointer is valid and the string is nul-terminated.
// (There is no shared writable memory, so the string can't change
// between this check and being used by the kernel.)
int
argstr(int n, char **pp)
{
  int addr;
  if(argint(n, &addr) < 0)
    return -1;
  return fetchstr(addr, pp);
}

extern int sys_chdir(void);
extern int sys_close(void);
extern int sys_dup(void);
extern int sys_exec(void);
extern int sys_exit(void);
extern int sys_fork(void);
extern int sys_fstat(void);
extern int sys_getpid(void);
extern int sys_kill(void);
extern int sys_link(void);
extern int sys_mkdir(void);
extern int sys_mknod(void);
extern int sys_open(void);
extern int sys_pipe(void);
extern int sys_read(void);
extern int sys_sbrk(void);
extern int sys_sleep(void);
extern int sys_unlink(void);
extern int sys_wait(void);
extern int sys_write(void);
extern int sys_uptime(void);
extern int sys_getforkcount(void);
extern int sys_getexitcount(void);
extern int sys_getwaitcount(void);
extern int sys_getpipecount(void);
extern int sys_getreadcount(void);
extern int sys_getkillcount(void);
extern int sys_getexeccount(void);
extern int sys_getfstatcount(void);
extern int sys_getchdircount(void);
extern int sys_getdupcount(void);
extern int sys_getgetpidcount(void);
extern int sys_getsbrkcount(void);
extern int sys_getsleepcount(void);
extern int sys_getuptimecount(void);
extern int sys_getopencount(void);
extern int sys_getwritecount(void);
extern int sys_getmknodcount(void);
extern int sys_getunlinkcount(void);
extern int sys_getlinkcount(void);
extern int sys_getmkdircount(void);
extern int sys_getclosecount(void);
extern int sys_countTraps(void);

static int (*syscalls[])(void) = {
[SYS_fork]    sys_fork,
[SYS_exit]    sys_exit,
[SYS_wait]    sys_wait,
[SYS_pipe]    sys_pipe,
[SYS_read]    sys_read,
[SYS_kill]    sys_kill,
[SYS_exec]    sys_exec,
[SYS_fstat]   sys_fstat,
[SYS_chdir]   sys_chdir,
[SYS_dup]     sys_dup,
[SYS_getpid]  sys_getpid,
[SYS_sbrk]    sys_sbrk,
[SYS_sleep]   sys_sleep,
[SYS_uptime]  sys_uptime,
[SYS_open]    sys_open,
[SYS_write]   sys_write,
[SYS_mknod]   sys_mknod,
[SYS_unlink]  sys_unlink,
[SYS_link]    sys_link,
[SYS_mkdir]   sys_mkdir,
[SYS_close]   sys_close,
[SYS_getforkcount]    sys_getforkcount,
[SYS_getexitcount]    sys_getexitcount,
[SYS_getwaitcount]    sys_getwaitcount,
[SYS_getpipecount]    sys_getpipecount,
[SYS_getreadcount]    sys_getreadcount,
[SYS_getkillcount]    sys_getkillcount,
[SYS_getexeccount]    sys_getexeccount,
[SYS_getfstatcount]   sys_getfstatcount,
[SYS_getchdircount]   sys_getchdircount,
[SYS_getdupcount]     sys_getdupcount,
[SYS_getgetpidcount]  sys_getgetpidcount,
[SYS_getsbrkcount]    sys_getsbrkcount,
[SYS_getsleepcount]   sys_getsleepcount,
[SYS_getuptimecount]  sys_getuptimecount,
[SYS_getopencount]    sys_getopencount,
[SYS_getwritecount]   sys_getwritecount,
[SYS_getmknodcount]   sys_getmknodcount,
[SYS_getunlinkcount]  sys_getunlinkcount,
[SYS_getlinkcount]    sys_getlinkcount,
[SYS_getmkdircount]   sys_getmkdircount,
[SYS_getclosecount]   sys_getclosecount,
[SYS_countTraps]      sys_countTraps,
};

void
syscall(void)
{
  int num;
  struct proc *curproc = myproc();

  num = curproc->tf->eax;
  
  if(num==SYS_fork){
  	forkid++;
	}
	if(num==SYS_exit){
  	exitid++;
	}
	if(num==SYS_wait){
  	waitid++;
	}
	if(num==SYS_pipe){
  	pipeid++;
	}
	if(num==SYS_read){
  	readid++;
	}
	if(num==SYS_kill){
  	killid++;
	}
	if(num==SYS_exec){
  	execid++;
	}
	if(num==SYS_fstat){
  	fstatid++;
	}
	if(num==SYS_chdir){
  	chdirid++;
	}
	if(num==SYS_dup){
  	dupid++;
	}
	if(num==SYS_getpid){
  	getpidid++;
	}
	if(num==SYS_sbrk){
  	sbrkid++;
	}
	if(num==SYS_sleep){
  	sleepid++;
	}
	if(num==SYS_uptime){
  	uptimeid++;
	}
	if(num==SYS_open){
  	openid++;
	}
	if(num==SYS_write){
  	writeid++;
	}
	if(num==SYS_mknod){
  	mknodid++;
	}
	if(num==SYS_unlink){
  	unlinkid++;
	}
	if(num==SYS_link){
  	linkid++;
	}
	if(num==SYS_mkdir){
  	mkdirid++;
	}
	if(num==SYS_close){
  	closeid++;
	}
	if(num==SYS_countTraps){
		curproc->forkid = forkid;
		curproc->exitid = exitid;
		curproc->waitid = waitid;
		curproc->pipeid = pipeid;
		curproc->readid = readid;
		curproc->killid = killid;
		curproc->execid = execid;
		curproc->fstatid=fstatid;
		curproc->chdirid=chdirid;
		curproc->dupid  =  dupid;
		curproc->getpidid=getpidid;
		curproc->sbrkid = sbrkid;
		curproc->sleepid=sleepid;
		curproc->uptimeid=uptimeid;
		curproc->openid = openid;
		curproc->writeid=writeid;
		curproc->mknodid=mknodid;
		curproc->unlinkid=unlinkid;
		curproc->linkid = linkid;
		curproc->mkdirid=mkdirid;
		curproc->closeid=closeid;
		//curproc->tf->eax = syscalls2[num](b);
	}
	

  if(num > 0 && num < NELEM(syscalls) && syscalls[num]) {
    curproc->tf->eax = syscalls[num]();
  } else {
    cprintf("%d %s: unknown sys call %d\n",
            curproc->pid, curproc->name, num);
    curproc->tf->eax = -1;
  }
}

#include "types.h"
#include "stat.h"
#include "user.h"
#include "syscall.h"

int
main(int argc, char *argv[])
{
	/*if(fork()==0){
		printf(1, "hello");
	}else{
		wait();
		printf(1, "goodbye");
	}*/
	//i'm adding code here because idk how to mess with MakeFile
	//printf(1,"sysfork: %d\n",SYS_fork);
	int rc = countTraps(SYS_fork);
	printf(1, "fork: %d\n",rc);
	rc = countTraps(SYS_exit);
	printf(1, "exits: %d\n",rc);
	rc = countTraps(SYS_wait);
	printf(1, "waits: %d\n",rc);
	rc = countTraps(SYS_pipe);
	printf(1, "pipes: %d\n",rc);
	rc = countTraps(SYS_read);
	printf(1, "reads: %d\n",rc);
	rc = countTraps(SYS_kill);
	printf(1, "kills: %d\n",rc);
	rc = countTraps(SYS_exec);
	printf(1, "execs: %d\n",rc);
	rc = countTraps(SYS_fstat);
	printf(1, "fstats: %d\n",rc);
	rc = countTraps(SYS_chdir);
	printf(1, "chdirs: %d\n",rc);
	rc = countTraps(SYS_dup);
	printf(1, "dups: %d\n",rc);
	rc = countTraps(SYS_getpid);
	printf(1, "getpids: %d\n",rc);
	rc = countTraps(SYS_sbrk);
	printf(1, "sbrks: %d\n",rc);
	rc = countTraps(SYS_sleep);
	printf(1, "sleeps: %d\n",rc);
	rc = countTraps(SYS_uptime);
	printf(1, "uptimes: %d\n",rc);
	rc = countTraps(SYS_open);
	printf(1, "opens: %d\n",rc);
	rc = countTraps(SYS_write);
	printf(1, "writes: %d\n",rc);
	rc = countTraps(SYS_mknod);
	printf(1, "mknods: %d\n",rc);
	rc = countTraps(SYS_unlink);
	printf(1, "unlinks: %d\n",rc);
	rc = countTraps(SYS_link);
	printf(1, "links: %d\n",rc);
	rc = countTraps(SYS_mkdir);
	printf(1, "mkdirs: %d\n",rc);
	rc = countTraps(SYS_close);
	printf(1, "closes: %d\n",rc);
	
  int i;

  for(i = 1; i < argc; i++)
    printf(1, "%s%s", argv[i], i+1 < argc ? " " : "\n");
  exit();
}

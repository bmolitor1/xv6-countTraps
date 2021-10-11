struct stat;
struct rtcdate;

// system calls
int fork(void);
int exit(void) __attribute__((noreturn));
int wait(void);
int pipe(int*);
int write(int, const void*, int);
int read(int, void*, int);
int close(int);
int kill(int);
int exec(char*, char**);
int open(const char*, int);
int mknod(const char*, short, short);
int unlink(const char*);
int fstat(int fd, struct stat*);
int link(const char*, const char*);
int mkdir(const char*);
int chdir(const char*);
int dup(int);
int getpid(void);
char* sbrk(int);
int sleep(int);
int uptime(void);
int getforkcount(void);
int getexitcount(void);
int getwaitcount(void);
int getpipecount(void);
int getreadcount(void);
int getkillcount(void);
int getexeccount(void);
int getfstatcount(void);
int getchdircount(void);
int getdupcount(void);
int getgetpidcount(void);
int getsbrkcount(void);
int getsleepcount(void);
int getuptimecount(void);
int getopencount(void);
int getwritecount(void);
int getmknodcount(void);
int getunlinkcount(void);
int getlinkcount(void);
int getmkdircount(void);
int getclosecount(void);
int countTraps(int);

// ulib.c
int stat(const char*, struct stat*);
char* strcpy(char*, const char*);
void *memmove(void*, const void*, int);
char* strchr(const char*, char c);
int strcmp(const char*, const char*);
void printf(int, const char*, ...);
char* gets(char*, int max);
uint strlen(const char*);
void* memset(void*, int, uint);
void* malloc(uint);
void free(void*);
int atoi(const char*);

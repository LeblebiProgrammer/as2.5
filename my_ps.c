#include "my_ps.h"

typedef struct statstruct_proc {
  int           pid;                      /** The process id. **/
  char          exName [_POSIX_PATH_MAX]; /** The filename of the executable **/
  char          state; /** 1 **/          /** R is running, S is sleeping,
			   D is sleeping in an uninterruptible wait,
			   Z is zombie, T is traced or stopped **/
  unsigned      euid,                      /** effective user id **/
                egid;                      /** effective group id */
  int           ppid;                     /** The pid of the parent. **/
  int           pgrp;                     /** The pgrp of the process. **/
  int           session;                  /** The session id of the process. **/
  int           tty;                      /** The tty the process uses **/
  int           tpgid;                    /** (too long) **/
  unsigned int	flags;                    /** The flags of the process. **/
  unsigned int	minflt;                   /** The number of minor faults **/
  unsigned int	cminflt;                  /** The number of minor faults with childs **/
  unsigned int	majflt;                   /** The number of major faults **/
  unsigned int  cmajflt;                  /** The number of major faults with childs **/
  int           utime;                    /** user mode jiffies **/
  int           stime;                    /** kernel mode jiffies **/
  int		cutime;                   /** user mode jiffies with childs **/
  int           cstime;                   /** kernel mode jiffies with childs **/
  int           counter;                  /** process's next timeslice **/
  int           priority;                 /** the standard nice value, plus fifteen **/
  unsigned int  timeout;                  /** The time in jiffies of the next timeout **/
  unsigned int  itrealvalue;              /** The time before the next SIGALRM is sent to the process **/
  int           starttime; /** 20 **/     /** Time the process started after system boot **/
  unsigned int  vsize;                    /** Virtual memory size **/
  unsigned int  rss;                      /** Resident Set Size **/
  unsigned int  rlim;                     /** Current limit in bytes on the rss **/
  unsigned int  startcode;                /** The address above which program text can run **/
  unsigned int	endcode;                  /** The address below which program text can run **/
  unsigned int  startstack;               /** The address of the start of the stack **/
  unsigned int  kstkesp;                  /** The current value of ESP **/
  unsigned int  kstkeip;                 /** The current value of EIP **/
  int		signal;                   /** The bitmap of pending signals **/
  int           blocked; /** 30 **/       /** The bitmap of blocked signals **/
  int           sigignore;                /** The bitmap of ignored signals **/
  int           sigcatch;                 /** The bitmap of catched signals **/
  unsigned int  wchan;  /** 33 **/        /** (too long) **/
  int		sched, 		  /** scheduler **/
                sched_priority;		  /** scheduler priority **/

} procinfo;



char *concat(char *str1, char *str2, char delimeter){
    int length = strlen(str1) + 1 + strlen(str2) + 1;
    int count = strlen(str1)+1;
    if(delimeter == '\0'){
      length -= 1;
      count -= 1;
      //val[strlen(str1)] = delimeter;
    }
    char *val = (char*)malloc(sizeof(char)*length);

    strcpy(val, str1);
    if(delimeter != '\0'){
      val[strlen(str1)] = delimeter;
    }

    int i = 0;
    for(i = 0; i< strlen(str2); i++){
        val[count] = str2[i];
        count++;
    }
    val[count] = '\0';
		//printf("%d len out concat\t", length);
    return val;
}

// char *fileReader(char *fpath){
//   printf("%s\n", fpath);
//     int fd = open(fpath, O_RDONLY);
//     char *fileStr = NULL;
//     if(fd != -1){
//         off_t currentPos = lseek(fd, (size_t)0, SEEK_CUR);
//         int size = lseek(fd, 0, SEEK_END);
//         if(size > 0){
//           printf("HI\n");
//         }
//         lseek(fd, currentPos, SEEK_SET);
//
//         fileStr = (char*)malloc(sizeof(char)*size);
//         read(fd, fileStr, size);
//     }
//     else{
//         printf("Configure file could not be opened\n");
//         exit(0);
//     }
//     close(fd);
//     return fileStr;
// }

// char *procFile(char *path){
//   FILE *fp;
//   fp= fopen(path, "r");
//   if(fp == NULL){
//
//   }
//   else{
//
//     // int pid;
//     // long vsize;
//     // long rss;
//     // procinfo * pinfo = (procinfo*)malloc(sizeof(procinfo));
//     //
//     // // fscanf(fp, "%d %s", &pid, name);
//     // fscanf (fp, " %d %s %c %d %d %d %d %d %u %u %u %u %u %d %d %d %d %d %d %u %u %d %u %u %u %u %u %u %u %u %d %d %d %d %u",
// 	  // /*             1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33*/
//     // &(pinfo->pid),
//     // &(pinfo->exName),
//     // &(pinfo->state),
// 	  // &(pinfo->ppid),
// 	  // &(pinfo->pgrp),
// 	  // &(pinfo->session),
// 	  // &(pinfo->tty),
// 	  // &(pinfo->tpgid),
// 	  // &(pinfo->flags),
// 	  // &(pinfo->minflt),
// 	  // &(pinfo->cminflt),
// 	  // &(pinfo->majflt),
// 	  // &(pinfo->cmajflt),
// 	  // &(pinfo->utime),
// 	  // &(pinfo->stime),
// 	  // &(pinfo->cutime),
// 	  // &(pinfo->cstime),
// 	  // &(pinfo->counter),
// 	  // &(pinfo->priority),
// 	  // &(pinfo->timeout),
// 	  // &(pinfo->itrealvalue),
// 	  // &(pinfo->starttime),
// 	  // &(pinfo->vsize),
// 	  // &(pinfo->rss),
// 	  // &(pinfo->rlim),
// 	  // &(pinfo->startcode),
// 	  // &(pinfo->endcode),
// 	  // &(pinfo->startstack),
// 	  // &(pinfo->kstkesp),
// 	  // &(pinfo->kstkeip),
// 	  // &(pinfo->signal),
// 	  // &(pinfo->blocked),
// 	  // &(pinfo->sigignore),
// 	  // &(pinfo->sigcatch),
// 	  // &(pinfo->wchan));
//     //
//     // pinfo->vsize = pinfo->vsize / 1024;
//     // printf("%d %s  %ld\n",pinfo->pid,pinfo->exName, pinfo->rss);
//     // if(name != NULL){
//     //   printf("%s\n", name);
//     // }
//     fclose(fp);
//   }
//   return "HI";
// }

char *fileReader(char *fpath){
  int fd;
  int MAX = 10;
  char buff[MAX];
  int size = 0;
  char *readString = (char *)malloc(sizeof(char)*MAX);

  fd = open(fpath, O_RDONLY);
  if (fd < 0) { return NULL; }

  int readSize = -1;
  int k = 0;
  char wasWritten = '0';
  while( (readSize = read(fd, buff, MAX)) > 0){
    if(wasWritten != '1'){
      wasWritten = '1';
    }
    size += readSize;

    readString = realloc(readString, size);

    int buffCount = 0;
    for(k = k; k < size; k++){
      readString[k] = buff[buffCount];
      buffCount++;
    }
    bzero(buff, MAX);
  }
  if(wasWritten == '1'){
    readString = realloc(readString, size+1);
    readString[size] = '\0';
  }else{
    free(readString);
    readString = NULL;
  }

  return readString;
}


char *loginFunction(char *fpath){

  char *str = fileReader(fpath);
  long uid = atoi(str);
  struct passwd *pwd;
  char *val = NULL;
  if(strcmp("4294967295", str) == 0){
    printf("root\n");
    val = (char*)malloc(sizeof(char)*5);
    strcpy(val, "root");
    val[4] = '\0';
  }
  else if((pwd = getpwuid(uid)) != NULL){
    printf("%s\n", pwd->pw_name);
    val = (char*)malloc(sizeof(char)*(strlen(pwd->pw_name) + 1));
    strcpy(val, pwd->pw_name);
    val[strlen(pwd->pw_name)] = '\0';
  }

  free(str);
  return val;

}

// char *statusFuntion

void procReader(char * id){

  printf("%s \t", id);
  char *path = concat("/proc", id, '/');
  char *statusPath = concat(path, "status", '/');
  char *statusFile = fileReader(statusPath);

  char *cmdLinePath = concat(path, "cmdline", '/');
  char *cmdLine = fileReader(cmdLinePath);
  if(cmdLine != NULL){
    //printf("Empty line");
  }
  //char *statStr = fileReader(statPath);
  //procFile(statPath);

  char *loginPath = concat(path, "loginuid", '/');
  char *username = loginFunction(loginPath);
  if(username != NULL){
    free(username);
  }
  if(cmdLine != NULL){
    free(cmdLine);
  }

  free(path);
  free(statusPath);
  free(statusFile);
  free(cmdLinePath);

  free(loginPath);
}

void callProc()
{
  char *str = "/proc";
  struct dirent *de;  // Pointer for directory entry

    // opendir() returns a pointer of DIR type.
    DIR *dr = opendir(str);

    if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
        printf("Could not open current directory" );
        return;
    }

    // Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html
    // for readdir()
  while((de = readdir(dr)) != NULL) {
    if(!isdigit(*de->d_name))
        continue;

    //printf("%s\n", de->d_name);

    procReader(de->d_name);

  }



    closedir(dr);
    return;

}


int main(int argc, char **argv){
  callProc();
  return 0;
}

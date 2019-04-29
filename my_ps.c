#include "my_ps.h"

typedef struct statstruct_proc {
  int           pid;                      /** The process id. **/
  char          exName[50]; /** The filename of the executable **/
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

procObj *procFile(char *path){
  procObj * proc = (procObj*)malloc(sizeof(procObj));
  FILE *fp;
  fp= fopen(path, "r");
  if(fp == NULL){

  }
  else{

    int pid = 0;
    char name[50];
    char s = '0';
    // char *state = (char*)malloc(sizeof(char)*3);
    int dummy = 0;
    unsigned int dummy2 = 0;
    unsigned long dummy3 = 0;

    unsigned long utime = 0;
    unsigned long stime = 0;

    unsigned long long startTime = 0;

    fscanf(fp, "%d %s %c %d %d %d %d %d %u %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %llu",
                //1 2 3  4  5  6  7  8  9  10  11  12  13  14  15  16  17  18  19  20  21  22
    &pid,//1
    name,//2
     &s,//3
    &dummy,//4
    &dummy,//5
    &dummy,//6
    &dummy,//7
    &dummy,//8
    &dummy2,//9
    &dummy3,//10
    &dummy3,//11
    &dummy3,//12
    &dummy3,//13
    &utime,//14
    &stime,//15
    &dummy3,//16
    &dummy3,//17
    &dummy3,//18
    &dummy3,//19
    &dummy3,//20
    &dummy3,//21
    &startTime);//22

    utime /= sysconf(_SC_CLK_TCK);
    stime /= sysconf(_SC_CLK_TCK);
    //struct tm *info = localtime(&stime);
    //startTime /= sysconf(_SC_CLK_TCK);
    //printf("%lu %lu %llu", utime, stime, startTime);

    // struct stat attrib;
    // stat(path, &attrib);
    // // char date[10];
    // // strftime(date, 10, "%d-%m-%y", gmtime(&(attrib.st_ctime)));
    // // strftime(date, 20, "%d-%m-%y", localtime(&(attrib.st_ctime)));
    // struct tm *info = localtime(&attrib.st_atime);
    // int hour = info->tm_hour;
    // hour--;
    // hour = hour%24;
    // int min = info->tm_min;
    // int month = info->tm_mon;
    // int day = info->tm_mday;
    // int year = info->tm_year;;
    //
    // //char *hi = asctime(info);
    // // printf("The file %s was last modified at %s\n", filePath, date);
    // time_t t = time(NULL);
    // struct tm tm = *localtime(&t);
    // if(tm.tm_year == year && tm.tm_mon == month && tm.tm_mday == day){
    //   char *sstime = (char*)malloc(sizeof(char)*6);
    //   sstime[0] = hour/10 + '0';
    //   sstime[1] = hour%10 + '0';
    //   sstime[2] = ':';
    //   sstime[3] = min/10 + '0';
    //   sstime[4] = min%10 + '0';
    //   sstime[5] = '\0';
    //   proc->time = sstime;
    //
    //
    //
    // }else{
    //   switch(tm.tm_mon){
    //     case 0:{
    //       char *month = "JAN";
    //       char dday[3];
    //       dday[0] = info->tm_mday/10 + '0';
    //       dday[1] = info->tm_mday%10 + '0';
    //       dday[2] = '\0';
    //       char *date = concat(month, dday, '\0');
    //       proc->time = date;
    //     }
    //     case 1:{
    //       char *month = "FEB";
    //       char dday[3];
    //       dday[0] = info->tm_mday/10 + '0';
    //       dday[1] = info->tm_mday%10 + '0';
    //       dday[2] = '\0';
    //       char *date = concat(month, dday, '\0');
    //       proc->time = date;
    //     }
    //     case 2:{
    //       char *month = "MAR";
    //       char dday[3];
    //       dday[0] = info->tm_mday/10 + '0';
    //       dday[1] = info->tm_mday%10 + '0';
    //       dday[2] = '\0';
    //       char *date = concat(month, dday, '\0');
    //       proc->time = date;
    //     }
    //     case 3:{
    //       char *month = "APR";
    //       char dday[3];
    //       dday[0] = info->tm_mday/10 + '0';
    //       dday[1] = info->tm_mday%10 + '0';
    //       dday[2] = '\0';
    //       char *date = concat(month, dday, '\0');
    //       proc->time = date;
    //     }
    //     case 4:{
    //       char *month = "MAY";
    //       char dday[3];
    //       dday[0] = info->tm_mday/10 + '0';
    //       dday[1] = info->tm_mday%10 + '0';
    //       dday[2] = '\0';
    //       char *date = concat(month, dday, '\0');
    //       proc->time = date;
    //     }
    //     case 5:{
    //       char *month = "JUN";
    //       char dday[3];
    //       dday[0] = info->tm_mday/10 + '0';
    //       dday[1] = info->tm_mday%10 + '0';
    //       dday[2] = '\0';
    //       char *date = concat(month, dday, '\0');
    //       proc->time = date;
    //     }
    //     case 6:{
    //       char *month = "JUL";
    //       char dday[3];
    //       dday[0] = info->tm_mday/10 + '0';
    //       dday[1] = info->tm_mday%10 + '0';
    //       dday[2] = '\0';
    //       char *date = concat(month, dday, '\0');
    //       proc->time = date;
    //     }
    //     case 7:{
    //       char *month = "AUG";
    //       char dday[3];
    //       dday[0] = info->tm_mday/10 + '0';
    //       dday[1] = info->tm_mday%10 + '0';
    //       dday[2] = '\0';
    //       char *date = concat(month, dday, '\0');
    //       proc->time = date;
    //     }
    //     case 8:{
    //       char *month = "SEP";
    //       char dday[3];
    //       dday[0] = info->tm_mday/10 + '0';
    //       dday[1] = info->tm_mday%10 + '0';
    //       dday[2] = '\0';
    //       char *date = concat(month, dday, '\0');
    //       proc->time = date;
    //     }
    //     case 9:{
    //       char *month = "OCT";
    //       char dday[3];
    //       dday[0] = info->tm_mday/10 + '0';
    //       dday[1] = info->tm_mday%10 + '0';
    //       dday[2] = '\0';
    //       char *date = concat(month, dday, '\0');
    //       proc->time = date;
    //     }
    //     case 10:{
    //       char *month = "NOV";
    //       char dday[3];
    //       dday[0] = info->tm_mday/10 + '0';
    //       dday[1] = info->tm_mday%10 + '0';
    //       dday[2] = '\0';
    //       char *date = concat(month, dday, '\0');
    //       proc->time = date;
    //     }
    //     case 11:{
    //       char *month = "DEC";
    //       char dday[3];
    //       dday[0] = info->tm_mday/10 + '0';
    //       dday[1] = info->tm_mday%10 + '0';
    //       dday[2] = '\0';
    //       char *date = concat(month, dday, '\0');
    //       proc->time = date;
    //     }
    //
    //   }
    //
    // }


    if(name[0] == '('){
      name[0] = '[';
    }
    if(name[strlen(name)-1] == ')'){
      name[strlen(name)-1] = ']';
    }
    int k = 0;
    int lenName = strlen(name)+1;
    char *val = (char*)malloc(sizeof(char)*(lenName));
    for(k = 0; k< lenName-1; k++){
      val[k] = name[k];
    }
    val[k] = '\0';
    proc->command = val;
    proc->pid = pid;
    proc->status = s;




    fclose(fp);
  }
  return proc;
  //return "HI";
}

char *fileReader(char *fpath, char limit){
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
    if(limit == '1' && size > 50)
    {
      break;
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
    return NULL;
    //readString = NULL;
  }

  return readString;
}

char *loginFunction(char *fpath){

  char *str = fileReader(fpath, '0');
  long uid = atoi(str);
  struct passwd *pwd;
  char *val = NULL;
  if(strcmp("4294967295", str) == 0){
    //printf("root\n");
    val = (char*)malloc(sizeof(char)*5);
    strcpy(val, "root");
    val[4] = '\0';
  }
  else if((pwd = getpwuid(uid)) != NULL){
    //printf("%s\n", pwd->pw_name);
    val = (char*)malloc(sizeof(char)*(strlen(pwd->pw_name) + 1));
    strcpy(val, pwd->pw_name);
    val[strlen(pwd->pw_name)] = '\0';
  }

  free(str);
  return val;

}

char* interpret(char *fileStr, char *word, char endChar){
  char* begin = strstr(fileStr, word);
  char *val = NULL;
  if(begin != NULL){
    int count = 0;
    count = strlen(word);
    int end = count;
    int start = count;
    char hasStarted = '0';
    for(count = count; count < strlen(begin); count++){
      if(begin[count] == endChar && hasStarted == '1'){
        break;
      }
      if(hasStarted == '1'){
        end++;
      }
      if(isalnum(begin[count]) > 0 && hasStarted == '0'){
        hasStarted = '1';
        start = count;
        end = start;
      }

    }
    //printf("%d", end);
    if(end>0){
      val = (char*)malloc(sizeof(char)*(end+1));
      int i = 0;
      for(start = start; start <= end; start++ ){
        val[i] = begin[start];
        i++;
      }
      val[i] = '\0';
      //printf("%s\t",val);
    }
  }
  return val;
}

float calculateMem(char *strMem, char *strRss){
  long mem = atol(strMem);
  long rss = atol(strRss) * 100;

  float value = ((float)rss)/((float)mem);
  //printf("%.1f\t", value);
  return value;
}

void procPrinter(procObj *_proc, char isInit){
  if(isInit == '1'){
    char *user = "USER";
    char *pid = "PID";
    char *cpu = "%CPU";
    char *mem = "%MEM";
    char *vsz = "VSZ";
    char *rss = "RSS";
    char *tty = "TTY";
    char *status = "STAT";
    char *start = "START";
    char *_time = "TIME";
    char *command = "COMMAND";
    printf ("%-5s\t", user);
    printf ("%5s\t", pid);
    printf ("%5s\t", cpu);
    printf ("%5s\t", mem);
    printf ("%5s\t", vsz);
    printf ("%5s\t", rss);
    printf ("%-5s\t", tty);
    printf ("%-5s\t", status);
    printf ("%-5s\t", start);
    printf("%-5s\t", _time);
    printf ("%-5s\t", command);

  }
  else{
    printf ("%-5s\t", _proc->user);
    printf ("%5d\t", _proc->pid);
    printf ("%5s\t", "");
    printf ("%5.1f\t", _proc->pmem);
    printf ("%5s\t", _proc->vsz);
    printf ("%5s\t", _proc->rss);
    char *tty = "?";
    printf ("%-5s\t",tty);

    printf ("%-5c\t",_proc->status);
    //char *val = _proc->start;
    printf ("%-5s\t", "");
    printf ("%-5s\t", "");
    printf ("%-5s\t",_proc->command);
  }

  printf("\n");
}

void procReader(char * id, char *mem){

  if(strcmp(id, "186") != 0){
    //return;
  }
  char *path = concat("/proc", id, '/');
  char *statusPath = concat(path, "status", '/');
  char *cmdLinePath = concat(path, "cmdline", '/');
  char *loginPath = concat(path, "loginuid", '/');
  char *statPath = concat(path, "stat", '/');

  char *statusFile = fileReader(statusPath, '0');
  char *cmdLine = fileReader(cmdLinePath, '1');
  char *username = loginFunction(loginPath);
  procObj *proc = procFile(statPath);

  //cmdLine = proc->command;

  //find vsz
  proc->vsz = interpret(statusFile, "VmSize:\t", ' ');
  if(proc->vsz == NULL){
    char *vmsize = (char*)malloc(sizeof(char)*2);
    vmsize[0] = '0';
    vmsize[1] = '\0';
    proc->vsz = vmsize;
  }
  //find rss
  proc->rss = interpret(statusFile, "VmRSS:\t", ' ');
  if(proc->rss == NULL){
    char *rss = (char*)malloc(sizeof(char)*2);
    rss[0] = '0';
    rss[1] = '\0';
    proc->rss = rss;

  }
  //calculate %mem
  proc->pmem = calculateMem(mem, proc->rss);
  if(username != NULL){
    proc->user = username;
  }

  if(cmdLine != NULL){
    proc->command = cmdLine;
  }else{
    //proc->command = cmdLine;
    // printf("%s", proc->command);
  }
  //printf("\n");
  procPrinter(proc, '0');
  free(proc->vsz);
  free(proc->rss);
  free(proc);

  free(path);
  free(statusPath);
  free(cmdLinePath);
  free(statPath);
  free(loginPath);

  free(statusFile);
}

void callProc()
{
  procPrinter(NULL, '1');
  char *str = "/proc";
  char *memFilePath = "/proc/meminfo";
  char *statusFile = fileReader(memFilePath, '0');
  char *memInfo = interpret(statusFile, "MemTotal:", ' ');
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

    procReader(de->d_name, memInfo);

  }



    closedir(dr);
    return;

}


int main(int argc, char **argv){
  callProc();
  return 0;
}

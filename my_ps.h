#ifndef MY_PS


#include <stdio.h>
#include <stdlib.h>

#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>

#include <ctype.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>


typedef struct structObj{
  char *user;
  int pid;
  float pcpu;
  float pmem;
  char *vsz;
  char *rss;
  char tty;
  char status;
  char *start;
  char *time;
  char *command;

  struct structObj *next;
}procObj;


#endif

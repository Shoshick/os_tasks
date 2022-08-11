#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <ulimit.h>
#include <unistd.h>

char *strsep(char **restrict stringp, const char *restrict delim);
char *strdup(const char *s);


extern char *optarg;
extern int optind, opterr, optopt;
extern char **environ;

#ifndef MAX_BUF
#define MAX_BUF 200 // USED ​​IN FUNCTION getcwd()
#define _XOPEN_SOURCE_EXTENDED 1
#endif

int main(int argc, char *argv[], char **envp) {
  int rez = 0;

  while ((rez = getopt(argc, argv, "ispuU:cC:dvV:")) != -1) {
    switch (rez) {
    case 'i':
      printf("Real User ID = %d\n", getuid());
      printf("Effective User ID = %d\n\n", geteuid());
      break;
    case 's':
      setpgrp();
      break;
    case 'p':
      printf("Process ID of the calling process = %d\n", getpid());
      printf("Parent process ID of the calling process = %d\n", getppid());
      printf("Process group ID of a process = %d\n\n", getpgrp());
      break;
    case 'u':
      printf("Ulimit value = %d\n\n", UL_GETFSIZE);
      break;
    case 'U':
      long newlimit;
      fprintf(stderr, "Maximum file size = %ld\n", ulimit(UL_GETFSIZE));
      newlimit = atol(optarg);
      ulimit(UL_SETFSIZE, newlimit);
      fprintf(stderr, "New maximum file size = %ld\n", ulimit(UL_GETFSIZE));
      if (fork() == 0) {
        execvp(optarg, &optarg);
        perror(optarg);
        exit(127);
      }
      break;
    case 'c':
      printf("Core file size = %d bytes\n\n", RLIMIT_CORE);
      break;
    case 'C':
      struct rlimit *cdlimit = malloc(sizeof(struct rlimit));
      if (cdlimit == NULL){
        printf("Ошибка, malloc вернул 0");
        return 0;
      }
      cdlimit->rlim_cur = atol(optarg);
      setrlimit(RLIMIT_CORE, cdlimit);
      fprintf(stderr, "New core file size = %d bytes\n\n", RLIMIT_CORE);
      break;
    case 'd':
      char path[MAX_BUF];
      getcwd(path, MAX_BUF);
      printf("Current working directory: %s\n\n", path);
      break;
    case 'v':
      char **all_env_val = environ;
      for (; *all_env_val; all_env_val++)
        printf("%s\n", *all_env_val);
      printf("\n");
      break;
    case 'V':
      char *env_name;
      char *env_val;
      env_val = strdup(optarg);
      if(env_val == NULL){
        printf("Ошибка, malloc вернул 0");
        return 0;
      }
      env_name = strsep(&env_val, "=");
      setenv(env_name, env_val, 1);
      printf("A new environment variable has been added: %s = %s\n\n", env_name, env_val);
      break;
    case '?':
      printf("Ошибка, введена некорректная опция !\n");
      break;
    }
  }
  return 0;
}
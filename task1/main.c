#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <ulimit.h>
#include <unistd.h>

extern char *optarg;
extern int optind, opterr, optopt;

#ifndef MAX_BUF
#define MAX_BUF 200 //USED ​​IN FUNCTION getcwd()
#define _XOPEN_SOURCE_EXTENDED 1
#endif

long newlimit;
char path[200];
char *name[20] = {0};
char *new_val[20] = {0};

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
      cdlimit->rlim_cur = atol(optarg);
      setrlimit(RLIMIT_CORE, cdlimit);
      fprintf(stderr, "New core file size = %d bytes\n\n", RLIMIT_CORE);
      break;
    case 'd':
      getcwd(path, MAX_BUF);
      printf("Current working directory: %s\n\n", path);
      break;
    case 'v':
      for (char **env = envp; *env != 0; env++) {
        char *thisEnv = *env;
        printf("%s\n", thisEnv);
      }
      break;
    case 'V':
      for (int g = 0, i = 0, j = 0, flag = 0; optarg[g] != '\0'; g++) {
        if (optarg[g] == '=') {
          flag = 1;
          continue;
        }
        if (flag == 0) {
          name[i] = optarg[g];
          i += 1;
        }
        if (flag == 1) {
          new_val[j] = optarg[g];
          j += 1;
        }
      }
      setenv(name, new_val, 1);
      printf("A new environment variable has been added: ");
      for (int i = 0; name[i] != '\0'; i++) {
        printf("%c", name[i]);
      }
      printf(" = ");
      for (int i = 0; new_val[i] != '\0'; i++) {
        printf("%c", new_val[i]);
      }
      printf("\n\n");
      break;
    case '?':
      printf("Error found !\n");
      break;
    }
  }
  return 0;
}
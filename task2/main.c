#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

int main(int argc, char *argv[], char **envp) {
  time_t now;
  struct tm *sp;
  setenv("TZ", "UTC8PST", 1);

  (void)time(&now);

  printf("%s", ctime(&now));

  sp = localtime(&now);
  printf("%d/%d/%02d %d:%02d %s\n", sp->tm_mon + 1, sp->tm_mday, sp->tm_year,
         sp->tm_hour, sp->tm_min, tzname[TIME_UTC]);
  exit(0);
  return 0;
}
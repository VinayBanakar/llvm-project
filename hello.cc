#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>

void block_sigprof_handling() {
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGPROF);
    // Block SIGPROF in the main thread
    pthread_sigmask(SIG_BLOCK, &set, NULL);
}

int main(int argc, char **argv) {
  //block_sigprof_handling();

  char *x = (char *)malloc(66);
  printf("Sleeping: %s\n", argv[1]);
  int rem = sleep(atoi(argv[1]));
  printf("Sleep remaining: %d\n", rem);
  memset(x, 0, 66);
  free(x);
  x = (char *)malloc(24);
  memset(x, 0, 24);
  free(x);
  return 0;
}

#include "simplethread.h"

/*
In order to see the effect of a race condition, invoke as follows:
./simplethread 2 | egrep "^\*" | sort -k3,3 -n -k6,6 -n | less
*/
int sharedVariable = 0;

// From pthread_create man page
static void *
thread_start(void *arg)
{
   struct thread_info *tinfo = arg;
   char *uargv, *p;

   printf("Thread %d: top of stack near %p\n",
           tinfo->thread_num, &p);

   simpleThread(tinfo->thread_num);
   return uargv;
}

void simpleThread(int which) {
  int num, val;

  for(num = 0; num < 20; num++) {
    if(random()> RAND_MAX / 2) {
      usleep(500);
    }
    val = sharedVariable;
    printf("*** thread %d sees value %d\n", which , val);
    sharedVariable++;
  }

  val = sharedVariable;
  printf("Thread %d sees final value %d\n", which, val);
}

int main(int argc, char *argv[]) {
  if(argc != 2) {
    printf("Usage %s numThreads\n", argv[0]);
    exit(1);
  }

  int s, tnum, opt, num_threads;
  struct thread_info *tinfo;
  pthread_attr_t attr;
  int stack_size;

  num_threads = atol(argv[1]);
  printf("Starting %d threads\n", num_threads);


  /* Allocate memory for pthread_create() arguments */

  tinfo = calloc(num_threads, sizeof(struct thread_info));
  if (tinfo == NULL)
      handle_error("calloc");

  /* Create one thread for each command-line argument */

  for (tnum = 0; tnum < num_threads; tnum++) {
      tinfo[tnum].thread_num = tnum + 1;

      /* The pthread_create() call stores the thread ID into
         corresponding element of tinfo[] */

      s = pthread_create(&tinfo[tnum].thread_id, NULL,
                         &thread_start, &tinfo[tnum]);
      if (s != 0)
          handle_error_en(s, "pthread_create");
  }

     /* Now join with each thread, and display its returned value */

     for (tnum = 0; tnum < num_threads; tnum++) {
         s = pthread_join(tinfo[tnum].thread_id, NULL);
         if (s != 0)
             handle_error_en(s, "pthread_join");

         printf("Joined with thread %d;\n",
                 tinfo[tnum].thread_num);
     }

     free(tinfo);
     exit(EXIT_SUCCESS);

  /*
  Spawns a new pthread using the given function as an entry point.
  This entry point can be considered the "main" function of that thread of execution.
  pthread_t thr;

  if(pthread_create(&thr, NULL, &entry_point, NULL)) {
    printf("Could not create thread\n");
    exit(2);
  }

  // Causes the calling thread to wait until the given thread terminates.
  if(pthread_join(thr, NULL)) {
    printf("Could not join thread\n");
    exit(3);
  }

  exit(0);
  */
}

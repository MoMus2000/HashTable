#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "uv.h"


int counter = 0;
int timer = 0;

// Will rip as fast as the CPU allows
void idle_handler(uv_idle_t* handle){
    if(counter >= 10){ uv_idle_stop(handle); }
    printf("Counter: %d\n", counter);
    counter ++;
}

void timer_handler(uv_timer_t* handle){
  time_t rawTime;
  time(&rawTime);
  printf("Timer: %ld\n", rawTime);
}

int main(int argc, char* argv[]){
  printf("Libuv version: %s\n", uv_version_string());

  uv_loop_t* loop = uv_default_loop();

  uv_idle_t idler = {0};
  uv_timer_t timer = {0};

  printf("Idling ...\n");
  uv_idle_init(loop, &idler);

  uv_timer_init(loop, &timer);

  uv_idle_start(&idler, idle_handler);

  // Repeat every 1s
  uv_timer_start(&timer, timer_handler, 1, 1000);

  uv_run(loop, UV_RUN_DEFAULT);

  uv_loop_close(loop);

  return 0;
}


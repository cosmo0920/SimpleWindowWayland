#include <iostream>
#include "WaylandCore.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define WIDTH 640
#define HEIGHT 480
#define TITLE  "SimpleWindow"

int main() {
  WaylandCore* core = new WaylandCore(WIDTH, HEIGHT, TITLE);
  
  while( !core->isShouldClose() ) {
    core->pollEvents();
    usleep(50*1000);
  }

  delete core;core = NULL;
  return 0;
}

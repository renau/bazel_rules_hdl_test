#include <cstdio>
#include <stdlib.h>

#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

vluint64_t     global_time = 0;
VerilatedVcdC *tfp         = 0;

void do_terminate() {
#ifdef VM_TRACE
  tfp->dump(global_time);
  tfp->close();
#endif

  printf("simulation finished at cycle %lld\n", (long long)global_time);

  exit(0);
}

void advance_clock(Vcounter *uut) {
  uut->clk ^= 1;
  uut->eval();
#ifdef VM_TRACE
  tfp->dump(global_time);
#endif
  uut->clk ^= 1;

  global_time++;
  uut->eval();
#ifdef VM_TRACE
  tfp->dump(global_time);
#endif

  global_time++;
}

int main() {
  Vcounter top;
#ifdef VM_TRACE
  // init trace dump
  Verilated::traceEverOn(true);
  tfp = new VerilatedVcdC;

  top.trace(tfp, 99);
  tfp->open("output.vcd");
#endif

  top.clk     = 1;
  top.enable  = 0;
  top.reset   = 1;
  advance_clock(&top);
  advance_clock(&top);
  advance_clock(&top);
  top.reset   = 0;
  advance_clock(&top);

  int counter = 0;

  while (global_time < 1000) {
    bool enable = (rand() & 0xF) == 0;
    top.enable = enable;

    if (enable)
      ++counter;

    advance_clock(&top);

    if (top.out != counter) {
      fprintf(stderr, "ERROR: unexpected output of %d vs %d\n", top.out, counter);
      //do_terminate();
    }
  }

  do_terminate();

  return 0;
}

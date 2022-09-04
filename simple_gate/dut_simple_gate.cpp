#include <cstdio>
#include <stdlib.h>

#include "Vsimple_gate.h"
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

void advance_clock(Vsimple_gate *uut) {
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
  Vsimple_gate top;
#ifdef VM_TRACE
  // init trace dump
  Verilated::traceEverOn(true);
  tfp = new VerilatedVcdC;

  top.trace(tfp, 99);
  tfp->open("output.vcd");
#endif

  advance_clock(&top);

  bool a=true;
  bool b=false;
  while (global_time < 40000) {

    a = !a; // 100% switch rate
    b = !b;

    top.a = a;
    top.b = b;

    advance_clock(&top);

    if (top.out != (a^b)) {
      fprintf(stderr, "ERROR: unexpected output of %d vs %d\n", top.out, a^b);
      //do_terminate();
    }
  }

  do_terminate();

  return 0;
}

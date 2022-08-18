#include <cstdio>

#include "Vregfile_256_1w_1r.h"
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

void advance_clock(Vregfile_256_1w_1r *uut) {
  uut->clock ^= 1;
  uut->eval();
#ifdef VM_TRACE
  tfp->dump(global_time);
#endif
  uut->clock ^= 1;

  global_time++;
  uut->eval();
#ifdef VM_TRACE
  tfp->dump(global_time);
#endif

  global_time++;
}

int main() {
  Vregfile_256_1w_1r top;
#ifdef VM_TRACE
  // init trace dump
  Verilated::traceEverOn(true);
  tfp = new VerilatedVcdC;

  top.trace(tfp, 99);
  tfp->open("output.vcd");
#endif

  top.clock   = 1;
  top.wena = 0;

  uint8_t conta=1;

  while (global_time < 500) {
    top.wena = 1;
    top.waddr = conta & 0x1F;
    top.wdata = global_time;

    top.raddr0 = (conta-5) & 0x1F;
    advance_clock(&top);

    ++conta;
  }

  do_terminate();

  return 0;
}

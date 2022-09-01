# bazel_rules_hdl_test

Several tests for bazel_rules_hdl

You need clang or gcc installed. In both cases with openmp installed (libomp-dev for gcc).

```
bazel build //counter:all
```

This performs synthesis and openroad place and route. 

To see the synthesized netlist:

```
ls -al bazel-bazel_rules_hdl_test/bazel-out/*/bin/counter/verilog_counter_synth_synth_output.v
```

To see the openroad results:

```
ls -al bazel-bazel_rules_hdl_test/bazel-out/*/bin/counter
```

NOTE: the WORKSPACE may point to https://github.com/renau/bazel_rules_hdl if there are issues with top of the tree bazel_rules_hdl


## To get the timing models

This is needed for a gate level simulation

```
git clone https://foss-eda-tools.googlesource.com/skywater-pdk/libs/sky130_fd_sc_hd
cd cells
yosys -p "read_verilog -DNO_PRIMITIVES */sky130_fd_sc_hd__*_?.v; write_verilog sky130_fd_sc_hd.v"

# NOTE: there is a type in an imposible wire, just delete the unused wire
```

## To run with verilator

Gate level simulation (runs yosys synthesis of counter, and runs verilator with the generated verilog)

```
bazel build //counter:top_gls 
 ./bazel-bin/counter/top_gls
```

Without the gate level simulation (gls)
```
bazel build //counter:top
 ./bazel-bin/counter/top
```


## Netlist verilator (DIRECTLY, not with bazel)

Tested with Verilator 4.222

```
verilator -O3 --top-module regfile_256_1w_1r ./verilog_regfile_synth_synth_output.v model/sky130_fd_sc_hd.v --cc --trace --exe ./regfile/dut_regfile.cpp
make -C obj_dir -f Vregfile_256_1w_1r.mk Vregfile_256_1w_1r
```


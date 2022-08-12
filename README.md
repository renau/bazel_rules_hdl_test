# bazel_rules_hdl_test

Several tests for bazel_rules_hdl

You need clang or gcc installed. In both cases with openmp installed (libomp-dev for gcc).

```
bazel build //counter:all
```

This performs synthesis and openroad place and route. 

To see the synthesized netlist:

```
ls -al bazel-bazel_rules_hdl_test/bazel-out/k8-fastbuild/bin/counter/verilog_counter_synth_synth_output.v
```

To see the openroad results:

```
ls -al bazel-bazel_rules_hdl_test/bazel-out/k8-fastbuild/bin/counter
```

NOTE: the WORKSPACE may point to https://github.com/renau/bazel_rules_hdl if there are issues with top of the tree bazel_rules_hdl


load("@rules_verilog//verilog:defs.bzl", "verilog_module")
#load("@rules_verilator//verilator:defs.bzl", "sv_library", "verilator_cc_library")
load("@rules_verilator//verilator:defs.bzl", "verilator_cc_library")


verilator_cc_library(
    name = "regfile_256_1w_1r",
    mtop = "regfile_256_1w_1r",
    srcs = ["regfile_256_1w_1r.v"],
)

cc_binary(
    name = "top",
    srcs = ["dut_regfile.cpp"],
    deps = [":regfile_256_1w_1r"],
)


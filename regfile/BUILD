load("@rules_verilog//verilog:defs.bzl", "verilog_module")
#load("@rules_verilator//verilator:defs.bzl", "sv_library", "verilator_cc_library")
load("@rules_verilator//verilator:defs.bzl", "verilator_cc_library")


verilator_cc_library(
    name = "regfile_256_1w_1r",
    mtop = "regfile_256_1w_1r",
    srcs = ["regfile_256_1w_1r.v"],
    trace = True,   # Enable VCD dump
)

cc_binary(
    name = "top",
    srcs = ["dut_regfile.cpp"],
    deps = [":regfile_256_1w_1r"],
)

load("@rules_hdl_pip_deps//:requirements.bzl", "requirement")

load("@rules_hdl//synthesis:build_defs.bzl", "synthesize_rtl")
load("@rules_hdl//place_and_route:build_defs.bzl", "place_and_route")
load("@rules_hdl//verilog:providers.bzl", "verilog_library")

place_and_route(
    name = "place_and_route",
    clock_period = "10",
    core_padding_microns = 20,
    die_height_microns = 20000,
    die_width_microns = 20000,
    placement_density = "0.7",
    synthesized_rtl = ":verilog_regfile_synth",
)

synthesize_rtl(
    name = "verilog_regfile_synth",
    top_module = "regfile_256_1w_1r",
    deps = [
        ":verilog_regfile",
    ],
)

verilog_library(
    name = "verilog_regfile",
    srcs = ["regfile_256_1w_1r.v"],
)


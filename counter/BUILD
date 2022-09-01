
load("@rules_hdl_pip_deps//:requirements.bzl", "requirement")

load("@rules_hdl//synthesis:build_defs.bzl", "synthesize_rtl")
load("@rules_hdl//place_and_route:build_defs.bzl", "place_and_route")
load("@rules_hdl//verilog:providers.bzl", "verilog_library")


place_and_route(
    name = "place_and_route",
    clock_period = "10",
    core_padding_microns = 20,
    die_height_microns = 200,
    die_width_microns = 200,
    placement_density = "0.7",
    synthesized_rtl = ":verilog_counter_synth",
)

synthesize_rtl(
    name = "verilog_counter_synth",
    top_module = "counter",
    deps = [
        ":verilog_counter",
    ],
)

verilog_library(
    name = "verilog_counter",
    srcs = [
        "counter.v",
    ],
)

load("@rules_verilator//verilator:defs.bzl", "verilator_cc_library")

verilator_cc_library(
    name = "counter_gls",
    mtop = "counter",
    srcs = [":verilog_counter_synth", "//model:sky130"],
    vopts = ["-Wno-DECLFILENAME", "--trace-underscore"],
    trace = True,   # Enable VCD dump
)

verilator_cc_library(
    name = "counter",
    mtop = "counter",
    srcs = ["counter.v"],
    trace = True,   # Enable VCD dump
)

cc_binary(
    name = "top",
    srcs = ["dut_counter.cpp"],
    deps = [":counter"],
)

cc_binary(
    name = "top_gls",
    srcs = ["dut_counter.cpp"],
    deps = [":counter_gls"],
)

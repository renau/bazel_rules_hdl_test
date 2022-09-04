
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
    synthesized_rtl = ":verilog_simple_gate_synth",
)

synthesize_rtl(
    name = "verilog_simple_gate_synth",
    top_module = "simple_gate",
    deps = [
        ":verilog_simple_gate",
    ],
)

verilog_library(
    name = "verilog_simple_gate",
    srcs = [
        "simple_gate.v",
    ],
)

load("@rules_verilator//verilator:defs.bzl", "verilator_cc_library")

verilator_cc_library(
    name = "simple_gate_gls",
    mtop = "simple_gate",
    srcs = [":verilog_simple_gate_synth", "//model:sky130"],
    vopts = ["-Wno-DECLFILENAME", "--trace-underscore"],
    trace = True,   # Enable VCD dump
)

verilator_cc_library(
    name = "simple_gate",
    mtop = "simple_gate",
    srcs = ["simple_gate.v"],
    trace = True,   # Enable VCD dump
)

cc_binary(
    name = "top",
    srcs = ["dut_simple_gate.cpp"],
    deps = [":simple_gate"],
)

cc_binary(
    name = "top_gls",
    srcs = ["dut_simple_gate.cpp"],
    deps = [":simple_gate_gls"],
)


load("@rules_hdl_pip_deps//:requirements.bzl", "requirement")

load("@rules_hdl//synthesis:build_defs.bzl", "synthesize_rtl")
load("@rules_hdl//place_and_route:build_defs.bzl", "place_and_route")
load("@rules_hdl//verilog:providers.bzl", "verilog_library")

place_and_route(
    name = "counter_place_and_route",
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



workspace(name = "project")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "rules_python",
    sha256 = "a3a6e99f497be089f81ec082882e40246bfd435f52f4e82f37e89449b04573f6",
    strip_prefix = "rules_python-0.10.2",
    url = "https://github.com/bazelbuild/rules_python/archive/refs/tags/0.10.2.tar.gz",
)

http_archive(
    name = "rules_pkg",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/rules_pkg/releases/download/0.7.0/rules_pkg-0.7.0.tar.gz",
        "https://github.com/bazelbuild/rules_pkg/releases/download/0.7.0/rules_pkg-0.7.0.tar.gz",
    ],
    sha256 = "8a298e832762eda1830597d64fe7db58178aa84cd5926d76d5b744d6558941c2",
)
load("@rules_pkg//:deps.bzl", "rules_pkg_dependencies")
rules_pkg_dependencies()


rules_hdl_git_hash = "3497bab04e37514dcdeb47e3090d57d78e2aa01a"
rules_hdl_git_sha256 = "8e08ae3edf060f61025b54945e8492b2238d2026d8ac7afc021008600edd70d9"
#rules_hdl_git_hash = "5eb04bfd56ce54c8a37eac967326fdc098086a5a"
#rules_hdl_git_sha256 = "501b4777ff18357ca916d9f22e6d943c807bbfdbd8b87a00b0612e359447fc6d"

http_archive(
    name = "rules_hdl",
    sha256 = rules_hdl_git_sha256,
    strip_prefix = "bazel_rules_hdl-%s" % rules_hdl_git_hash,
    urls = [
        "https://github.com/hdl/bazel_rules_hdl/archive/%s.tar.gz" % rules_hdl_git_hash,
        #"https://github.com/renau/bazel_rules_hdl/archive/%s.tar.gz" % rules_hdl_git_hash,
    ],
)

load("@rules_hdl//dependency_support:dependency_support.bzl", rules_hdl_dependency_support = "dependency_support")
rules_hdl_dependency_support()

load("@rules_hdl//:init.bzl", rules_hdl_init = "init")
rules_hdl_init()

http_archive(
    name = "com_grail_bazel_toolchain",
    sha256 = "77c368349e1a90e6e133c7a16743c622856a0e6b4c9935d7d40ece53cf9d3576",
    strip_prefix = "bazel-toolchain-7e7c7cf1f965f348861085183d79b6a241764390",
    urls = ["https://github.com/grailbio/bazel-toolchain/archive/7e7c7cf1f965f348861085183d79b6a241764390.tar.gz"],
)

load("@com_grail_bazel_toolchain//toolchain:deps.bzl", "bazel_toolchain_dependencies")

bazel_toolchain_dependencies()

load("@com_grail_bazel_toolchain//toolchain:rules.bzl", "llvm_toolchain")

llvm_toolchain(
    name = "llvm_toolchain",
    llvm_version = "10.0.1",
    sha256 = {
        "linux": "02a73cfa031dfe073ba8d6c608baf795aa2ddc78eed1b3e08f3739b803545046",
    },
    strip_prefix = {
        "linux": "clang+llvm-10.0.1-x86_64-pc-linux-gnu",
    },
    urls = {
        "linux": [
            # Use a custom built Clang+LLVM binrary distribution that is more portable than
            # the official builds because it's built against an older glibc and does not have
            # dynamic library dependencies to tinfo, gcc_s or stdlibc++.
            #
            # For more details, see the files under toolchains/clang.
            "https://github.com/retone/deps/releases/download/na5/clang+llvm-10.0.1-x86_64-pc-linux-gnu.tar.xz",
        ],
    },
    # Disabled for now waiting on https://github.com/pybind/pybind11_bazel/pull/29
    # sysroot = {
    #     "linux": "@org_chromium_sysroot_linux_x64//:sysroot",
    # },
)


load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# Verilator
http_archive(
    name = "rules_verilator",
    sha256 = "0e81b8138b68e1cab25b8afeea60786b6162c62fef8029180c80c609fd7385cb",
    strip_prefix = "rules_verilator-8bd890eb3a19d1af26499cd587d26d1f354090af",
    urls = ["https://github.com/renau/rules_verilator/archive/8bd890eb3a19d1af26499cd587d26d1f354090af.tar.gz"],
)

load(
    "@rules_verilator//verilator:repositories.bzl",
    "rules_verilator_dependencies",
    "rules_verilator_toolchains"
)
rules_verilator_dependencies()
rules_verilator_toolchains()

# Register toolchain dependencies
load("@rules_m4//m4:m4.bzl", "m4_register_toolchains")
m4_register_toolchains()

load("@rules_flex//flex:flex.bzl", "flex_register_toolchains")
flex_register_toolchains()

load("@rules_bison//bison:bison.bzl", "bison_register_toolchains")
bison_register_toolchains()


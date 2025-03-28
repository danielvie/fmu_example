const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const lib = b.addSharedLibrary(.{
        .name = "BouncingBall",
        .target = target,
        .optimize = optimize,
    });

    lib.linkLibCpp();
    lib.addCSourceFile(.{ .file = b.path("src/BouncingBall.cpp") });
    lib.addCSourceFile(.{ .file = b.path("src/fmi2Functions.cpp") });
    lib.addIncludePath(b.path("fmi2/headers/"));

    b.installArtifact(lib);
}

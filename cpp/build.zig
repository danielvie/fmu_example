const std = @import("std");

pub fn build(b: *std.Build) !void {
    const targets: []const std.Target.Query = &.{
        .{ .cpu_arch = .x86_64, .os_tag = .windows },
        .{ .cpu_arch = .x86_64, .os_tag = .linux, .abi = .gnu },
        // .{ .cpu_arch = .x86_64, .os_tag = .linux, .abi = .musl },
    };

    const optimize = b.standardOptimizeOption(.{});

    for (targets) |t| {
        const lib = b.addSharedLibrary(.{
            .name = "BouncingBall",
            .target = b.resolveTargetQuery(t),
            .optimize = optimize,
        });

        lib.linkLibCpp();
        lib.addCSourceFile(.{ .file = b.path("src/BouncingBall.cpp") });
        lib.addCSourceFile(.{ .file = b.path("src/fmi2Functions.cpp") });
        lib.addIncludePath(b.path("fmi2/headers/"));

        const target_output = b.addInstallArtifact(lib, .{
            .dest_dir = .{
                .override = .{
                    .custom = try t.zigTriple(b.allocator),
                },
            },
        });

        b.getInstallStep().dependOn(&target_output.step);
    }
}

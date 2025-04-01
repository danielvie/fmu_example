const std = @import("std");

fn make_target(query: std.Target.Query) std.Target.Query {
    return query;
}

pub fn build(b: *std.Build) !void {
    const targets: []const std.Target.Query = &.{
        make_target(.{ .cpu_arch = .x86_64, .os_tag = .windows }),
        make_target(.{ .cpu_arch = .x86_64, .os_tag = .linux, .abi = .gnu }),
    };

    const optimize = b.standardOptimizeOption(.{});

    for (targets) |t| {
        const lib = b.addSharedLibrary(.{
            .name = "BouncingBall",
            .target = b.resolveTargetQuery(t),
            .optimize = optimize,
        });

        const cppflags = [_][]const u8{
            "-Wall",
            "-Wextra",
            "-std=c++20",
            "-O2",
        };

        lib.linkLibCpp();
        lib.addCSourceFile(.{
            .file = b.path("src/BouncingBall.cpp"),
            .flags = &cppflags,
        });
        lib.addCSourceFile(.{
            .file = b.path("src/fmi2Functions.cpp"),
            .flags = &cppflags,
        });
        lib.addIncludePath(b.path("include"));
        lib.addIncludePath(b.path("lib/fmi2/headers/"));

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

def _foo_binary_impl(ctx):
    enum_header_paths = [f.path for src in ctx.attr.enum_srcs for f in src.files.to_list()]
    print("\n\nheader paths: {}\n\n".format(enum_header_paths))

    generated_header_file = Label("//software/parameter_v2/config.hpp")
    generated_source_file = Label("//software/parameter_v2/config.cpp")

    args = ctx.actions.args()
    args.add("--output_header_file", generated_header_file)
    args.add("--output_source_file", generated_source_file)
    args.add_all("--include_headers", enum_header_paths)
    ctx.actions.run(
        outputs = [
            generated_source_file,
            #            ctx.attr._generated_header_file,
            #            ctx.attr._generated_source_file,
        ],
        arguments = [args],
        executable = ctx.attr._generation_script,
    )

foo_binary = rule(
    implementation = _foo_binary_impl,
    attrs = {
        "enum_srcs": attr.label_list(allow_files = [".h", ".hpp"]),
        "_generation_script": attr.label(
            default = Label("//software/parameter_v2/scripts:dynamic_param_v2_test"),
            executable = True,
            cfg = "host",
        ),
        #        "_generated_header_file": attr.label(
        #            default = Label("//software/parameter_v2/config.hpp"),
        #            allow_single_file = [".h", ".hpp"],
        #        ),
        #        "_generated_source_file": attr.label(
        #            default = Label("//software/parameter_v2/config.cpp"),
        #            allow_single_file = [".cpp"],
        #        ),
    },
)

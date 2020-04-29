def _generate_dynamic_parameters_impl(ctx):
    output_file = ctx.outputs.generated_config_file

    args = ctx.actions.args()
    args.add("--generated_config_file", output_file)

    if output_file.extension == "hpp":
        print("configured for an hpp file")
        args.add("-cpp")
    elif output_file.extension == "h":
        print("confugured for an h file")
        args.add("-c")
    else:
        fail(
            msg = "Invalid generated_config_file extension. Expected 'h' or 'hpp'",
            attr = ctx.attr.generated_config_file.name,
        )

    enum_headers = [f for target in ctx.attr.enum_targets for f in target[CcInfo].compilation_context.headers.to_list()]
    enum_header_paths = [f.path for f in enum_headers]
    args.add_all("--include_headers", enum_headers)

    ctx.actions.run(
        outputs = [output_file],
        arguments = [args],
        progress_message = "Generating DynamicParameters",
        executable = ctx.executable._generation_script,
    )

    return [DefaultInfo(files = depset([output_file]))]

generate_dynamic_parameters = rule(
    implementation = _generate_dynamic_parameters_impl,
    attrs = {
        "enum_targets": attr.label_list(),
        "_generation_script": attr.label(
            default = Label("//shared/parameter_v2/scripts:dynamic_param_v2_test"),
            executable = True,
            cfg = "host",
            allow_files = True,
        ),
        "generated_config_file": attr.output(mandatory = True),
    },
)

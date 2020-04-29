import yaml
import os
from pathlib import Path
import argparse
from rules_python.python.runfiles import runfiles

# Path relative to the bazel WORKSPACE root
# This path is included in the data for the py_binary
PARAMETER_CONFIG_PATH = Path("./shared/parameter_v2/config")
PARAMETER_CONFIG_PATH = Path(".")
#
def validate_yaml_metadata_schema(document):
    pass

# def validate_yaml_parameter_schema(document):
#     pass
#
# def validate_yaml_schema(loaded_yaml_generator):
#     try:
#         metadata_document = next(loaded_yaml_generator)
#         validate_yaml_metadata_schema(metadata_document)
#     except StopIteration:
#         raise RuntimeError("Error validating ")
#
#     try:
#         parameter_document = next(loaded_yaml_generator)
#         validate_yaml_parameter_schema(parameter_document)
#     except StopIteration:
#         raise RuntimeError("Error validating ")
#
#     try:
#         next(loaded_yaml_generator)
#         raise RuntimeError("")
#     except StopIteration:
#         pzel force ass

def main(generated_config_file, include_headers, generate_for_cpp):
    # ws = os.path.dirname(__file__)
    # # config_root = os.path.join(ws, "shared/parameter_v2/config")
    # config_root = os.path.join(ws, "")
    # for root, dirs, files in os.walk(config_root, topdown=True):
    #     print("{} - {}".format(root, files))
    # r = runfiles.Create()
    # print("r: {}".format(r))
    # assert(r)
    # foo = r.Rlocation("shared")
    # print(foo)
    print(os.getenv("RUNFILES_DIR"))


    # print("in main: {}".format(PARAMETER_CONFIG_PATH))
    # for root, dirs, files in os.walk(PARAMETER_CONFIG_PATH, topdown=True):
    #     print("{} - {}".format(root, files))
        # for filename in files:
        #     full_filepath = Path(root).joinpath(filename)
        #     stream = open(full_filepath, 'r')
        #     all_data = yaml.load_all(stream)
        #     # validate_yaml_schema(all_data)
        #     for data in all_data:
        #         print(data)


    print("writing file")
    with open(generated_config_file, 'w') as of:
        of.write("Hello world\n")

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Generate DynamicParameters')
    parser.add_argument('--generated_config_file', type=str, required=False)
    output_type = parser.add_mutually_exclusive_group(required=True)
    output_type.add_argument("-c", dest='generate_for_cpp', action='store_false')
    output_type.add_argument("-cpp", dest='generate_for_cpp', action='store_true')
    parser.add_argument('--include_headers', nargs='+', required=False)

    args = parser.parse_args()
    main(args.generated_config_file, args.include_headers, args.generate_for_cpp)
    # print("\n\nRunning python config generation")
    # print("\n\nargs: {}\n\n".format(args))
    #
    # print("done")


    # print("I'm RUNNING")
    # for root, dirs, files in os.walk(PARAMETER_CONFIG_PATH, topdown=True):
    #     print("{} - {}".format(root, files))
    #     for filename in files:
    #         full_filepath = Path(root).joinpath(filename)
    #         stream = open(full_filepath, 'r')
    #         all_data = yaml.load_all(stream)
    #         validate_yaml_schema(all_data)
    #         for data in all_data:
    #             print(data)
    # print("DONE")

#!/usr/bin/env python

import yaml
import os
from pathlib import Path
import argparse

# Path relative to the bazel WORKSPACE root
# This path is included in the data for the py_binary
PARAMETER_CONFIG_PATH = Path("./software/parameter_v2/config")

def validate_yaml_metadata_schema(document):
    pass

def validate_yaml_parameter_schema(document):
    pass

def validate_yaml_schema(loaded_yaml_generator):
    try:
        metadata_document = next(loaded_yaml_generator)
        validate_yaml_metadata_schema(metadata_document)
    except StopIteration:
        raise RuntimeError("Error validating ")

    try:
        parameter_document = next(loaded_yaml_generator)
        validate_yaml_parameter_schema(parameter_document)
    except StopIteration:
        raise RuntimeError("Error validating ")

    try:
        next(loaded_yaml_generator)
        raise RuntimeError("")
    except StopIteration:
        pass


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Generate DynamicParameters')
    parser.add_argument('--output_header_file', type=str, required=True)
    parser.add_argument('--output_source_file', type=str, required=True)
    parser.add_argument('--include_headers', type=list, required=True)

    args = parser.parse_args()
    print("\n\nargs: {}\n\n".format(args))


    print("I'm RUNNING")
    for root, dirs, files in os.walk(PARAMETER_CONFIG_PATH, topdown=True):
        print("{} - {}".format(root, files))
        for filename in files:
            full_filepath = Path(root).joinpath(filename)
            stream = open(full_filepath, 'r')
            all_data = yaml.load_all(stream)
            validate_yaml_schema(all_data)
            for data in all_data:
                print(data)
    print("DONE")

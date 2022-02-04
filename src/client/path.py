import os
from pathlib import Path

def get_project_home_path():
    return os.environ['TRAINER_HOME']

def get_build_path():
    return os.path.join(get_project_home_path(), "build")

def get_bin_path():
    return os.path.join(get_project_home_path(), "bin")

def get_client_path():
    return os.path.join(get_project_home_path(), "client")

def get_config_path():
    return os.path.join(get_client_path(), "config")

def get_solution_path():
    return os.path.join(get_project_home_path(), "solutions")
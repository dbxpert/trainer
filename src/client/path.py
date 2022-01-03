import os
from pathlib import Path

def search_from_root(name):
    for path, dirs, files in os.walk("/"):
        if name in dirs:
            return os.path.join(path, name)

def get_project_home_path():
    return search_from_root("trainer")

def get_build_path():
    return os.path.join(get_project_home_path(), "build")

def get_bin_path():
    return os.path.join(get_project_home_path(), "bin")

def get_source_path():
    return os.path.join(get_project_home_path(), "src")

def get_client_path():
    return os.path.join(get_source_path(), "client")

def get_config_path():
    return os.path.join(get_project_home_path(), "client/config")

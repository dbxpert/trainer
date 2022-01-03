import os
import configparser
from path import get_config_path

def get_config():
    config = configparser.ConfigParser()
    config_path = os.path.join(get_config_path(), "trainer.cfg")
    if os.path.isfile(config_path):
        config.read(config_path)
    else:
        raise Exception("Cannot find config file in " + config_path)

    return config


import os
import subprocess
from path import get_build_path
from runtime_context import instance as context

class Builder:
    def __init__(self):
        self.build_path = get_build_path()

    def build(self, debug):
        if os.path.isfile(os.path.join(self.build_path, "Makefile")):
            os.chdir(self.build_path)
            p = subprocess.run(["make", "clean"])

            if debug :
                os.environ["ETF_COMPILE_OPT"] = "-g"

            p = subprocess.run(["make", "--jobs=16"])

            if p.returncode != 0:
                raise Exception("Build failed")
        else:
            raise Exception("Cannot find Makefile")

        context.set_debug(debug)
        context.set_compiled(True)

instance = Builder()

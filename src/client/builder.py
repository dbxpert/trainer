import os
import subprocess
from path import get_build_path, get_solution_path, get_project_home_path
from runtime_context import instance as context

class Builder:
    def build(self, debug):
        if os.path.isfile(os.path.join(get_solution_path(), "CMakeLists.txt")):
            os.chdir(get_build_path())
            if debug:
                p = subprocess.run(["cmake", "-DCMAKE_BUILD_TYPE=Debug", "-DBUILD_SOLUTION_ONLY=ON", get_project_home_path()])
                if p.returncode != 0:
                    raise Exception("Build failed")
            else:
                p = subprocess.run(["cmake", "-DCMAKE_BUILD_TYPE=Release", "-DBUILD_SOLUTION_ONLY=ON", get_project_home_path()])
                if p.returncode != 0:
                    raise Exception("Build failed")
            p = subprocess.run(["cmake", "--build", ".", "--clean-first"])
            if p.returncode != 0:
                raise Exception("Build failed")
        else:
            raise Exception("Cannot find CMakeLists.txt")

        context.set_debug(debug)
        context.set_compiled(True)

instance = Builder()

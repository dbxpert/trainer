import os
import subprocess
from path import get_build_path, get_solution_path, get_project_home_path
from runtime_context import instance as context

class Builder:
    def build(self, debug):
        if os.path.isfile(os.path.join(get_solution_path(), "CMakeLists.txt")):
            os.chdir(get_build_path())
            self.cmake(debug)
            self.compile() 
        else:
            raise Exception("Cannot find CMakeLists.txt")

        context.set_debug(debug)
        context.set_compiled(True)
    
    def cmake(self, debug):
        command = ["cmake"]
        
        if debug:
          command.append("-DCMAKE_BUILD_TYPE=Debug")
        else:
          command.append("-DCMAKE_BUILD_TYPE=Release")

        command.append("-DBUILD_SOLUTION=ON")
        command.append("-DBUILD_SERVER=OFF")
        command.append(get_project_home_path())
        
        p = subprocess.run(command)
        
        if p.returncode != 0:
            raise Exception("CMake failed")
    
    def compile(self):
        p = subprocess.run(["cmake", "--build", "."])
        if p.returncode != 0:
            raise Exception("Compile failed")
    
instance = Builder()
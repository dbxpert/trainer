import os
import subprocess
from path import get_client_path

problem_count = 5

def get_problem_choice():
    print("Select a problem:")
    print()
    client_path = get_client_path()
    os.chdir(client_path)

    test_types = list(range(1, problem_count + 1))
    problems = "".join("Problem..." + str(s) + " " for s in test_types)
    p = subprocess.run(["sh", "./select_option.sh", problems])
    return str(p.returncode)

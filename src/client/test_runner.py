import os
import subprocess
import printer
from path import get_client_path
from command import Command
from communicator import instance as communicator
from runtime_context import instance as context

def get_test_choice():
    print("Select a problem:")
    print()
    client_path = get_client_path()
    os.chdir(client_path)

    test_types = list(range(1, 5))
    problems = "".join("Problem..." + str(s) + " " for s in test_types)
    p = subprocess.run(["sh", "./select_option.sh", problems])

    return test_types[p.returncode - 1]

def get_test_result(choice):
    msg = choice + "\0"
    communicator.send_message(msg)
    reply = communicator.recv_message()
    printer.print_result(reply)

def run_test():
    if not context.server_connected:
        communicator.connect()

    choice = get_test_choice()

    try:
        get_test_result(choice)
    except Exception as e:
        print("Exception")
        communicator.close()
        raise e
    else:
        pass

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

    test_types = ["Sort", "Join", "Grouping"]
    p = subprocess.run(["sh", "./select_option.sh", "".join(str(s)+" " for s in test_types)])

    return test_types[p.returncode - 1]

def get_test_result(comm, command, choice):
    msg = command.name + "," + choice + "\0"
    comm.send_message(msg)
    reply = comm.recv_message()
    printer.print_result(reply)

def run_test(command):
    if not context.server_connected:
        communicator.connect()

    choice = get_test_choice()

    try:
        get_test_result(communicator, command, choice)
    except Exception as e:
        print("Exception")
        communicator.close()
        raise e
    else:
        pass

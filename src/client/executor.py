import os
import subprocess
import time
from version import product_version
from command import Command
from test_runner import run_test
from path import get_bin_path
from builder import instance as builder
from communicator import instance as communicator
from runtime_context import instance as context

def print_wrong():
    print("Invalid command. Enter help.")
    print()

def help():
    print()
    print("Here are commands you can use:")
    print()
    width = max(len(command.name) for command in Command) + 2
    for command in Command:
        if command == Command.NONE or command == Command.WRONG:
            continue
        print(" ", command.name.lower().ljust(width), command.value)
    print()

def start_server():
    bin_path = get_bin_path()
    os.chdir(bin_path)
    p = subprocess.Popen("./trainer")
    return [not p.poll(), p.pid]

def build(debug):
    global context
    if context.server_connected:
        communicator.close()
        time.sleep(1)

    builder.build(debug)
    server = start_server()

    if not server[0]:
        raise Exception("Cannot start server")
    else:
        context.set_server_running(True)

    if context.debug:
        print("Running [PID=" + str(server[1]) + "]")

    time.sleep(1)
    communicator.connect()

def quit():
    global context

    if context.server_connected:
        communicator.close()

    context.set_client_running(False)
    print("Good bye!")

action = {
    Command.NONE : lambda: None,
    Command.WRONG : print_wrong,
    Command.HELP : help,
    Command.VERSION : product_version,
    Command.BUILD : lambda: build(False),
    Command.DEBUG : lambda: build(True),
    Command.RUN : run_test,
    Command.QUIT : quit
}

def run(command):
    action[command]()

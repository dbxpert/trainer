from version import product_version
from command import Command
from solution_runner import run_solution
from solution_debugger import debug_solution
from builder import instance as builder
from runtime_context import instance as context
from communicator import instance as communicator

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

def quit():
    global context
    communicator.close()
    context.set_client_running(False)
    print("Good bye!")

action = {
    Command.NONE : lambda: None,
    Command.WRONG : print_wrong,
    Command.HELP : help,
    Command.VERSION : product_version,
    Command.BUILD : lambda: builder.build(False),
    Command.DEBUG : debug_solution,
    Command.RUN : run_solution,
    Command.QUIT : quit
}

def run(command):
    action[command]()

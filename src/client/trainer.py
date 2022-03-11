from command import Command, parse_command
from executor import run
from version import python_version_check, product_version
from runtime_context import instance as context
from communicator import instance as communicator
import psutil

def welcome():
    python_version_check()
    product_version()
    print("Welcome to the training program for Tibero executor team!")
    run(Command.HELP)

def check_server_running():
    process_name = "trsvr"
    for proc in psutil.process_iter():
        if process_name in proc.name():
            return True
    return False

def main():
    if not check_server_running():
        print("Server is not running")
        sys.exit(1)

    communicator.connect()
    welcome()

    while context.client_running:
        command = input("TRAINER> ")
        command_type = parse_command(command)

        try:
            run(command_type)
        except Exception as e:
            print("Exception: {}".format(e))
            pass

main()

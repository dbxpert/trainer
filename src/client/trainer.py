from command import Command, parse_command
from executor import run
from version import python_version_check, product_version
from runtime_context import instance as context

def welcome():
    python_version_check()
    print()
    product_version()
    print("Welcome to the training program for Tibero executor team!")
    run(Command.HELP)

def main():
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

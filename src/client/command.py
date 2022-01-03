from enum import Enum, auto

class Command(Enum):
    NONE = "none"
    WRONG = "wrong"
    HELP = "print this list"
    VERSION = "print trainer version"
    BUILD = "build your solution"
    DEBUG = "build your solution in debug mode"
    RUN = "run your solution with user test cases"
    SUBMIT = "run your solution with trainer test cases"
    QUIT = "exit"

def parse_command(command):
    command_type = Command.NONE

    if command:
        command = command.upper()
        if command in Command.__members__:
            command_type = Command[command]
        else:
            command_type = Command.WRONG

    return command_type

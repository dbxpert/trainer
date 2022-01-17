from enum import Enum, auto

class Command(Enum):
    NONE = "none"
    WRONG = "wrong"
    HELP = "print this list"
    VERSION = "print trainer version"
    BUILD = "build your solution"
    DEBUG = "build your solution in debug mode"
    RUN = "run your solution with trainer testcases"
    QUIT = "exit"

class Shortcut(Enum):
    H = "HELP"
    V = "VERSION"
    B = "BUILD"
    D = "DEBUG"
    R = "RUN"
    Q = "QUIT"

def parse_command(command):
    command_type = Command.NONE

    if command:
        command = command.upper()
        if command in Command.__members__:
            command_type = Command[command]
        elif command in Shortcut.__members__:
            shortcut = Shortcut[command]
            command_type = Command[shortcut.value]
        else:
            command_type = Command.WRONG

    return command_type

import printer
from communicator import instance as communicator
from runtime_context import instance as context
from problems import get_problem_choice
from builder import instance as builder

def run_solution():
    if (not context.compiled) or (context.debug) :
      builder.build(False)

    choice = get_problem_choice()
    get_test_result(choice)

def get_test_result(choice):
    msg = "RUN_SOLUTION," + choice + "\0"
   
    communicator.send_message(msg)
    reply = communicator.recv_message()
    printer.print_result(reply)

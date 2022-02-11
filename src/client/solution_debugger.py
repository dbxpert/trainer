import printer
import os
import subprocess
from communicator import instance as communicator
from problems import get_problem_choice
from builder import instance as builder
from path import get_bin_path

def debug_solution():
  builder.build(True)
  choice = get_problem_choice()
  execute_debugger(choice)
  get_test_result(choice)

def execute_debugger(choice):
  msg = "PREPARE_DEBUG," + choice + "\0"
  communicator.send_message(msg)
  reply = communicator.recv_message().decode("utf-8")
  
  if reply != "ACK":
    raise Exception("Prepare debug failed")
  
  os.chdir(get_bin_path())
  p = subprocess.run(["cgdb", "--args", "trsol", "trainer/trainer1-4"])
 
  if p.returncode != 0:
    raise Exception("Debugger aborted abnormally")

def get_test_result(choice):
  msg = "VERIFY_DEBUG," + choice + "\0"
 
  communicator.send_message(msg)
  reply = communicator.recv_message()
  printer.print_result(reply)

import struct

class Color:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

def print_test_result(result):
    user_time = float(result[0])/1000000
    success = result[1]

    pass_fail = Color.OKGREEN + "PASS" if success else Color.FAIL + "FAIL"
    pass_fail = pass_fail + Color.ENDC
    test_time = "Elapse Time: " + Color.OKBLUE + str(user_time) + " ms" + Color.ENDC

    print("Test Result: " + pass_fail)
    print(test_time)

def print_result(reply):
    length = len(reply)

    if length != 9:
        raise Exception("Wrong reply format")
    
    res_tuple = struct.unpack('q?', reply)
    print_test_result(res_tuple)
   
    print()
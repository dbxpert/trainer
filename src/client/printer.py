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

    test_header = "[ TEST RESULT ]"
    pass_fail = Color.OKGREEN + "PASS" if success else Color.FAIL + "FAIL"
    pass_fail = pass_fail + Color.ENDC
    test_time = "(Elapsed: " + str(user_time) + " ms)"

    line = test_header + " "
    line = line + pass_fail + " "
    line = line + test_time
    print(line)

def print_result(reply):
    if not bool(reply[0]):
        raise Exception(results[0].decode("utf-8"))

    length = len(reply)

    if length != 17:
        raise Exception("Wrong reply format")
    
    res_tuple = struct.unpack('q?', reply)
    print_test_result(res_tuple)
   
    print()

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

def print_test_result(result, number):
    pm_time = float(result[0])/1000000
    user_time = float(result[1])/1000000
    success = result[2]

    test_header = "[ Test " + str(number) + " ]"
    test_time = "(Requirement: " + str(pm_time) + " ms, User: " + str(user_time) + " ms)"
    pass_fail = Color.OKGREEN + "PASS" if success else Color.FAIL + "FAIL"
    pass_fail = pass_fail + Color.ENDC

    line = test_header + " "
    line = line + pass_fail + " "
    line = line + test_time
    print(line)

def print_result(reply):

    if not bool(reply[0]):
        raise Exception(results[0].decode("utf-8"))

    reply = reply[1:]
    length = len(reply)

    if length % 17 != 0:
        raise Exception("Wrong reply format")

    i = 0
    success = 0

    results = [reply[i:i+17] for i in range (0, length, 17)]

    for result in results:
        res_tuple = struct.unpack('qq?', result)
        print_test_result(res_tuple, i + 1)

        if res_tuple[2]:
            success = success + 1

        i = i + 1

    print()

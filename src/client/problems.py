problem_count = 5

def get_problem_choice():
    user_input = input("Select a problem: [1~"+ str(problem_count) + "] ")
    
    try:
        choice = int(user_input)
        if choice < 1 or choice > problem_count:
          raise Exception("Invalid problem number")
    except ValueError:
        raise Exception("Invalid problem number")

    print()
    return user_input

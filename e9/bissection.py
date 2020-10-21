from math import (exp, sin, cos, tan)
import fileinput


def bissection(low, high, tolerance, func):
    """Function to execute the bissection method and print the answer"""
    if func(low) * func(high) <= 0:  # we're assuming there's only one root in the [0, 1] interval
        while (high - low) > tolerance:
            center = (high + low) / 2
            if func(center) <= 0:
                high = center
            else:
                low = center
        print("%.4f" % ((low + high) / 2))  # print the answer
    else:
        print("No solution")  # print this if there's no solution


def problem_function(p, q, r, s, t, u):
    """The function as stated in the problem"""
    return lambda x: p * exp(-x) + q * sin(x) + r * cos(x) + s * tan(x) + t * (x ** 2) + u


# each line of input corresponds to a test case
for line in fileinput.input():
    # split line of user's input by whitespace to get the parameters of the mathematical function
    func_param = line.split()

    # get a mathematical function with the parameters p, q, r, s, t and u
    f = problem_function(int(func_param[0]), int(func_param[1]), int(func_param[2]),
                         int(func_param[3]), int(func_param[4]), int(func_param[5]))

    # get and print the answer with the bissection method
    bissection(0, 1, 1e-9, f)

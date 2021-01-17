import fileinput
# usar https://pypi.org/project/bitarray/ para tentar aumentar eficiência depois

sieve = []
primes = []
max_dividend = {}
min_non_dividend = {}

def get_sieve(limit):
    """
    Defines every prime number in the interval [2, limit] using the 
    the Sieve of Eratosthenes, and the sieve itself (both global variables)
    """
    global sieve
    global primes

    sieve_size = limit + 1

    # sieve[j] = True if j is prime, and False otherwise
    sieve = [True]*sieve_size

    # zero and one are not prime, by definiton
    sieve[0] = False
    sieve[1] = False

    # check out Wikipedia's entry (Sieve of Eratosthenes) for a mathematical explanation
    for i in range(2, sieve_size):
        if sieve[i]:
            for j in range(2*i, sieve_size, i):
                sieve[j] = False
            primes.append(i)


def get_prime_factors(number):
    """
    Returns the prime factors of 'number'. For example, for number=825, the
    function returns {3: 1, 5: 2, 11: 1} (a dictionary). This means that 825 has one 3, two 5s and
    one 11 as prime factors. In another words 825 = 3*5*5*11.
    """
    factors = {}
    i = 0
    global primes

    # get every prime number in the interval [2, number]
    if number == 0 or number == 1:
        return {}
    possible_factor = primes[i]

    while possible_factor * possible_factor <= number:
        while number % possible_factor == 0:
            factors[possible_factor] = factors.get(possible_factor, 0) + 1
            number = number / possible_factor
        i += 1
        possible_factor = primes[i]

    if number != 1:  # if the remaining number is prime
        factors[int(number)] = factors.get(int(number), 0) + 1

    # return the prime factors, and every possible prime factor (so i can print in a ordered manner)
    return factors        


def print_test_result(n, m):
    """
    Outputs a line stating whether or not m divides n!, in the specified format.
    """
    global max_dividend, min_non_dividend

    if m not in max_dividend:
       max_dividend[m] = 0
    elif max_dividend[m] and max_dividend[m] <= n:
        print(f"{m} divides {n}!")
        return       

    if m not in min_non_dividend:
        min_non_dividend[m] = 0    
    elif min_non_dividend[m] and min_non_dividend[m] >= n:
        print(f"{m} does not divide {n}!")
        return

    m_prime_factors = get_prime_factors(m)
    result = "divides"

    if (m > n) and (m_prime_factors and tuple(m_prime_factors)[-1] <= n): 
        if len(m_prime_factors) != len([v for v in m_prime_factors.values() if v == 1]):
            result = "does not divide"
            m_pf = tuple(m_prime_factors)
            m_greatest_pf = m_pf[-1]
            for f in range(n, 1, -1):
                if max_dividend[m] and max_dividend[m] <= f:
                    print(f"{m} divides {n}!")
                    return
                if min_non_dividend[m] and min_non_dividend[m] >= f:
                    print(f"{m} does not divide {n}!")
                    return                                       
                if m_greatest_pf > f or result == "divides":
                    break
                n_prime_factors = get_prime_factors(f)  

                for factor in m_pf:
                    if factor in n_prime_factors: 
                        m_prime_factors[factor] -= n_prime_factors[factor]               

                        if m_prime_factors[factor] <= 0:
                            del m_prime_factors[factor]
                            if not m_prime_factors:
                                result = "divides"
                                break
                            m_pf = tuple(m_prime_factors)
                            m_greatest_pf = m_pf[-1]
    else:
        if m != 1 and (m > n or m == 0):
            result = "does not divide"                                   

    if result == "divides":
        max_dividend[m] = max(max_dividend[m], n)
    elif result == "does not divide":
        if min_non_dividend[m] == 0:
            min_non_dividend[m] = n
        else:    
            min_non_dividend[m] = min(min_non_dividend[m], n)

    print(f"{m} {result} {n}!")


def main():
    get_sieve(65536)
    for line in fileinput.input():
        params = line.split()
        n = int(params[0])
        m = int(params[1])
        print_test_result(n, m)


if __name__ == "__main__":
    main()

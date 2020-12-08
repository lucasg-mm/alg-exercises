import fileinput
# usar https://pypi.org/project/bitarray/ para tentar aumentar eficiência depois

def get_primes(limit):
    """
    Returns every prime number in the interval [2, limit] using the 
    the Sieve of Eratosthenes.
    """

    if limit == 0 or limit == 1:
        return []

    sieve_size = limit + 1

    # sieve_set[j] = True if j is prime, and False otherwise
    sieve_set = set()

    # zero and one are not prime, by definiton
    sieve_set.add(0)
    sieve_set.add(1)
    primes = []

    # check out Wikipedia's entry (Sieve of Eratosthenes) for a mathematical explanation
    for i in range(2, sieve_size):
        if i not in sieve_set:
            for j in range(2*i, sieve_size, i):
                sieve_set.add(j)
            primes.append(i)

    return primes


def get_prime_factors(number):
    """
    Returns the prime factors of 'number'. For example, for number=825, the
    function returns {3: 1, 5: 2, 11: 1} (a dictionary). This means that 825 has one 3, two 5s and
    one 11 as prime factors. In another words 825 = 3*5*5*11.
    """
    factors = {}
    i = 0

    # get every prime number in the interval [2, number]
    primes = get_primes(number)
    if primes == []:
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

    m_prime_factors = get_prime_factors(m)
    divides = False

    if n < m: 
        for f in range(n, 1, -1):
            n_prime_factors = get_prime_factors(f)   

            for factor in tuple(m_prime_factors):
                if factor in n_prime_factors:  # if the prime factor of m is not even a prime factor of n!, m might divide n!
                    if m_prime_factors[factor] > 0: 
                        m_prime_factors[factor] -= n_prime_factors[factor]               

                        if m_prime_factors[factor] <= 0:
                            m_prime_factors.pop(factor)
                            if not m_prime_factors:
                                divides = True
                                break        
            if divides:
                break
    else:
        divides = True                    

    if divides:
        print(f"{m} divides {n}!")
    else:
        print(f"{m} does not divide {n}!")            

def main():
    for line in fileinput.input():
        params = line.split()
        n = int(params[0])
        m = int(params[1])
        print_test_result(n, m)


if __name__ == "__main__":
    main()

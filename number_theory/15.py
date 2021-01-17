def get_primes(limit):
    """
    Returns every prime number in the interval [2, limit] using the 
    the Sieve of Eratosthenes.
    """

    sieve_size = limit + 1

    # sieve_set[j] = True if j is prime, and False otherwise
    sieve_set = [True for number in range(sieve_size)]

    # zero and one are not prime, by definiton
    sieve_set[0] = sieve_set[1] = False
    primes = []

    # check out Wikipedia's entry (Sieve of Eratosthenes) for a mathematical explanation
    for i in range(2, sieve_size):
        if sieve_set[i]:
            for j in range(2*i, sieve_size, i):
                sieve_set[j] = False
            primes.append(i)

    return primes


def get_fact_prime_factors(factorial):
    """
    Returns the prime factors of factorial!. For example, for factorial=5 (5!), the
    function returns {5: 1, 2: 3, 3: 1} (a dictionary). This means that 5! has one 5, three 2s and
    one 3 as prime factors. In another words 5! = 2*2*2*3*5. It also returns every possible prime factor,
    which is every prime number in the interval [2, factorial].
    """
    factors = {}

    max_primes = get_primes(factorial)  # every possible prime factor
    for number in range(factorial, 1, -1):
        i = 0
        # get every prime number in the interval [2, number]
        primes = get_primes(number)
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
    return (factors, max_primes)


def print_fact_prime_factors(number):
    """
    Prints the output in the specified way.
    """
    factors, primes = get_fact_prime_factors(number)
    print(str(number).rjust(3) + "! =", end="")
    i = 1
    for prime in primes:
        if i == 16:
            print("")
            print(f"{factors[prime]}".rjust(9), end="")
            i = 1
        else:
            print(f"{factors[prime]}".rjust(3), end="")
        i += 1
    print("")


def main():
    number = int(input())
    while number != 0:
        print_fact_prime_factors(number)
        number = int(input())


if __name__ == "__main__":
    main()

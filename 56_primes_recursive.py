def is_prime(n, d=2):
    if n < 2: return False
    if d * d > n: return True
    if n % d == 0: return False
    return is_prime(n, d+1)

def primes_upto(n, current=2):
    if current > n:
        return []
    rest = primes_upto(n, current+1)
    if is_prime(current):
        return [current] + rest
    else:
        return rest

if __name__ == "__main__":
    import sys
    if len(sys.argv) < 2:
        print("Usage: python3 primes_recursive.py <limit>"); sys.exit(1)
    limit = int(sys.argv[1])
    p = primes_upto(limit, 2)
    print(p)

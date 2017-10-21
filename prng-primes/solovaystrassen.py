import time
from fractions import gcd
from blumblumshub import BlumBlumShub

class SolovayStrassen(object):

    prng = BlumBlumShub(496967, 17)

    def prime(self, bits=20):
        number = SolovayStrassen.prng.next(bits)

        while not self.probably_prime(number):
            #print(number)
            number = SolovayStrassen.prng.next(bits)

        return number

    def probably_prime(self, n, precision=15):
        if n == 2: # Se o número é 2, então é primo
            return True

        if not n & 1: # Se o número é par e diferente de 2, então não é primo
            return False

        for _ in range(precision):
            a = self.random(2, n - 2)      # Obtém um número aleatório no intervalo
            x = self.jacobi_symbol(a, n)   # Cálculo do Jacobi Symbol

            if x == 0 or pow(a, (n-1)//2, n) != x % n: # Se x não for 0 ou não satisfazer a congruência,
                return False                          # então n não é primo

        return True # Se tudo falhou, então n provavelmente é primo

    def random(self, low, high): # Número aleatório em [low, high]
        bits = high.bit_length()
        r = SolovayStrassen.prng.next(bits)

        while r < low or r > high:
            r = SolovayStrassen.prng.next(bits)

        return r
    
    # Jacobi Symbol extraído de https://github.com/ralphleon/Python-Algorithms/blob/master/Cryptology/ss_prime.py
    def jacobi_symbol(self, n, m):
        if gcd(n,m) != 1: return 0;
        negative = 1;

        while n > 1:
            if m > n and n % 2 == 1 and m % 2 == 1:
                t = n; n = m; m = t;
                m1 = n % 4;
                m2 = m % 4;

                if m1 == 3 and m2 == 3:
                    negative *= -1;
                n = n % m;

            elif n % 2 == 0:
                n = n / 2;

                if m % 8 == 3 or m % 8 == 5:
                    negative *= -1;
                else:
                    negative *= 1;            
            else:
                print("ERROR!")
                
        return negative;

if __name__ == "__main__":
    gp = SolovayStrassen()

    bits = [40, 56, 80, 128, 168, 224, 256, 512, 1024, 2048, 4096]

    for numBits in bits:
        print("Number of bits: " + str(numBits))
        start_time = time.time()
        number = gp.prime(numBits)
        elapsed_time = time.time() - start_time
        print("Generated prime: " + str(number))
        print("Elapsed time (ms): " + str(elapsed_time*1000))



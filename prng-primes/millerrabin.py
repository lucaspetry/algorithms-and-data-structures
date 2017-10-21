import time
from blumblumshub import BlumBlumShub

class MillerRabin(object):

    prng = BlumBlumShub(496843, 17)

    def prime(self, bits=20):
        number = MillerRabin.prng.next(bits)

        while not self.probably_prime(number):
            #print(number)
            number = MillerRabin.prng.next(bits)

        return number

    def probably_prime(self, n, precision=15):
        if n == 2: # Se o número é 2, então é primo
            return True

        if not n & 1: # Se o número é par e diferente de 2, então não é primo
            return False

        r, s = 0, n - 1
        
        while not s & 1: # Recuperar r e s de 2^r * s = n - 1
            r += 1
            s //= 2

        for _ in range(precision):
            a = self.random(2, n - 1) # Obtém um número aleatório no intervalo

            x = pow(a, n - 1, n)      # Pequeno teorema de Fermat para verificar se o número é primo
            if x == 1 or x == n - 1: # Se verdadeiro, então n pode ser primo
                continue

            for _ in range(r - 1):
                x = pow(x, 2, n)

                if x == 1:
                    return False

                if x == n - 1:
                    continue

            return False

        return True # Se tudo falhou, então n provavelmente é primo

    def random(self, low, high): # Número aleatório em [low, high]
        bits = high.bit_length()
        r = MillerRabin.prng.next(bits)

        while r < low or r > high:
            r = MillerRabin.prng.next(bits)

        return r


if __name__ == "__main__":
    gp = MillerRabin()

    bits = [40, 56, 80, 128, 168, 224, 256, 512, 1024, 2048, 4096]

    for numBits in bits:
        print("Number of bits: " + str(numBits))
        start_time = time.time()
        number = gp.prime(numBits)
        elapsed_time = time.time() - start_time
        print("Generated prime: " + str(number))
        print("Elapsed time (ms): " + str(elapsed_time*1000))



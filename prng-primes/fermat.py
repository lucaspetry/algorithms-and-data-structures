import time
from blumblumshub import BlumBlumShub

class Fermat(object):

    prng = BlumBlumShub(496967, 17)

    def prime(self, bits=20):
        number = Fermat.prng.next(bits)

        while not self.probably_prime(number):
            #print(number)
            number = Fermat.prng.next(bits)

        return number

    def probably_prime(self, n, precision=15):
        if n == 2: # Se o número é 2, então é primo
            return True

        if not n & 1: # Se o número é par e diferente de 2, então não é primo
            return False

        for _ in range(precision):
            a = self.random(2, n - 2) # Obtém um número aleatório no intervalo
            x = pow(a, n - 1, n)      # Pequeno teorema de Fermat para verificar se o número é primo

            if x != 1:            # Se x for diferente de 1, então n não é primo
                return False

        return True # Se tudo falhou, então n provavelmente é primo

    def random(self, low, high): # Número aleatório em [low, high]
        bits = high.bit_length()
        r = Fermat.prng.next(bits)

        while r < low or r > high:
            r = Fermat.prng.next(bits)

        return r


if __name__ == "__main__":
    gp = Fermat()

    bits = [40, 56, 80, 128, 168, 224, 256, 512, 1024, 2048, 4096]

    for numBits in bits:
        print("Number of bits: " + str(numBits))
        start_time = time.time()
        number = gp.prime(numBits)
        elapsed_time = time.time() - start_time
        print("Generated prime: " + str(number))
        print("Elapsed time (ms): " + str(elapsed_time*1000))



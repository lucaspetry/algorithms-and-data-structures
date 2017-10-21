import pyprimes
import time

class BlumBlumShub(object):

    def __init__(self, rand = 8, seed = 3242):
        self.rand = rand # Número para busca de primos
        self.p = self.prime()
        self.q = self.prime()

        # Enquanto P = Q, gera outro Q
        while self.p == self.q:
            self.q = self.prime()

        self.m = self.p * self.q
        self.seed = seed % self.m

    def next(self, bits):
        result = 0

        for i in range(bits):
            self.seed = (self.seed**2) % self.m # X_(n-1) ^ 2 mod (P*Q)

            # Deslocar um bit para esquerda e adicionar o bit
            # menos significativo ao resultado
            result = (result << 1) | (self.seed & 1)
        
        return result

    def prime(self):
        prime = pyprimes.nth_prime(self.rand)

        while prime & 3 != 3: # Verifica se o número é congruente a 3 mod 4
            self.rand = self.rand + 1
            prime = pyprimes.nth_prime(self.rand)
        
        self.rand = self.rand + 1
        return prime

if __name__ == "__main__":
    
    prng = BlumBlumShub();
    numBits = [40, 56, 80, 128, 168, 224, 256, 512, 1024, 2048, 4096]

    for num in numBits:
        print("Number of bits: " + str(num))
        start_time = time.time()
        print("Generated number: " + str(prng.next(num)))
        elapsed_time = time.time() - start_time
        print("Elapsed time (ms): " + str(elapsed_time*1000))



import time

class Xorshift(object):

    X = 24352523235243938281904358347541075349572839407935731984
    Y = 53453462491901992024098509247872937418374983175381780139
    Z = 25924952945924959245328520384091385091809357830758327583
    W = 92394246512145637843190248935824509873140719384091380913

    def next(self, bits):
        result = 0

        for i in range(bits):
            rand = self.rand()

            # Shift a bit to the left and add least significant
            # bit to the result
            result = (result << 1) | (rand & 1)
        
        return result

    def rand(self):
        t = Xorshift.X ^ (Xorshift.X << 11)
        Xorshift.X = Xorshift.Y
        Xorshift.Y = Xorshift.Z
        Xorshift.Z = Xorshift.W
        Xorshift.W = Xorshift.W ^ (Xorshift.W >> 19) ^ t ^ (t >> 8)
        return Xorshift.W

if __name__ == "__main__":
    
    prng = Xorshift();
    numBits = [40, 56, 80, 128, 168, 224, 256, 512, 1024, 2048, 4096]

    for num in numBits:
        print("Number of bits: " + str(num))
        start_time = time.time()
        print("Generated number: " + str(prng.next(num)))
        elapsed_time = time.time() - start_time
        print("Elapsed time (ms): " + str(elapsed_time*1000))

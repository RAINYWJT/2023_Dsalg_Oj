import random

v = random.randint(1, 100)
r = random.randint(1, 100)
c = random.randint(1, 100)

def gen_e():
    return random.randint(0,25)

if __name__ == '__main__':
    print(f'{v} {r} {c}', end=' ')
    for i in range(r*c):
        print(f'{gen_e()}', end=' ')
    print('\n')
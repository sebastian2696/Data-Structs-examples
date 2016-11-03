import sys, random

if __name__ == '__main__':

    n_items = int(sys.argv[1])

    seq_prob = 0.0
    if len(sys.argv) > 2:
        seq_prob = float(sys.argv[2])

    items = []
    k = int(random.random() * 1000000)
    for i in range(n_items):
        if random.random() < seq_prob:
            k += 1
        else:
            k = int(random.random() * 1000000)
        items.append(k)

    for i in items:
        print(i)

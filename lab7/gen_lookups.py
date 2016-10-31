#!/bin/env python
import sys, random

if __name__ == '__main__':
    if len(sys.argv) < 3:
        print("Usage: ./gen_words number_of_items number_of_lookups")
        sys.exit(1)

    n_items = int(sys.argv[1])
    n_lookups = int(sys.argv[2])
    prefix = sys.argv[2]

    items = [i for i in range(n_items)]
    random.shuffle(items)

    with open('lookups-%s.txt' % prefix, 'w') as f:
        for i in range(n_lookups):
            f.write("%s\n" % random.choice(items))

    print("Wrote %s lookups out of %s to %s" % (n_lookups, n_items, 'lookups-%s.txt' % prefix))

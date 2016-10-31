#!/bin/env python
import sys, random

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("Usage: ./gen_words number_of_items")
        sys.exit(1)

    n_items = int(sys.argv[1])
    prefix = sys.argv[1]

    items = [i for i in range(n_items)]
    random.shuffle(items)

    with open('words-%s.txt' % prefix, 'w') as f:
        for k in items:
            v = k
            f.write("%s %s\n" % (k,v))

    print("Wrote %s entries to %s" % (n_items, 'words-%s.txt' % prefix))

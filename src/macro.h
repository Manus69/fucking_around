#ifndef MACRO_H
#define MACRO_H

#define LOG2(n)                    ((unsigned) (8 * sizeof (unsigned long long) - __builtin_clzll((n)) - 1))
#define POWER_OF_2(n)              (__builtin_popcount((n)) == 1)

#endif
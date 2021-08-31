# s3798993-OSP-2021-s1-Assign1-Mon1630
# The Producer-Consumer Problem
Implementing a multi-threaded producer and consumer model under Linux

Create an array of size 10 which are "buckets" that hold items that have been produced - e.g., random numbers,
random strings, etc. Have five threads that are concurrently producing items to fill the available buckets and five
threads that are concurrently consuming those items - say, printing them out to the screen would be fine. Have the
program run for 10 seconds and then clean-up and exit without crashes, race conditions or deadlocks.

    make PCP
    ./simulation

# The Cigarette Smoker’s Problem

Three smokers possess a large supply of one of three ingredients for cigarettes – paper, tobacco and matches. A nonsmoking agent takes an item from two of the smokers at random, and places them on the table. Each smoker checks the items on the table one at a time to see if it is their turn. The third smoker combines the items on the table with his own, and smokes. When finished, the agent places a new, possibly different pair of items on the table.

    make CSP
    ./simulation
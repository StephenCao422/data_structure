## Goals and Overview
In this MP you will:\
-Use three different MinHash implementations to create lossy ‘sketches’ of larger datasets\
-Use MinHash sketches to approximate similarity between datasets\
-Measure the accuracy between exact solutions and approximate solutions\
-Create a graph representation of all pairwise minhash estimates\

## Creating MinHash Sketches Three Ways
As seen in lecture, the MinHash sketch is built on the assumption that a good hash function exhibits SUHA-like uniform independence. Under this assumption, by keeping track of some fraction of our overall hash indices (the k-th minimum) we can estimate both the number of unique items in our dataset but also estimate similarity between two datasets by the relative overlap of our minima.

As with most data structures, there are many ways to implement the same underlying idea. For this assignment we will build vectors of minima three different ways. The first approach, k-minima minhash (or kminhash), is the most straightforward and is what most people think of when they hear ‘bottom-k minhash’. Given one hash, we record the k-smallest hash indices from a dataset as a representation of the full dataset. The second, k-hash minhash (or khash_minhash), is the easiest to implement if you have infinite hash functions but is generally considered to be the worst possible implementation (so we will use it in Part 1 and quickly forget about it). Given k unique hashes, we record only the global minimum value for each hash as a representation of the full dataset. We still end up with a set of k minima, but this is only good if we truly have k-independent hash functions. The last, k-partition minhash (or kpartition_minhash), is very useful when our datasets have a high variability in their cardinalities but applying them to cardinality estimation is not something we have seen how to do. (Instead of having the k-th minima, we have k different minima over different ranges.) Much like k-hash, we will use them in Part 1 but generally not consider them in Part 2. To build a k-partition MinHash, we use one hash function but partitions the hashes based on a particular number of its prefix bits. For example, if our hash produces a five-bit index and we use two prefix bits:
``` 
Hash Indices (binary): [00110, 01110, 01001, 00111 11100, 11111, 11011]

Bucket 00: [110, 111] # Min Value: 00110
Bucket 01: [110, 001] #Min Value: 01001
Bucket 10: [] # Min Value: 11111 <-- THE GLOBAL MAX INT DENOTES NO MINIMA
Bucket 11: [011, 100, 111] # Min Value 11011
``` 
In all three MinHashes, the output of a MinHash sketch is a vector of the minimum hashing values, which in our case is best represented as a vector<uint64_t>. If there are not enough hashed items to make the full MinHash (for example, asking for the 10 minimum hash values for a dataset with four unique values), then the remaining values should be filled with the global maximum integer (Given in the assignment as GLOBAL_MAX_INT). This is most likely to occur in k-partition MinHash with a high number of partitions but a small set of input items. However you will need to implement this edge case for every sketch to pass all tests.
Consider: Is it reasonable to use the maximum possible integer as a ‘reserved’ placeholder for finding no minima? Why or why not?

In addition to the actual MinHash sketches, you are required to write several functions that use your MinHash sketches to estimate both cardinality and similarity. While it is not tested directly, you are encouraged to explore the provided integer datasets and parameter space to see how the accuracy of each of the three minhash approaches perform when compared to the relevant exact calculation.

Consider: Only the bottom-k MinHash is able to use the full sketch to estimate cardinality. But this is possible for both of our other MinHash sketches with a different approach. How might you take advantage of k independent global minima over different ranges as an estimate of cardinality?

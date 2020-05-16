# Project 4
Joy Paul

### instructions to run.
cd into project3 directory
run: gcc allocator_joypaul.c  then  run: ./a.out <memory_size_in_bytes>

## Challenges:

This project was the most challenging of them all. However, I have a working solution. This program only urilizes 
the Best fit strategey to resource efficient. You must pass memory size in bytes while running ./a.out 

"allocator: type command ->" prompts you to enter inputs. Here are a few commands:

RQ: Request memory.
RL P#: Releases memory.
STAT: Request the status of the memory.

Crucial functions:
requestMemory(): Uses the best method to request memory.
releaseMemory(): Releases memory from the linked list DS.
compactMemory(): Merges used and un-used memories together.


## What I learned:

I learned to use custom structs with C. I also learned about memorry allocation with malloc() which was preety neat. 
Since this program only uses the best fir strategy, the other strategies i.e. Worst fit and First fit aren't utilized here.
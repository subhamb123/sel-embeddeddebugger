# Sprint 5 Report (02/02/2024 - 03/02/2024)

[Video](https://youtu.be/T_ZTPY_ZFps)

## What's New (User Facing)
 * Compile time vector table integration
 * Programmatically determines stack base address and size
 * Creates data dump of the memory values around valid addresses found in the general purpose registers and stack

## Work Summary (Developer Facing)
New assembly code was created to store the general purpose register values without any overwrite. Functions were added to snapshot.c to determine valid addresses
and create the data dump. Exception handler was also integrated into the SynchronousInterruptHandler function to improve handling of exceptions.



## Unfinished Work
The stack decoding algorithm needs revisited as a aspect of its functionality was not as complete to its goals.
Supporting multiple threads is still not implmented.

## Completed Issues/User Stories
Here are links to the issues that we completed in this sprint

 * 
 
 ## Incomplete Issues/User Stories
 Here are links to issues we worked on but did not complete in this sprint:

 * Modify stack decoder, call order https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/issues/52
    Data required was not being dumped properly, corrected too late into the spring to address and test properly. 
 * Multi-Threaded Snapshots https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/issues/54
    Lower priority than increasing speed, and is beyond original scope     


## Code Files for Review
Please review the following code files, which were actively developed during this sprint, for quality:
 * [main.py] (https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/blob/main/debugger/Utility/main.py)
 * [read-write.py] https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/blob/main/debugger/Configs/read-write.py
 * [snapshot.c] https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/blob/dochoa-Debugger/src/snapshot.c
 * [debugger.py] https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/blob/main/debugger/Utility/StackDecode.py

## Retrospective Summary
Here's what went well:
  * Preserving the general purposer register values
  * Programmatically loading symbol values
  * Integrating our exception handler with the system

Here's what we'd like to improve:
   * Testing - all testing has so far been manual
   * Revisiting stack decoding script for correctness
   * Refactoring - It still needs to be proven 100% to be abstract

Here are changes we plan to implement in the next sprint:
   * Multithreading
   * Create automated testsdisc


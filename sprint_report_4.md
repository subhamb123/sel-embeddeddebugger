# Sprint 4 Report (1/08/2024 - 02/02/2024)

[Video](https://youtu.be/q6VmzGlIHkw)

## What's New (User Facing)
 * Increased snapshot loading speed
 * Refactored code

## Work Summary (Developer Facing)
The time required to load a snapshot onto the board has been decreased. Additionally, the code has been refactored for style.


## Unfinished Work
The stack decoding algorithm needs revisited as a aspect of its functionality was not as complete to its goals.
Supporting multiple threads is next, as well as testing.

## Completed Issues/User Stories
Here are links to the issues that we completed in this sprint

 * Merge Documents into one https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/issues/21
 * Refactor code https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/issues/51
 * Increase speed of writing snapshot back to system https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/issues/49
 
 ## Incomplete Issues/User Stories
 Here are links to issues we worked on but did not complete in this sprint:

 * Modify stack decoder, call order https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/issues/52
    Realization of the was found late in the sprint, not enough time to adjust to fix 
 * Multi-Threaded Snapshots https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/issues/54
    Lower priority than increasing speed, and is beyond original scope
      


## Code Files for Review
Please review the following code files, which were actively developed during this sprint, for quality:
 * [main.py] (https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/blob/main/debugger/Utility/main.py)
 * [read-write.py] https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/blob/main/debugger/Configs/read-write.py

## Retrospective Summary
Here's what went well:
  * Refactored code for easier review
  * Increased speeds for loading snapshots

Here's what we'd like to improve:
   * Testing - all testing has so far been manual
   * Revisiting stack decoding script for correctness
   * Refactoring - It still needs to be proven 100% to be abstract

Here are changes we plan to implement in the next sprint:
   * Multithreading
   * Create automated testsdisc


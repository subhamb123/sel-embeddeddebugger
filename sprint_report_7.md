# Sprint 6 Report (03/02/2024 - 04/02/2024)

[Video](https://youtu.be/3sjefHx5_tU)

## What's New (User Facing)
 * FreeRTOS Stack Tracing for All Stacks
 * Stretch goals met!

## Work Summary (Developer Facing)
Implementing the ability to trace the stack of every function within a FreeRTOS implementaiton was completed. Additionally, all other functions were further tested for correctness.


## Unfinished Work
Our stretch goals have been met, no other unfinished work is left!

## Completed Issues/User Stories
Here are links to the issues that we completed in this sprint
 * Deadlock Detector: https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/issues/61
 * MModify decoding script to work with multithreaded snapshots: https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/issues/62
 * Print correct stack information for tasks: https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/issues/64
 
 ## Incomplete Issues/User Stories
None!

## Code Files for Review
Please review the following code files, which were actively developed during this sprint, for quality:
 * [freeRTOS-StackDecode.py] (https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/blob/hpotter94-FreeRTOS-Stack-Decode-Patch/debugger/freeRTOS-StackDecode.py)
 * [freeRTOS_snapshot.c] (https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/blob/dochoa-Debugger/freertos%20src/freeRTOS_snapshot.c)
 * [freeRTOS_snapshot.h] (https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/blob/dochoa-Debugger/freertos%20src/freeRTOS_snapshot.h)
 * [snapshot_handler.py] (https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/blob/dochoa-Debugger/debugger/snapshot_handler.py)
 * [freertos_hello_world.c] (https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/blob/main/src/freertos_hello_world.c)

## Retrospective Summary
Here's what went well:
  * Completed all stretch tasks!

Here's what we'd like to improve:
  * Learn to defeat Murphy in regards to Murphy's Law when it comes to demoing

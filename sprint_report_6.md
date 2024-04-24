# Sprint 6 Report (03/02/2024 - 04/02/2024)

[Video](https://youtu.be/HcbLP8OQ4YY)

## What's New (User Facing)
 * FreeRTOS implementation of snapshots
 * FreeRTOS Deadlock Detector

## Work Summary (Developer Facing)
Snapshot functionality has been implemeneted into FreeRTOS applications. This will allow for snapshots to be taken and loaded into FreeRTOS instances running on the target SOM. Additionally, one of the tasks before implementing multiple threads with FreeRTOS was to check if deadlock detection between two tasks worked properly. This is important to test and document because should such a scenario happen when using multiple threads, now we know how to use another task to detect this so we can solve it and not cause further delay.


## Unfinished Work
Adding FreeRTOS functionality to the stack decoding script still needs finished. It will trace the stack of active task when the exception occurs, however we have the goal of printing the trace stack of every task active in the FreeRTOS implementation on exception - printing the information required for non-active tasks has proven to be more difficult than initally expected.


## Completed Issues/User Stories
Here are links to the issues that we completed in this sprint
 * Modify Stack Decoder, Call Order https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/issues/52
 * Multi-Threaded Snapshots: https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/issues/54
 * Deadlock Detector: https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/issues/61
 
 ## Incomplete Issues/User Stories
 Here are links to issues we worked on but did not complete in this sprint:
 * Print correct stack information for tasks https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/issues/64 Was originally included in issue #54; this has shown to be far more difficult than anticipated, and has been created as a separate issue.
 * Modify decoding script to work with multithreade snapshots https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/issues/62 Stack location for non-active tasks is not being uncovered correctly, making this not possible yet.


## Code Files for Review
Please review the following code files, which were actively developed during this sprint, for quality:
 * [StackDecode.py] (https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/blob/hpotter-StackDecode/debugger/StackDecode.py)
 * [freeRTOS_snapshot.c] (https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/blob/dochoa-Debugger/freertos%20src/freeRTOS_snapshot.c)
 * [freeRTOS_snapshot.h] (https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/blob/dochoa-Debugger/freertos%20src/freeRTOS_snapshot.h)
 * [snapshot_handler.py] (https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/blob/dochoa-Debugger/debugger/snapshot_handler.py)
 * [freertos_hello_world.c] (https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/blob/main/src/freertos_hello_world.c)
 * [showcase.c] (https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/blob/main/debugger/showcase.c)

## Retrospective Summary
Here's what went well:
  * Corrected and verified trace call recreation
  * Successfully implementing multithreaded snapshot capabilities
  * Successfully implementing a deadlock detector

Here's what we'd like to improve:
  * Cleaning/refactoring code

Here are changes we plan to implement in the next sprint:
   * Trace call recreation of every task in a FreeRTOS snapshot, not just the active one during the exception.


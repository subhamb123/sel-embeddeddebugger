# Sprint 6 Report (03/02/2024 - 04/02/2024)

[Video]()

## What's New (User Facing)
 * FreeRTOS Deadlock Detector

## Work Summary (Developer Facing)
One of the tasks before implementing multiple threads with FreeRTOS was to check if deadlock detection between two tasks worked properly. This is important to test and document because should such a scenario happen when using multiple threads, now we know how to use another task to detect this so we can solve it and not cause further delay.



## Unfinished Work


## Completed Issues/User Stories
Here are links to the issues that we completed in this sprint

 * Deadlock Detector: https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/issues/61
 
 ## Incomplete Issues/User Stories
 Here are links to issues we worked on but did not complete in this sprint:

 *  


## Code Files for Review
Please review the following code files, which were actively developed during this sprint, for quality:
 * [freertos_hello_world.c] (https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/blob/main/src/freertos_hello_world.c)
 * [showcase.c] (https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/blob/main/debugger/showcase.c)

## Retrospective Summary
Here's what went well:
  * Successfully implementing a deadlock detector

Here's what we'd like to improve:
   * 

Here are changes we plan to implement in the next sprint:
   * 


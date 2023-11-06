# Sprint 2 Report (10/05/23 - 11/05/2023)

Video: https://youtu.be/uoWRx5RXBtE

## What's New (User Facing)
 * Board outputs stack and register values
 * Python script to read in values from serial port
 * Extract symbol table from generated elf file
 * Basic implementation of stack decoding

## Work Summary (Developer Facing)
We created an exception handler that prints out the stack contents and register values through the serial port. The exception handler uses assembly code to access the register data. It also uses assembly code to integrate itself in the vector table. The exception handler gets called whenever an exception is thrown. The Python script uses pyserial to read in the information outputted by the exception handler. It handles both the stack and registers values. The next step is for it to generate TCL scripts to write the information back into the stack and registers.


## Unfinished Work
We did not inmplement writing the information back to the board. That part is still unfinished. We ran out of time. It took longer than expected to get the exception handler integrated with the vector table. Additionally the logic to decode the stack's function names has not been perfected. This has been more difficult than anticipated and we ran out of time. We will make sure it complete that part by the end of sprint 3.

## Completed Issues/User Stories
Here are links to the issues that we completed in this sprint
(for brevity, only one issue per document will be included):

 * Setup and verify development environments https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/issues/10
 * Solution Approach https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/issues/11
 * Testing and Acceptance https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/issues/22
 * Create script to extract table https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/issues/34
 * Create script to read from serial porthttps://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/issues/38
 * Create method to decode stack using symbol table https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/issues/35

 ## Incomplete Issues/User Stories
 Here are links to issues we worked on but did not complete in this sprint:
 
 c Create script to decode function names from stack https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/issues/33
    This needs to be tested more thoroughly before being considered complete.
 * Integrate with vector table https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/issues/39
    This took more time than anticipated to complete.
 * Integrate stack reading and decoding https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/issues/36
    We could not start this early enough to finish for this sprint, as it required sufficient progress from the previous issues before starting.


## Code Files for Review
Please review the following code files, which were actively developed during this sprint, for quality:
 * [read_serial.py](https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/blob/dochoa-Debugger/debugger/read_serial.py)
 * [snapshot.h](https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/blob/dochoa-Debugger/workspace/TestProject/src/snapshot.h)
 * [snapshot.c](https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/blob/dochoa-Debugger/workspace/TestProject/src/snapshot.c)
 * [extractSymbolTable.py] (https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/blob/hpotter-StackDecode/extractSymbolTable.py)
 * [stackDecode.py] (https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/blob/hpotter-StackDecode/StackDecode.py)

## Retrospective Summary
Here's what went well:
  * Writing through the serial port
  * Extracting symbol table
  * Item x
 
Here's what we'd like to improve:
   * Consistency of reading in from the serial port
   * Greater testing during development
   * Documenting and keeping Github issues updated
   * Integrating as we develop
  
Here are changes we plan to implement in the next sprint:
   * Complete semester 1 goals:
   * Generate a function call stack
   * Decode the stack data
   * Integrate these components
   * Restore system state

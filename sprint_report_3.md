# Sprint 3 Report (11/05/2023 - 12/05/2023)

Video: <insert link>

## What's New (User Facing)
 * Improve script for parsing script, manually tested
 * Created script to integrate reading script dump and parser
 * Create dump history
 * Debugger writes stack and register values back to the baord

## Work Summary (Developer Facing)
We added more functionality to the debugger. It can now generate and execute TCL scripts to write back the contents
of the stack and registers to the board. 

## Unfinished Work
So far we are only working with one CPU core. The debugger currently has the stack location and size hard coded but
once we start working with multiple cores we will change that.

## Completed Issues/User Stories
Here are links to the issues that we completed in this sprint

 * Create script to decode function names from stack https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/issues/33
 * Create file to integrate stack reading and decoding https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/issues/36
 * Integrate COM port communication and stack parsers https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/issues/45  
 * Create tcl script that will restore stack and register data https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/issues/37
 * Integrate with vector table https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/issues/39
 * Manual testing for stack decoding https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/issues/46
 
 ## Incomplete Issues/User Stories
 Here are links to issues we worked on but did not complete in this sprint:

 * Merge Documents into one https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/issues/21
    This has just been low priority, especially as it will be continue to be added to over the project's life.  


## Code Files for Review
Please review the following code files, which were actively developed during this sprint, for quality:
 * [main.py](https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/blob/main/debugger/main.py)
 * [stackDecode.py](https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/blob/main/debugger/StackDecode.py)
 * [read_registers_to_save.py](https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/blob/main/debugger/read_registers_to_save.py)
 * [debugger.py](https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/blob/main/debugger/debugger.py)

## Retrospective Summary
Here's what went well:
  * Integrating different elements
  * Extracting symbol table
  * System integration - CI is next!
  * Generating and executing TCL scripts

Here's what we'd like to improve:
   * Testing - all testing has so far been manual
   * Greater testing during development
   * Decrease hard coded parts
   * Technical documentation
  
Here are changes we plan to implement in the next sprint:
   * Establish CI for more streamlined updates
   * Create automated tests
   * Restore complete system state

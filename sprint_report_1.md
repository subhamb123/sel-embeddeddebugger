# Sprint x Report (8/26/23 - 10/05/2023)

## What's New (User Facing)
 * User Interface Mockup
 * Sprint video! https://youtu.be/y9P1kN8TdcE

## Work Summary (Developer Facing)
Over this last month we have prepared for starting this project off. Due to its nature of working with a specific set of hardware, this has taken some time for us to get the hardware and get accustomed to the new environment. 
We have started looking into the different aspects that will contribute to our understanding of this system - namely the ARM exception model, common ARM instructions, and TCL - and will be shortly starting to use this in a more practical means. 
Once we have a more solid understanding of this, we can start tackling the project properly. As we have laid out the components of this project's design, we can also examine what will take priority. 


## Unfinished Work
Not all of our environments are working correctly, and those that are working correctly are still having some issues. We ran into unforseen compatibility issues (for example, a computer running an incompatible architecture for the IDE vitis), as well as driver issues
for example. It was unexpected that this would turn out to be a difficult task. These should take not to resolve, however if problems persist we will have to contact AMD (the manufacturer of the SOM, developer of SOM) or talk with SEL about the environment they want us to
develop within. My hope was to have a finished program we completed through the SOM to print onto the PC screen, however we came up short when getting it to print. The signal will send to the SOM and it will run, however communication errors with USB drivers
and serial ports have been problematic.

If applicable, explain the work you did not finish in this sprint. For issues/user stories in the current sprint that have not been closed, (a) any progress toward completion of the issues has been clearly tracked (by checking the checkboxes of  acceptance criteria), (b) a comment has been added to the issue to explain why the issue could not be completed (e.g., "we ran out of time" or "we did not anticipate it would be so much work"), and (c) the issue is added to a subsequent sprint, so that it can be addressed later.

## Completed Issues/User Stories
Here are links to the issues that we completed in this sprint:

 * There are many issues, each for individual parts of assignments. To avoid bloat, only the main issues for these are listed.
 * https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/issues/7 Requirements and Specifications - General 
 * https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/issues/11 Solution Approach - Introduction
 * https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/issues/9 Distribute Hardware
 * https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/issues/8 Quickstart Guide for Development Boards
 
 ## Incomplete Issues/User Stories
 Here are links to issues we worked on but did not complete in this sprint:
 
 * https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/issues/1 ARM Exception Handler Research
    This will likely remain incomplete until further implementation.
 * https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/issues/19 Resolve Issues with vitis Environment
    It turns out the environment was much harder to get working than anticipated.
 * https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/issues/10
    Cannot be completed until issue 19 is resolved, due to interconnectivity.


## Code Files for Review
  None
 
## Retrospective Summary
Here's what went well:
  * The design phase for documentation went well, and the team has a good idea of how to approach development.
  * Transitioning to using Github for issue tracking has been working well for the team so far.

 
Here's what we'd like to improve:
   * Using Github better. It's great for work delegation and planning, but we're probably not usin it to its fullest extent
   * Getting the hardware set up correctly. We really can't move forward until this is improved!
   * Documenting as we go, it hasn't been bad but it's always good to improve on.
  
Here are changes we plan to implement in the next sprint:
   * Working environments with SOMs
   * Basic implementations running through SOM
   * Read data currently on the CPU stack

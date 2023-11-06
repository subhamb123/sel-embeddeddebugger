# Sprint x Report (10/05/23 - 11/05/2023)

## What's New (User Facing)
 * Board outputs stack and register values
 * Python script to read in values from serial port

## Work Summary (Developer Facing)
Provide a one paragraph synposis of what your team accomplished this sprint. Don't repeat the "What's New" list of features. Instead, help the instructor understand how you went about the work described there, any barriers you overcame, and any significant learnings for your team.
We created an exception handler that prints out the stack contents and register values through the serial port. The exception handler uses assembly code to access the register data. It also uses assembly code to integrate itself in the vector table. The exception handler gets called whenever an exception is thrown. The Python script uses pyserial to read in the information outputted by the exception handler. It handles both the stack and registers values. The next step is for it to generate TCL scripts to write the information back into the stack and registers.


## Unfinished Work
If applicable, explain the work you did not finish in this sprint. For issues/user stories in the current sprint that have not been closed, (a) any progress toward completion of the issues has been clearly tracked (by checking the checkboxes of  acceptance criteria), (b) a comment has been added to the issue to explain why the issue could not be completed (e.g., "we ran out of time" or "we did not anticipate it would be so much work"), and (c) the issue is added to a subsequent sprint, so that it can be addressed later.
We did not inmplement writing the information back to the board. That part is still unfinished. We ran out of time. It took longer than expected to get the exception handler integrated with the vector table. We will make sure it complete that part by the end of sprint 3.

## Completed Issues/User Stories
Here are links to the issues that we completed in this sprint:

 * URL of issue 1
 * URL of issue 2
 * URL of issue n

 Reminders (Remove this section when you save the file):
  * Each issue should be assigned to a milestone
  * Each completed issue should be assigned to a pull request
  * Each completed pull request should include a link to a "Before and After" video
  * All team members who contributed to the issue should be assigned to it on GitHub
  * Each issue should be assigned story points using a label
  * Story points contribution of each team member should be indicated in a comment
 
 ## Incomplete Issues/User Stories
 Here are links to issues we worked on but did not complete in this sprint:
 
 * URL of issue 1 <<One sentence explanation of why issue was not completed>>
 * URL of issue 2 <<One sentence explanation of why issue was not completed>>
 * URL of issue n <<One sentence explanation of why issue was not completed>>
 
 Examples of explanations (Remove this section when you save the file):
  * "We ran into a complication we did not anticipate (explain briefly)." 
  * "We decided that the feature did not add sufficient value for us to work on it in this sprint (explain briefly)."
  * "We could not reproduce the bug" (explain briefly).
  * "We did not get to this issue because..." (explain briefly)

## Code Files for Review
Please review the following code files, which were actively developed during this sprint, for quality:
 * [read_serial.py](https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/blob/dochoa-Debugger/debugger/read_serial.py)
 * [snapshot.h](https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/blob/dochoa-Debugger/workspace/TestProject/src/snapshot.h)
 * [snapshot.c](https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/blob/dochoa-Debugger/workspace/TestProject/src/snapshot.c)
 
## Retrospective Summary
Here's what went well:
  * Writing through the serial port
  * Item 2
  * Item x
 
Here's what we'd like to improve:
   * Consistency of reading in from the serial port
   * Item 2
   * Item x
  
Here are changes we plan to implement in the next sprint:
   * Item 1
   * Item 2
   * Item x
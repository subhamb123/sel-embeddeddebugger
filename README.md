# SEL Debugger

## A debugger for an integrated system

### A debugger for an integrated system meant for the KV-260 SOM

This project is to create a debugger for the KV-260 SOM for SEL that will take snapshots for debugginag and CPU restoration purposes.

### Additional information about the project

Computers are imperfect, and therefore we must account for this. Inevitably, system errors will occur, which can crash a system. 
An ability to reboot a system with as minimal of downtime as possible is critical. This project will allow for this, a restoration
system for when a system inevitably crashes. Additionally, this data stored can be used for debugging purposes, mitigating problems
in the future.

## Installation

### Prerequisites

Due to no deliverables for the hardware yet, instructions for running these are not provided yet until it can be fully sure of the requirements.

Hardware:
Xilinx Kria_KV260 Vision AI Starter Kit (SK-KV260-G)
XDS110 JTAG Debug Probe

Software:
GCC
git

### Add-ons

Currently: None

### Installation Steps
Note: This is only for the mockup of the UI.
Open a directory within your terminal to an empty folder

```
(clone repository)
git init
git clone https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger
cd sel-embeddeddebugger
gcc interface.c
./a.out
```

## Functionality
Basic mockup of the planned UI.

## Known Problems
Coming soon!

## Contributing
1. Fork it!
2. Create your feature branch: `git checkout -b my-new-feature`
3. Commit your changes: `git commit -am 'Add some feature'`
4. Push to the branch: `git push origin my-new-feature`
5. Submit a pull request :D

## Additional Documentation
Project Description - https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/blob/main/documents/SEL-EmbeddedDebugger-Project-Description.pdf
Project Requirements - https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/blob/main/documents/SEL-EmbeddedDebugger-Project-Requirements.pdf
Project Solution Approach - https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/blob/main/documents/SEL-EmbeddedDebugger-Project-Solution-Approach.pdf

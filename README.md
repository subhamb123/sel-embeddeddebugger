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

Hardware:
Xilinx Kria_KV260 Vision AI Starter Kit (SK-KV260-G)
XDS110 JTAG Debug Probe
A Windows PC

Software:
GCC
git
xilinx vitis
Python

### Add-ons

Currently: None

### Installation Steps
1.  Install xilinx vitis (https://www.xilinx.com/support/download.html). When installing, ensure devices for SoCs and UltraScale+ are included.
2.  Connect the SOM to the PC with both the mini USB port and JTAG debugger
3.  Ensure system can communicate with SOM by opening serial connection (for example, with putty)
4.  Create a new application project, for the KV260 platform using the following .xsa file (https://github.com/Xilinx/kria-vitis-platforms/tree/main/kv260)
5.  Create a 'hello, world' project, and debug this project to ensure SOM communication. This will be seen in a serial connection from step 3
6.  Clone main branch into workspace - ensure snapshot.c is included in the build.
7.  Run main.py, select desired menu option.

## Functionality
- Read stack data, register data from the SOM.
- Decode this stack data for its program counters and function names.
- Load stack data and register data back onto board

## Known Problems
- Currently, it is only able to load a single CPU core
- Automated testing needs to be implemented
- Some scripts still rely on hardcoded directories

## Contributing
1. Fork it!
2. Create your feature branch: `git checkout -b my-new-feature`
3. Commit your changes: `git commit -am 'Add some feature'`
4. Push to the branch: `git push origin my-new-feature`
5. Submit a pull request :D

## Additional Documentation
- [Project Description](https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/blob/main/documents/SEL-EmbeddedDebugger-Project-Description.pdf)
- [Project Requirements](https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/blob/main/documents/SEL-EmbeddedDebugger-Project-Requirements.pdf)
- [Project Solution Approach](https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/blob/main/documents/SEL-EmbeddedDebugger-Project-Solution-Approach.pdf)
- [Project Testing and Acceptance Criteria](https://github.com/WSUCptSCapstone-F23-S24/sel-embeddeddebugger/blob/main/documents/SELEmbeddedDebugger-TestingandAcceptance.pdf)

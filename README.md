# VirtualMachine2
This project is my second attempt at writing a virtual machine that reads bytecode and executes it. 
I've also written a "compiler" that can read some custom assembly language and emit vm2 bytecode; 
it is available in the [VirtualMachine2-Compiler](https://github.com/batburger/VirtualMachine2-Compiler) repository. 
That repository also includes a link to the "spec" of the virtual machine bytecode - it is incomplete, perhaps ambition and hubris 
got the better of me, but I figured I'd leave it in the original state. Despite this, the virtual machine itself is 
fully functional and can execute any algorithm. There is a third repository, [VirtualMachine2-Visualizer](https://github.com/batburger/VirtualMachine2-Visualizer) 
which is an interactive terminal programme which you can use to explore the VM's bytecode. 

## Dependencies
* Depends only on the C++17 standard library.

## Building
To build, clone this repository and run `cmake .` and `cmake --build .`.

# CSCE 412 Project 3
## Getting Started
### Cloning the Code
First, clone the repository to your preferred directory.
Then, ensure that you are in the root directory at CSCE412Project3 in your terminal.
### Execution
In order to compile the application, type:
`make clean; make`: [Cleans the build files and then recompiles with the executable]
`./outDebug`: Will run the executable.

You will get a few choices:
1. Number of cycles: Number of cycles that the load balancer will run for.
2. Number of servers: How many servers the load balancer is initialized with originally.
3. File name: If you want to log with different file names for different simulations.


### Documentation
In order to rebuild the Doxygen documentation, type `doxygen Doxyfile` in the root directory. 

The relevant files will be generated in a file named `html/`.

However, all documentation will be deployed to `412-project-3.vanessacodes.com` by default on commits to main, through GitHub Actions.
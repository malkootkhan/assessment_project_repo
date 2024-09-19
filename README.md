# Project Overview    
This project is a C++ application developed on Ubuntu 22.04 using the Vim editor. The code has been designed to be portable and has been tested on both Linux environments. It utilizes the CMake build system for easy configuration and compilation, and it automatically manages dependencies like the GoogleTest framework. C++ standard 20 is used.    

## Build Instructions    
### Linux Build Process    
To build the project on Linux, follow these steps. Ensure you have the necessary tools installed (g++, CMake, make), and that their paths are added to the system's environment variable.   
**1. clone the repository:**     
`git clone <repository_url>`      
`cd <repository_directory>`    

**2. Create a build directory and navigate into it:**    
`mkdir build`     
`cd build`    

**2. Run CMake to configure the project:**     
`cmake ..`     

**3. Compile the project:**     
`make`    

**4. Run Resulting Binary/executable (project_root/bin/queueExec):**    
`$(PROJECT_ROOT)/bin/queueExec`   

**5. Run all test cases:**    
`$(PROJECT_ROOT)/bin/test_queue`    

**6. OR run ctest in the test directory:**  
`$(PROJECT_ROOT)/build/test/ctest`   

ctest is a tool and part of Cmake used to automate the testing process 

**Notes:**      
The first build may take some time as it will download the required dependencies, such as GoogleTest framework.    
Once downloaded, the dependencies are placed in the appropriate directories for subsequent builds.    

## Additional Information      
### Dependencies   
GoogleTest: A C++ testing framework used to write unit tests for the code.   
These dependencies are automatically downloaded and configured during the build process.   

### IDE Compatibility   
Linux: Developed and tested using Vim. It should work with any modern text editor or IDE that supports C++.   


## Documentation and Doxygen Generation
**1. Install Doxygen:** First, ensure that Doxygen is installed on your Linux system by running the following command:
`sudo apt-get install doxygen`

2. **Generate Documentation:** No additional configuration is needed. Once Doxygen is installed, you can generate the documentation by running:   
`doxygen Doxyfile`     
This will generate the documentation in the format specified by the Doxyfile configuration.   

3. The above command will create html directory where you can find all the relevant documents generated in the html format

#### Contact     
If you have any questions or need further assistance, feel free to reach out via email at engr.mkhan1990@gmail.com.  





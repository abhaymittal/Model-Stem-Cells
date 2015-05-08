#Computational modeling of decision making in stem cells

####Authors: Abhay Mittal and Pratik Varshney

Language: C++

###Requirements for compilation and execution
1. Code::Blocks v13.12
2. For reading/writing XML files
    1. Required Packages (OS: Ubuntu 14.04)
       	   libxml++2.6-dev libxml++2.6-doc
       
    2. Add to Linker options in Code::Blocks:
       	   pkg-config --cf lags --libs libxml++-2.6
3. Doxygen v1.8.6
4. Netbeans v8.0
5. MATLAB R2012b
6. Paraview v4.3.1
7. graphviz v2.36.0

###Steps to build the project

1. To build the C++ code
   1. Open stem_cel.cbp in Code::Blocks v13.12, it will open the project in Code::Blocks.
   2. Build the project.

2. To build the GUI
   1. Open NetBeans IDE v8.0 and click on open project icon.
   2. Select the gui directory present in the project directory.
   3. Build the project.

### Steps to execute the project
1. To generate environment state and statistics files
   1. Open a terminal window in the project directory.
   2. Type the following command
      	   java -jar gui/dist/uscp.jar
   3. Enter the configuration values or load an existing configuration.
   4. Click on run program. (The environment statistics are stored in the log/ directory and the environment states are stored in the iterations/ directory)
   5. Exit.

2. To generate the plots from the statistics
   1. Open MATLABvR2012b and set the log/ directory as the working directory
   2. Enter the following command
      	    plotting
   3. The plots will be saved in the log/ directory

3. To generate the vizualization
   1. Open Paraview v4.3.1
   2. Open python shell in Paraview.
   3. Enter the following commands  
      (Change the <path to project dir> in the code below with the path of the project directory)
      ```
      import os
      os.chdir('<path to project dir>')
      execfile('uscp_sim.py')
      ```
   4. Enter the number of files you want to vizualize in the dialog box that pops up. The maximum value is the total number of iterations+1.
   5. The vizualization will be loaded.
   6. In Animation view, select Mode = Snap To TimeSteps.
   7. Click on File -> Save Animation.
   8. Select the desired settings.
   9. Save the video.


### Steps to generate the documentation
1. Open terminal in the project directory
2. Enter the following command
   	 doxygen comment_config
3. The html documentation will be generated in docs/html/ and the latex documentation will be generated in docs/latex/ directory.
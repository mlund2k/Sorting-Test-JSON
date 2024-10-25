# Sorting-Test-JSON


This program compares a few popular computational sort methods on JSON files to determine which methods perform best in varying scenarios.


This program was compiled using WSL (Windows Subsystem for Linux) on Windows 10 and 11 and runs perfectly in such environments.


**Steps to run:**
- Copy files into one directory, unzip ```P2_files.zip``` for examples to test on
- Set the location of the files as your directory with your terminal of choice
- Execute ```make``` to compile the project
- Execute ```./sortedverification sampleexample.json``` to determine whether the JSON file is numerically sorted and display JSON object information on the sorting status of the JSON. Other example JSONs besides sampleexample.json can be found in P2_files.
- Execute ```./consistentresultverification sampleexample.json almostsampleexample.json``` to compare the information stored in each JSON against each other, searching for mismathces and displaying other relevant information. Other example JSONs can be found in P2_files.
- Execute ```./timealgorithms sampleexample.json``` to perform a few popular sort methods on a JSON list of numeric values. Information on each sort such as time and comparisons are stored and exported in .csv format into ```output.csv```. Other example JSONs can be found in P2_files.


Credits for providing the sorting files (quicksort.cpp/h, mergesort.cpp/h, insertionsort.cpp/h) for this project:
```// Author: Rob Gysel```
```// ECS60, UC Davis```
```// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks```

If compiling raises a fatal error on ```#include <json/json.h>```, make sure to run the following commands to install json on your computer:
```sudo apt-get install libjsoncpp-dev```
```sudo ln -s /usr/include/jsoncpp/json/ /usr/include/json```
Credits: https://github.com/stardust95/TinyCompiler/issues/2#issuecomment-410946235

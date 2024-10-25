#include <iostream> // output library
#include <fstream> // file read library
#include <string>  // string library
#include <ctime> // time verification library
#include <vector> // vector library
#include <iomanip> // library for nicer looking decimals
#include "quicksort.h" // quicksort
#include "mergesort.h" // mergesort
#include "insertionsort.h" // insertion sort
#include "json.hpp" // json library
using namespace std; // namespace std

int main(int argc, char** argv) { // command line arguments
    if(argc != 2){ // check if incorrect amount of arguments
        cout << "Usage: ./timealgorithms [file_name].json" << endl; // output usage format
        return 0; // exit
    }

    ofstream output; // create output file
    output.open("output.csv"); // format output file to csv
    output << "Sample" << "," << "InsertionSortTime" << "," << "InsertionSortCompares" << ","; // creating columns
    output << "InsertionSortMemaccess" << "," << "MergeSortTime" << "," << "MergeSortCompares"; // creating columns
    output << "," << "MergeSortMemaccess" << "," << "QuickSortTime" << "," << "QuickSortCompares"; // creating columns
    output << "," << "QuickSortMemaccess" << endl; // creating columns
    output << fixed << showpoint << setprecision(6); // prevent scientific notation for readability

    ifstream f(argv[1]); // read in file from command line
    nlohmann::json data = nlohmann::json::parse(f); // parse the file
    for(int i=1;i<=data["metadata"]["numSamples"]; i++){ // loop over all samples
        vector<int> A; // define temporary copy vector
        string name; // used to keep track of sample name

        // this is really annoying to have to add, but since the sampleexample uses format "sample1"
        // and autograder examples use format "sample01", the program must predict the format
        if(data["metadata"]["numSamples"] < 10){ // if json contains single digit samples
            name = "Sample" + to_string(i); // create proper string name for json array
        }
        else{ // if json contains double digit samples
            if(i < 10){ // if current index is double digits
                name = "Sample0" + to_string(i); // create proper string name for json array of format sample0#
            }
            else{ // otherwise for single digit
                name = "Sample" + to_string(i); // create proper string name for json array
            }
        }

        output << name << ","; // read sample name to output file
        for(int j=0; j<data["metadata"]["arraySize"]; j++){ // loop over all indexes in each sample
            A.push_back(data[name][j]); // copy data to temp vector
        }

        int comparisons = 0; // define reference variable to keep track of comparisons
        int memaccess = 0; // define reference variable to keep track of memory accesses

        clock_t itime = clock(); // start timing insertion sort
        InsertionSort(&A, comparisons, memaccess); // perform insertion sort
        itime = clock() - itime; // stop timing insertion sort

        output << (float)itime/CLOCKS_PER_SEC << "," << comparisons << "," << memaccess << ","; // read insertionsort data to output

        for(int j=0; j<data["metadata"]["arraySize"]; j++){ // loop over all indexes in each sample
            A.at(j) = data[name][j]; // reset vector to sort again
        }
        comparisons = 0; // reset comparisons
        memaccess = 0; // reset memory accesses

        clock_t mtime = clock(); // start timing merge sort
        MergeSort(&A, comparisons, memaccess); // perform merge sort
        mtime = clock() - mtime; // stop timing merge sort

        output << (float)mtime/CLOCKS_PER_SEC << "," << comparisons << "," << memaccess << ","; // read mergesort data to output

        for(int j=0; j<data["metadata"]["arraySize"]; j++){ // loop over all indexes in each sample
            A.at(j) = data[name][j]; // reset vector to sort again
        }
        comparisons = 0; // reset comparisons
        memaccess = 0; // reset memory accesses

        clock_t qtime = clock(); // start timing quick sort
        QuickSort(&A, comparisons, memaccess); // perform quick sort
        qtime = clock() - qtime; // stop timing quick sort

        output << (float)qtime/CLOCKS_PER_SEC << "," << comparisons << "," << memaccess << endl; // read quicksort data to output
    }
    output.close(); // close the file

    string display; // define display string
    ifstream f2("output.csv"); // read in output file for display
    if(f2){ // while file has not been fully parsed
        while(getline(f2,display)){ // parse next line
            cout << display << endl; // display file to terminal for autograder
        }
    }

    return 0; //exit program
}

#include <iostream> // output library
#include <fstream> // file read library
#include <string>  // string library
#include "json.hpp" // json library
using namespace std; // namespace std

int main(int argc, char** argv){ // command line arguments
    if(argc != 2){ // check if incorrect amount of arguments
        cout << "Usage: ./sortedverification [file_name].json" << endl; // output usage format
        return 0; // exit
    }

    ifstream f(argv[1]); // read in file from command line
    nlohmann::json data = nlohmann::json::parse(f); // parse the file
    nlohmann::json output; // create output json value

    output["metadata"]["arraySize"] = data["metadata"]["arraySize"]; // copy arraysize to output
    output["metadata"]["numSamples"] = data["metadata"]["numSamples"]; // copy number of samples to output
    output["metadata"]["file"] = argv[1]; // copy file name to output
    
    int swi = 0; // samples with inversions counter
    for(int i=1; i<=data["metadata"]["numSamples"]; i++){ // loop through all sample arrays
        int inversions = 0; // counter for inversions per sample array
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
        
        for(int j=0; j+1 < data["metadata"]["arraySize"]; j++){ // loop through all indexes of sample array
            if(data[name][j] > data[name][j+1]){ // detects consecutive inversion
                inversions++; // increment inversions
                output[name]["ConsecutiveInversions"][to_string(j)][0] = data[name][j]; //copy first # of consecutive inversion to output
                output[name]["ConsecutiveInversions"][to_string(j)][1] = data[name][j+1]; //copy second # of consecutive inversion to output
                for(int l=0; l<data["metadata"]["arraySize"]; l++){ //loop over entire sample array
                    output[name]["sample"][l] = data[name][l]; // copy sample array to output
                }
                }
        }
        if(inversions > 0){ // detect samples with inversions
            swi++; // increment counter for samples with inversions
        }
    }
    output["metadata"]["samplesWithInversions"] = swi; // copy samples with inversions to output
    string str = output.dump(4); // dump output to string
    cout << str << endl; // display string as output
    return 0; // exit program
}
#include <iostream> // output library
#include <fstream> // file read library
#include <string>  // string library
#include "json.hpp" // json library
using namespace std; // namespace std

int main(int argc, char** argv){ // command line arguments
    if(argc != 3){ // check if incorrect amount of arguments
        cout << "Usage: ./sortedverification [file_name].json [file_name].json" << endl; // output usage format
        return 0; // exit
    }

    ifstream f1(argv[1]); // read in file 1 from command line
    nlohmann::json data1 = nlohmann::json::parse(f1); // parse file 1
    ifstream f2(argv[2]); // read in file 2 from command line
    nlohmann::json data2 = nlohmann::json::parse(f2); // parse file 2
    nlohmann::json output; // create output json value

    output["metadata"]["File1"]["arraySize"] = data1["metadata"]["arraySize"]; // copy arraysize of file 1 to output
    output["metadata"]["File2"]["arraySize"] = data2["metadata"]["arraySize"]; // copy arraysize of file 2 to output
    output["metadata"]["File1"]["numSamples"] = data1["metadata"]["numSamples"]; // copy number of samples from file 1 to output
    output["metadata"]["File2"]["numSamples"] = data2["metadata"]["numSamples"]; // copy number of samples from file 2 to output
    output["metadata"]["File1"]["name"] = argv[1]; // copy file 1 name to output
    output["metadata"]["File2"]["name"] = argv[2]; // copy file 2 name to output

    int con = 0; // conflicting sample counter
    for(int i=1; i <= data1["metadata"]["numSamples"]; i++){ // loop through sample arrays
        int mismatches = 0; // counter for mismatches per sample array
        string name; // used to keep track of sample name

        // this is really annoying to have to add, but since the sampleexample uses format "sample1"
        // and autograder examples use format "sample01", the program must predict the format
        if(data1["metadata"]["numSamples"] < 10){ // if json contains single digit samples
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
        for(int j=0; j < data1["metadata"]["arraySize"]; j++){ // loop through all indexes of each sample array
            if(data1[name][j] != data2[name][j]){ // detects conflicting entry
                mismatches++; // increment mismatches
                output[name]["Mismatches"][to_string(j)][0] = data1[name][j]; //copy file 1 mismatch to output
                output[name]["Mismatches"][to_string(j)][1] = data2[name][j]; //copy file 2 mismatch to output
                for(int k=0; k<data1["metadata"]["arraySize"]; k++){ //loop over entire sample array
                    output[name][argv[1]][k] = data1[name][k]; // copy array from file 1 to output
                    output[name][argv[2]][k] = data2[name][k]; // copy array from file 2 to output
                }
            }
        }

        if(mismatches > 0){ // detect mismatches
            con++; // increment counter for conflicing data
        }
    }

    output["metadata"]["samplesWithConflictingResults"] = con; // copy conflicting resutls count to output
    string str = output.dump(4); // dump output to string
    cout << str << endl; // display string as output
    return 0; //exit program
}
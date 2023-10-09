#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
  string filename = "";
  cout << "Input file name: ";
  getline(cin, filename);

  ifstream inputFile(filename);
  if ( not inputFile ) {
      cout << "Error: failed opening the file." << endl;
      return 1;
  }
  string outputFilename = "";
      cout << "Output file name: ";
      getline(cin, outputFilename);

      ofstream outputFile(outputFilename);
      if (!outputFile) {
          cout << "Error: Failed to open the output file." << endl;
          inputFile.close(); // Close the input file before exiting
          return 1; // Return an error code
      }

      string sum = "";
      string line;
      int i = 1;
      while ( getline(inputFile, line) ) {
          sum += to_string(i);
          sum += " ";
          sum += line;
          sum += "\n";
          i++;
      }
      inputFile.close();

      outputFile << sum; // Write the sum to the output file
      outputFile.close();

      return 0;
  }


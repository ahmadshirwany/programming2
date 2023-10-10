#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int main() {
    cout << "Input file: ";
    string input_file = "";
    getline(cin, input_file);

    ifstream input_object(input_file);

    if (!input_object) {
        cout << "Error! The file " << input_file << " cannot be opened." << endl;
        return EXIT_FAILURE;
    } else {
        string line;
        map<string, vector<int>> result;

        int line_number = 1;

        while (getline(input_object, line)) {
            string key = "";
            vector<int> numbers;
            numbers.push_back(1);
            numbers.push_back(line_number);

            for (auto cha : line) {
                if (cha == ' ') {
                    if (!result.empty() && result.find(key) != result.end()) {
                        if (find(result[key].begin(), result[key].end(), line_number) == result[key].end()) {
                            result[key][0]++;
                            result[key].push_back(line_number);
                        }
                    } else {
                        result[key] = numbers;
                    }

                    key = "";
                } else {
                    key += cha;
                }
            }

            if (!result.empty() && result.find(key) != result.end()) {
                if (find(result[key].begin(), result[key].end(), line_number) == result[key].end()) {
                    result[key][0]++;
                    result[key].push_back(line_number);
                }
            } else {
                result[key] = numbers;
            }

            line_number++;
        }

        for (const auto& pair : result) {
            cout << pair.first << ": ";
            for (size_t i = 1; i < pair.second.size(); i++) {
                cout << pair.second[i];
                if (i != pair.second.size() - 1) {
                    cout << ", ";
                }
            }
            cout << endl;
        }

        input_object.close();
        return EXIT_SUCCESS;
    }
}

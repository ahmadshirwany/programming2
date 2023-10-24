#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;
const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";


std::vector<std::string> split(const std::string& s,
                               const char delimiter,
                               bool ignore_empty = false)
{
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

void print_recusive(const std::string& key,   map<string, vector<string>> map_of_vectors, int times){
        for (int i = 0; i < times; i++) {
               std::cout << "..";
           }
        cout <<key<< endl;

        for (const std::string new_key: map_of_vectors[key]){
            if (map_of_vectors.count(key) > 0) {
                int t = times + 1 ;
                print_recusive(new_key, map_of_vectors, t);

            }

        }

}
void count(const std::string& key, const std::map<std::string, std::vector<std::string>>& map_of_vectors, int& network_count) {
    if (map_of_vectors.count(key) > 0) {
    for (const std::string& new_key : map_of_vectors.at(key)) { // Use const reference here
        if (map_of_vectors.count(new_key) > 0) {
            count(new_key, map_of_vectors, network_count);
        }
        network_count++;
    }
    }
}
int depth(const std::string& key, const std::map<std::string, std::vector<std::string>>& map_of_vectors, int depth_count) {
    if (map_of_vectors.count(key) > 0) {
    for (const std::string& new_key : map_of_vectors.at(key)) {
         if (map_of_vectors.count(new_key) > 0) {
            count(new_key, map_of_vectors, depth_count);
         }
     }

    }
    depth_count++;
   return depth_count;
}
int depth2(const std::string& key, const std::map<std::string, std::vector<std::string>>& map_of_vectors) {
    if (map_of_vectors.count(key) == 0) {
        return 0; // Base case: no further depth
    }

    int max_child_depth = 0;

    for (const std::string& new_key : map_of_vectors.at(key)) {
        int child_depth = depth2(new_key, map_of_vectors);
        if (child_depth > max_child_depth) {
            max_child_depth = child_depth;
        }
    }

    return 1 + max_child_depth; // Add 1 for the current level
}


int main()
{
    // TODO: Implement the datastructure here
       map<string, vector<string>> map_of_vectors;

    while(true)
    {
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        // Allowing empty inputs
        if(parts.size() == 0)
        {
            continue;
        }

        std::string command = parts.at(0);

        if(command == "S" or command == "s")
        {
            if(parts.size() != 3)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            // TODO: Implement the command here!
            map_of_vectors[parts.at(1)].push_back(parts.at(2));
        }
        else if(command == "P" or command == "p")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            print_recusive(id,map_of_vectors,0);

        }
        else if(command == "C" or command == "c")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            int network_count = 0;
            count(id,map_of_vectors,network_count);
            cout << network_count<<endl;

        }
        else if(command == "D" or command == "d")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);
            int depth_count = depth2(id,map_of_vectors);
//            int a = 0;
//            if (map_of_vectors.count(id) > 0) {
//            for (const std::string& new_key : map_of_vectors.at(id)) {
//                a = depth(new_key,map_of_vectors,0);
//                if(a>depth_count){
//                    depth_count = a;
//                }
//            }
//            }
            cout << depth_count+1<<endl;

            // TODO: Implement the command here!

        }
        else if(command == "Q" or command == "q")
        {
           return EXIT_SUCCESS;
        }
        else
        {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}

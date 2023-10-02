#include <iostream>
#include <string>
#include <vector>


// TODO: Implement split function here
// Do not change main function
std::vector<std::string> split(const std::string& line, char separator , bool check = false)
  {
   std::string obj = "";
   std::vector<std::string> new_vector ;
   for (size_t i = 0; i < line.length(); ++i) {
        char a =    line[i] ;
        if (a == separator){
            if (check==true ){
                if (obj != ""){

                new_vector.push_back(obj);
                obj = "";
                }
            }
             else{
                    new_vector.push_back(obj);
                    obj = "";
                }
            }

        else{
            obj += a;

        }
   }
   new_vector.push_back(obj);
   return new_vector;

}
int main(){
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}

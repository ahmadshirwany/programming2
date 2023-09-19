#include <iostream>
#include <string>
#include <cctype>

using namespace std;

const std::string KEY_LENGTH_ERROR = "Error! The encryption key must contain 26 characters.",
             KEY_CASE_ERROR = "Error! The encryption key must contain all alphabets a-z.",
             KEY_ALPHABET_ERROR = "Error! The encryption key must contain only lower case characters.";

const int KEY_LENGTH = 26;

bool check_key_length(std::string key)
{
    int key_length = key.length();

    return key_length == KEY_LENGTH;
}
bool check_key_lowercase (string key)
{
    for(char c : key)
    {
        if(!std::islower(c)){
            return false;
        }

    }
    return true;
}

bool check_key_alphabet(string key)
{
    //ASCII a=97, z=122
    for (int i = 97; i<=122;i++)
    {
        //convert ascii value to charecter
        char c = i;

        //check if key contains charecter
        if(key.find(c) == string::npos)
        {
            return false;
        }
    }
    return true;
}

bool check_key(string key)
{
    if(!check_key_length(key))
    {
        cout << KEY_LENGTH_ERROR << endl;
        return false;
    }
    if(!check_key_lowercase(key))
    {
        cout << KEY_CASE_ERROR << endl;
        return false;
    }
if (!check_key_alphabet(key))
{
    cout << KEY_ALPHABET_ERROR << endl;
    return false;
}
return true;
}




int main() {

        string encryptionKey = "abcdefghijklmnopqrstuvwzyx";
        string inputText = "thismessageisnotreallyencryptedtoomuch";

        // get user input

        cout << "Enter the encryption key: ";

        getline(std::cin, encryptionKey);

        if (!check_key(encryptionKey))
        {
            return EXIT_FAILURE;
        }

        if(!check_key_lowercase(encryptionKey))
        {
            cout << KEY_CASE_ERROR << endl;
            return EXIT_FAILURE;
        }

        cout << "Enter the text to be encrypted:";
        getline(cin, inputText);

    string encryptedText;

    // Create a mapping between characters in the input text and the encryption key
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    encryptedText = inputText; // Initialize encrypted text with the input text

    for (size_t i = 0; i < inputText.length(); ++i) {
        char c = inputText[i];
        if (isalpha(c)) {
            // Determine whether the character is uppercase or lowercase
            bool isUppercase = isupper(c);
            c = tolower(c); // Convert to lowercase for mapping

            // Find the index of the character in the alphabet
            size_t index = alphabet.find(c);

            // If the character is found in the alphabet, replace it with the corresponding character in the encryption key
            if (index != string::npos) {
                char replacementChar = encryptionKey[index];
                if (isUppercase) {
                    replacementChar = toupper(replacementChar);
                }
                encryptedText[i] = replacementChar;
            }
        }
    }

    // Output the encrypted text
    cout << "Encrypted text: " << encryptedText << endl;

    return 0;
}

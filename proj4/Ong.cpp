// Header goes here

#include "Cipher.h"
#include "Ong.h"
#include <istream>
#include <string>
#include <vector>
using namespace std;

//consts
const int UPPER = 2;
const int LOWER = 1;
const int NONLETTER = 0;

// helper function
int IsLetter(char letter);


// Name: Ong (Default Constructor)
// Desc: Constructor to build an empty Ong Cipher
// Preconditions - None
// Postconditions - Creates a Ong cipher to be encrypted
Ong::Ong(){};

// Name: Ong (Overloaded Constructor)
// Desc: Constructor to build a populated Ong Cipher
// Preconditions - Pass it the message and isEncrypted
// Postconditions - Creates a Ong cipher to be encrypted
Ong::Ong(string message, bool isEncypted):Cipher(message, isEncypted){};

// Name: Ong (Destructor)
// Desc: Destructor - Anything unique to Ong to delete?
// Preconditions - ~Ong exists
// Postconditions - Ong destroyed
Ong::~Ong(){};

// Name: IsVowel (Helper function)
// Desc: Returns true if vowel, space, or punctuation
// Preconditions - Message exists
// Postconditions - Returns true or false as above
// Notes:
// Leave the body blank
bool Ong::IsVowel(char isVowel){
    switch (isVowel){
    case 'A':
        return true;
    case 'a':
        return true;
    case 'E':
        return true;
    case 'e':
        return true;
    case 'I':
        return true;
    case 'i':
        return true;
    case 'O':
        return true;
    case 'o':
        return true;
    case 'U':
        return true;
    case 'u':
        return true;

    default:
        return false;
    }

    return true;
};

// Name: Encrypt
// Desc: If vowel then vowel and dash displayed. dog = dong-o-gong
// If consonant then consonant and ong and dash displayed.
// Preconditions - Message exists
// Postconditions - Encrypts as above
void Ong::Encrypt(){

    string decryptMessage = GetMessage();
    string hyphenMessage;
    string encryptMessage;

    // add dashes in between each letter of word
    for (long unsigned i = 0; i < decryptMessage.size(); i++){
        char currLetter = decryptMessage[i];

        // copy first char to new message
        if (i == 0){
            hyphenMessage.push_back(currLetter);

        // edit every letter in word to contain dash inbetween 
        } else{
            char prevLetter = decryptMessage[i-1];
            
            // if previous and current char are letters
            if (IsLetter(prevLetter) && IsLetter(currLetter)){
                hyphenMessage.push_back('-');
                hyphenMessage.push_back(currLetter);
            // otherwise copy char to new message
            } else{
                hyphenMessage.push_back(currLetter);
            }
        }
    }

    // add "ong" after every consonent in word
    for (long unsigned i = 0; i < hyphenMessage.size(); i++){
        char currLetter = hyphenMessage[i];

        // copy first letter in new hyphenated message
        if (i == 0){
            encryptMessage.push_back(currLetter);

        // edit every letter in word to contain ong after consonant
        } else{
            char prevLetter = hyphenMessage[i-1];
            
            // if previous char is a consonant and letter, and current 
            // char is a dash: add "ong-"
            if (!IsVowel(prevLetter) && IsLetter(prevLetter) 
                && currLetter == '-'){
                encryptMessage.push_back('o');
                encryptMessage.push_back('n');
                encryptMessage.push_back('g');
                encryptMessage.push_back('-');
            
            // if previous char is a consonant and letter:
            //  add "ong"
            } else if (!IsVowel(prevLetter) && IsLetter(prevLetter)
                && currLetter == ' '){
                encryptMessage.push_back('o');
                encryptMessage.push_back('n');
                encryptMessage.push_back('g');
                encryptMessage.push_back(' ');
            
            // otherwise just copy char to new message
            } else{
                encryptMessage.push_back(currLetter);
            }
        }
    }

    SetMessage(encryptMessage);
};

// Name: Decrypt
// Desc: Removes the dashes and "ong" when necessary cong-a-tong = cat
// Preconditions - Message exists
// Postconditions - Original message is displayed
void Ong::Decrypt(){

    string decryptMessage = GetMessage();
    string hyphenMessage;
    string encryptMessage;

    // delete dashes in between each letter of word
    for (long unsigned i = 0; i < decryptMessage.size(); i++){
        char currLetter = decryptMessage[i];

        // copy first char to new message
        if (i == 0){
            hyphenMessage.push_back(currLetter);

        // edit every letter in word to contain dash inbetween 
        } else{
            char prevLetter = decryptMessage[i-1];
            
            // if previous and current char are letters
            if (IsLetter(prevLetter) && IsLetter(currLetter)){
                hyphenMessage.push_back('-');
                hyphenMessage.push_back(currLetter);
            // otherwise copy char to new message
            } else{
                hyphenMessage.push_back(currLetter);
            }
        }
    }

    // delete "ong" after every consonent in word
    for (long unsigned i = 0; i < encryptMessage.size(); i++){
        char currLetter = encryptMessage[i];

        // copy first letter in new hyphenated message
        if (i == 0){
            decryptMessage.push_back(currLetter);

        // edit every letter in word to contain ong after consonant
        } else{
            char prevLetter = encryptMessage[i-1];
            
            // if previous char is a consonant and letter, and current 
            // char is a dash: add "ong-"
            if (!IsVowel(prevLetter) && IsLetter(prevLetter) 
                && currLetter == '-'){
                decryptMessage.pop_back();
                decryptMessage.pop_back();
                decryptMessage.pop_back();
                decryptMessage.pop_back();
            
            // if previous char is a consonant and letter:
            //  add "ong"
            } else if (!IsVowel(prevLetter) && IsLetter(prevLetter)
                && currLetter == ' '){
                decryptMessage.pop_back();
                decryptMessage.pop_back();
                decryptMessage.pop_back();
                decryptMessage.pop_back();
            
            // otherwise just copy char to new message
            } else{
                decryptMessage.push_back(currLetter);
            }
        SetMessage(decryptMessage);
        }
    }
};


// Name: ToString
// Desc - A function that returns the string of the object type
// Preconditions - The object exists
// Postconditions - The subtype is returned (Ong in this case)

// Notes:
// isn't much different than encrypt. i found it easiest to have an inMessage.
// You can also use a counter to skip letters if you want. 
string Ong::ToString(){
    return "(Ong)";
};

// Name: FormatOutput()
// Desc - A function that returns the formatted output for Output function
// Preconditions - The object exists (use stringstream)
// Postconditions - o, delimiter, isencrypted, delimiter,
// message, delimiter, blank are output
string Ong::FormatOutput(){

    stringstream ss;
    ss << 'o' << "|" << GetIsEncrypted()
    << "|" << GetMessage()
    << "|" << endl;

    return ss.str();
};

// helper function to check if char is upper, lower, or neither
int IsLetter(char letter){
  if (letter >= 'A' && letter <= 'Z'){
    return UPPER;
  } else if (letter >= 'a' && letter <= 'z'){
    return LOWER;
  } else{
    return NONLETTER;
  }
};
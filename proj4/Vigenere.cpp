// Header goes here

#include "Cipher.h"
#include "Vigenere.h"
#include <istream>
#include <string>
using namespace std;

// Name: Vigenere (Default Constructor)
// Desc: Constructor to build an empty Vigenere Cipher (Defaults key to "test")
// Preconditions - None
// Postconditions - Creates a Vigenere cipher to be encrypted
Vigenere::Vigenere(){};
// Name: Vigenere (Overloaded Constructor)
// Desc: Constructor to build a populated Vigenere Cipher
// Preconditions - Pass it the message, isEncrypted, and key
// Postconditions - Creates a Vigenere cipher to be encrypted
Vigenere::Vigenere(string message, bool isEncrypted, string key):Cipher(message, isEncrypted){
    m_key = key;
};
// Name: Vigenere (Destructor)
// Desc: Destructor - Anything specific to delete in Vigenere?
// Preconditions - ~Vigenere exists
// Postconditions - Vigenere destroyed
// Notes:
// Leave the body blank
Vigenere::~Vigenere(){};

// Name: Encrypt
// Desc: Encrypts using key (See project document for details)
// Preconditions - Message exists
// Postconditions - Encrypts using key
void Vigenere::Encrypt(){

string decryptMessage = GetMessage();
string encryptMessage;
string key = m_key;

// counter 
int j = 0;

for (long unsigned i = 0; i < decryptMessage.size(); i++) { 
    // check upper case
    if( decryptMessage[i] >= 'A' && decryptMessage[i] <= 'Z'){   
        // converting in range 0-25 
        int x = (decryptMessage[i]-'A' + key[j%key.size()]-'a') %26; 

        // convert into alphabets(ASCII) 
        x += 'A'; 
        // concatenate
        encryptMessage += x;
        // increment counter
        j++;
    } else if(decryptMessage[i] >= 'a' && decryptMessage[i] <= 'z'){   
        // converting in range 0-25 
        int x = (decryptMessage[i]-'a' + key[j%key.size()]-'a') %26; 

        // convert into alphabets(ASCII) 
        x += 'a'; 

        encryptMessage += x; 
        j++;
    } else {
        encryptMessage += decryptMessage[i];
    }
}
SetMessage(encryptMessage);
};

// // Name: Decrypt
// // Desc: Decrypts using key (See project document for details)
// // Preconditions - Message exists
// // Postconditions - Uses key to decrypt.
void Vigenere::Decrypt(){
    string encryptMessage = GetMessage();
    string decryptMessage = "";
    string key = m_key;

    // counter for key
    int j = 0;

    for (int i = 0; i < encryptMessage.size(); i++){
        // each letter in message
        char letter = encryptMessage.at(i);
        // lower case letter in message
        if (letter >= 'a' && letter <= 'z'){
            // convert letter to range 0-25
            letter = (letter - key[j%key.size()] + 26) %26;
            // convert letter back to it's ASCII value
            int message = letter += 'a';
            // concatenate letter to message
            decryptMessage += message;
            // increment key counter
            j++;
        } else if (letter >= 'A' && letter <= 'Z'){
            // convert letter to range 0-25
            letter = ((tolower(letter)) - key[j%key.size()] + 26) %26;
            // convert letter back to it's ASCII value
            int message = letter += 'A';
            // concatenate letter to message (need to add 6 for some reason)
            decryptMessage += message;
            // increment key counter
            j++;        
        } else{
            // letter is not a letter so don't change
            decryptMessage += letter;
        }
    SetMessage(decryptMessage);
    }
};

// Name: ToString
// Desc - A function that returns the string of the object type
// Preconditions - The object exists
// Postconditions - The subtype is returned (Vigenere in this case)
string Vigenere::ToString(){
    return "(Vigenere)";
};

// Name: FormatOutput()
// Desc - A function that returns the formatted output for Output function
// Preconditions - The object exists (use stringstream)
// Postconditions - v, delimiter, isencrypted, delimiter,
// message, delimiter, key are returned for output
string Vigenere::FormatOutput(){

    stringstream ss;
    
    ss << 'v' << "|" << GetIsEncrypted()
    << "|" << GetMessage()
    << "|" << m_key
    << endl;

    return ss.str();
};

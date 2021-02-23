#include "Caesar.h"
#include "Cipher.h"

// Name: Caesar (Default Constructor)
// Desc: Constructor to build an empty Caesar Cipher (Defaults to shift 3)
// Preconditions - None
// Postconditions - Creates a Caesar cipher to be encrypted
Caesar::Caesar(){
    m_shift = 3; // default is 3
};

// Name: Caesar (Overloaded Constructor)
// Desc: Constructor to build a populated Caesar Cipher (Defaults to shift 3)
// Preconditions - Pass it the message, isEncrypted, and shift (any integer)
// Postconditions - Creates a Caesar cipher to be encrypted
Caesar::Caesar(string message, bool isEncrypted, int shift):Cipher(message, isEncrypted){
    m_shift = shift;
};

// Name: Caesar (Destructor)
// Desc: Destructor - Anything specific to Caesar to delete?
// Preconditions - ~Caesar exists
// Postconditions - Caesar destroyed
// Notes:
// Leave the body blank
Caesar::~Caesar(){};

// Name: Encrypt
// Desc: Shifts characters right based on shift (lower stay lower, upper stay upper)
// Preconditions - Message exists
// Postconditions - Shifts each character "right".
void Caesar::Encrypt(){
    
    string decryptMessage = GetMessage(), encryptMessage = "";
    int shift = m_shift;
    // difference - (ASCII value + shift)- ASCII UpperBound
    int difference;
    // sum - difference + ASCII LowerBound
    int sum;
    
    // lower = 97 <-> 122
    int lowerCaseUpperBound = 'z';
    int lowerCaseLowerBound = 'a';

    // upper = 65 <-> 90
    int upperCaseUpperBound = 'Z';
    int upperCaseLowerBound = 'A';
  
    for (long unsigned i = 0; i < decryptMessage.size(); i++){        
        if (decryptMessage.at(i) <= 'A' && decryptMessage.at(i) <= 'Z'){
            encryptMessage += int(decryptMessage.at(i));
        } else if (isupper(decryptMessage.at(i)) &&
        decryptMessage.at(i)+shift > upperCaseUpperBound){
            difference = (decryptMessage.at(i)+shift)-upperCaseUpperBound;
            sum = difference + upperCaseLowerBound;
            encryptMessage += sum-1;
        } else if (islower(decryptMessage.at(i)) &&
        decryptMessage.at(i)+shift > lowerCaseUpperBound){
            difference = (decryptMessage.at(i)+shift)-lowerCaseUpperBound;
            sum = difference + lowerCaseLowerBound;
            encryptMessage += sum-1;
        } else {
            encryptMessage += int(decryptMessage.at(i))+shift;
        }
    }
    SetMessage(encryptMessage);
};  

// Name: Decrypt
// Desc: Shifts characters left based on shift (lower stay lower, upper stay upper)
// Preconditions - Message exists
// Postconditions - Shifts each character "left".
void Caesar::Decrypt(){
    string decryptMessage = GetMessage(), encryptMessage = "";
    int shift = m_shift;
    // difference - (ASCII value + shift)- ASCII UpperBound
    int difference;
    // sum - difference + ASCII LowerBound
    int sum;
    
    // lower = 97 <-> 122
    int lowerCaseUpperBound = 122;
    int lowerCaseLowerBound = 97;

    // upper = 65 <-> 90
    int upperCaseUpperBound = 90;
    int upperCaseLowerBound = 65;
  
    for (long unsigned i = 0; i < decryptMessage.size(); i++){        
        if (decryptMessage.at(i) == ' ' || decryptMessage.at(i) == '"' ||
        decryptMessage.at(i) == ',' || decryptMessage.at(i) == '.' ||
        decryptMessage.at(i) == '(' || decryptMessage.at(i) == ')' ||
        decryptMessage.at(i) == '\''){
            encryptMessage += int(decryptMessage.at(i));
        } else if (isupper(decryptMessage.at(i)) &&
        decryptMessage.at(i)-shift < upperCaseLowerBound){
            difference = decryptMessage.at(i)-upperCaseLowerBound;
            sum = upperCaseUpperBound - difference;
            encryptMessage += sum;
        } else if (islower(decryptMessage.at(i)) &&
        decryptMessage.at(i)-shift < lowerCaseLowerBound){
            difference = decryptMessage.at(i)-lowerCaseLowerBound;
            sum = lowerCaseUpperBound - difference;
            encryptMessage += sum;
        } else{
            encryptMessage += int(decryptMessage.at(i))-shift;
        }
    }
    SetMessage(encryptMessage);
};

// Name: ToString
// Desc - A function that returns the string of the object type
// Preconditions - The object exists
// Postconditions - The subtype is returned (Caesar in this case)
string Caesar::ToString(){
    return "(Caesar)";
}

// Name: FormatOutput()
// Desc - A function that returns the formatted output for Output function
// Preconditions - The object exists (use stringstream)
// Postconditions - c, delimiter, isencrypted, delimiter,
// message, delimiter, m_shift are returned for output
string Caesar::FormatOutput(){

    stringstream ss;
    ss << 'c' << "|" << GetIsEncrypted()
    << "|" << GetMessage()
    << "|" << m_shift
    << endl;

    return ss.str();
};
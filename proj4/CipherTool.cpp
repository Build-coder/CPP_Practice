
//Title: CipherTool.cpp
//Author: Phil Wood
//Date: 3/30/2020
//Description: This is part of the Cipher Project in CMSC 202 @ UMBC
#include <iostream>
#include "CipherTool.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>      //Used to format output for each subtype for output
using namespace std;

// helper function
void EncryptedDisplay(bool isEncrypted);

// Name: CipherTool Constructor
// Desc - Creates a new CipherTool and sets m_filename based on string passed
// Preconditions - Input file passed and populated with Cipher
// Postconditions - CipherTool created
CipherTool::CipherTool(string filename){
  m_filename = filename;
};

// Name: CipherTool Destructor
// Desc - Calls destructor for all ciphers in m_ciphers
// Preconditions - m_ciphers is populated
// Postconditions - m_ciphers emptied
CipherTool::~CipherTool(){
  for (long unsigned i = 0; i < m_ciphers.size(); i++){
    delete m_ciphers[i];
    m_ciphers[i] = nullptr;
  }
};

// Name: LoadFile
// Desc - Opens file and reads in each Cipher. Each Cipher dynamically allocated
// and put into m_ciphers
// Preconditions - Input file passed and populated with Ciphers
// Postconditions - m_ciphers populated with Ciphers
void CipherTool::LoadFile(){
  char cipherType;
  string message, keyword;
  int shift;
  bool isEncrypted;

  ifstream file(m_filename);

    while (file >> cipherType){
      file.ignore(256, DELIMITER);
      file >> isEncrypted;
      file.ignore(256, DELIMITER);
      getline(file, message, DELIMITER);

      if (cipherType == 'c'){
        file >> shift;
        Cipher* cipherPtr = new Caesar(message, isEncrypted, shift);
        m_ciphers.push_back(cipherPtr);

      } else if (cipherType == 'v'){
        file >> keyword;
        Cipher* cipherPtr = new Vigenere(message, isEncrypted, keyword);
        m_ciphers.push_back(cipherPtr);

      } else{
        Cipher* cipherPtr = new Ong(message, isEncrypted);
        m_ciphers.push_back(cipherPtr); 
      }
    }
  
  file.close();
};

// Name: DisplayCiphers
// Desc - Displays each of the ciphers in the m_ciphers
// Preconditions - Input file passed and m_ciphers populated
// Postconditions - Displays ciphers
void CipherTool::DisplayCiphers(){
  int count = 1;

  for (long unsigned i = 0; i < m_ciphers.size(); i++){
    cout << count << ".) " << *m_ciphers.at(i);
    
    count++;
  }
  cout << endl;
};

// Name: EncryptDecrypt
// Desc - Encrypts or decrypts each of the ciphers in the m_ciphers
// Preconditions - Input file passed and m_ciphers populated
// Postconditions - Either Encrypts or Decrypts each cipher in m_ciphers
void CipherTool::EncryptDecrypt(bool isEncrypted){

  for (long unsigned i = 0; i < m_ciphers.size(); i++){
    // if encrypted -> decrypt
    if (isEncrypted == 1){
      if (m_ciphers.at(i)->GetIsEncrypted()){
        m_ciphers.at(i)->Decrypt();
        m_ciphers.at(i)->ToggleEncrypted();
      }
    } else {
      // if decrypted -> encrypt
      if (!m_ciphers.at(i)->GetIsEncrypted()){
        m_ciphers.at(i)->Encrypt();
        m_ciphers.at(i)->ToggleEncrypted();
      }
    }
  }

// helper function to output encryption status of all ciphers
EncryptedDisplay(isEncrypted);
};

// Name: Export
// Desc - Exports each of the ciphers in the m_ciphers (so they can be reused)
// Preconditions - Input file passed and m_ciphers populated
// Postconditions - All ciphers exported
void CipherTool::Export(){
  
  ofstream myfile;
  string exportFile;
  int count;

  cout << "What would you like to call the export file? "
  << endl;

  cin >> exportFile;

  myfile.open(exportFile);

  for (int i = 0; i < int(m_ciphers.size()); i++){
    myfile << m_ciphers[i]->FormatOutput();
    count = i+1;
  }

  cout << endl << count << " ciphers have been exported to "
  << exportFile << endl << endl;;

  myfile.close();

}

// Name: Menu
// Desc - Displays menu and returns choice
// Preconditions - m_ciphers all populated
// Postconditions - Returns choice
int CipherTool::Menu(){
  int choice;

  cout << "1. Display All Ciphers"
  << endl << "2. Encrypt All Ciphers"
  << endl << "3. Decrypt All Ciphers"
  << endl << "4. Export All Ciphers"
  << endl << "5. Quit" << endl;
  cin >> choice;

  return choice;
};

// Name: GetType
// Desc - Pass it a cipher and it returns the char of the subtype
// Returns c for Caesar, v for Vigenere, and o for Ong
// Preconditions - m_ciphers all populated
// Postconditions - Returns char of type
char CipherTool::GetType(Cipher* cipher){
  for (long unsigned i = 0; i < m_ciphers.size(); i++){
    if (cipher->ToString() == "Caesar"){
      return 'c';
    } else if (cipher->ToString() == "Vigenere"){
      return 'v';
    } else if (cipher->ToString() == "Ong"){
      return 'o'; 
    }
  }

  return 0;
}

// Name: Start
// Desc - Loads input file, allows user to choose what to do
// Preconditions - m_ciphers populated with ciphers
// Postconditions - none
void CipherTool::Start(){
  bool endLoop = false;
  LoadFile();

while (endLoop == false){
  switch (Menu()){
    case 1:
      CipherTool::DisplayCiphers();
      break;
    case 2:
      CipherTool::EncryptDecrypt(DECRYPTED);
      break;
    case 3:
      CipherTool::EncryptDecrypt(ENCRYPTED);
      break;
    case 4:
      CipherTool::Export();
      break;
    case 5:
      endLoop = true;
      break;
    default:
      cout << "Enter a valid number" << endl;
      break;
  }
}
};

// helper function to output status of all ciphers
void EncryptedDisplay(bool isEncrypted){
  isEncrypted ? cout << "All ciphers are decrypted" << 
  endl << endl : cout << "All ciphers are encrypted" << 
  endl << endl;
};


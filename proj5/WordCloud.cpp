//Title: WorldCloud.cpp
//Author: Jeremy Dixon / Phil Wood
//Date: 4/20/2020
//Description: Implementation of functions in WordCloud.h

#include "WordCloud.h"
#include <string>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// Name: WordCloud (Default Constructor)
// Desc: Used to pass an essay (in input file) and generates word list and frequency
//       Dynamically allocates m_cloud. m_fileName would be hardcoded.
// Preconditions: Input file has correctly formatted input
// Postconditions: Returns list of items and their frequency (stored in LL)
WordCloud::WordCloud(){

  // dynamically allocates m_cloud
  m_cloud = new LL<string>();

  // m_fileName is hardcoded
  m_fileName = "proj5_test1.txt";

}

// Name: WordCloud (Overloaded Constructor) - Passed filename for input
// Desc: Used to pass an essay (in input file) and generates word list and frequency
//       Dynamically allocates m_cloud
// Preconditions: Input file has correctly formatted input
// Postconditions: Returns list of items and their frequency (stored in LL)
WordCloud::WordCloud(string file){

  // dynamically allocates m_cloud
  m_cloud = new LL<string>();

  // m_fileName is softcoded
  m_fileName = file;

}

// Name: ~WordCloud (Destructor)
// Desc: Deallocates m_cloud
// Preconditions: m_cloud has been dynamically allocated
// Postconditions: m_cloud is empty
WordCloud::~WordCloud(){

  // deallocates m_cloud
  delete m_cloud;
  m_cloud = nullptr;
}

// Name: LoadFile()
// Desc: Loads a file (everything as a string although could be anything stringlike)
//       Each input file is an unknown length
// Preconditions: m_fileName is populated with good data
// Postconditions: m_cloud is populated
void WordCloud::LoadFile()
{
  string str = "";

  ifstream file(m_fileName);

  while (file >> str)
  {
    str = m_cloud->ToLowerString(str);
    RemovePunct(str);

    m_cloud->Insert(str);
  }

  file.close();
}

// Name: RemovePunct (passed a string
// Desc: When passed a string, removes all non letter punctation on the beginning
//       or end of the string.
//       These are all ok: "don't" "inner-circle" but "candy," is bad
//       Is called during LoadFile
// Preconditions: Strings to be evaluated
// Postconditions: Punctuation is removed from string
void WordCloud::RemovePunct(string& word){

  int i = 0; // char counter
  
  // erase all punc until first letter
  for (string::iterator it = word.begin(); it != word.end(); ++it){
    
    if (m_cloud->IsLetter(*it) || m_cloud->IsNumber(*it)){
      word.erase(0, i);
      break;
    }

    ++i;
  }

  i = word.size(); // char counter (reverse)

  // erase all punc after last letter
  for (string::reverse_iterator iter = word.rbegin(); iter != word.rend(); ++iter){
    
    if (m_cloud->IsLetter(*iter) || m_cloud->IsNumber(*iter)){

      if (i < int(word.size())){
        word.erase(i, word.size());
      }
      
      return;
    }

    --i;
  }
}

// Name: RemoveCommon
// Desc: Iterates through m_cloud and removes all common words after they are read
// Preconditions: m_cloud is populated and EXCLUDE_LIST is populated
// Postconditions: m_cloud will have no words from EXCLUDE_LIST
void WordCloud::RemoveCommon(){

  for (vector<string>::const_iterator it = EXCLUDE_LIST.begin(); it != EXCLUDE_LIST.end(); ++it){
    m_cloud->RemoveAt(*it);
  }
}

// Name: RemoveSingles
// Desc: Asks the user if they would like to remove words with a frequency of 1
//       Should use the overloaded [] NOTE: Don't forget m_cloud is a pointer!
// Preconditions: m_cloud is populated
// Postconditions: m_cloud will have no words with a frequency of 1
void WordCloud::RemoveSingles(){

  string response;
  int count = 0;

  cout << "Would you like to remove words with a frequency of 1 from list" << endl;
  // cin >> response;
  // response = m_cloud->ToLowerString(response);
  response = "yes";

  if (response == "yes" || response == "y")
  {
    for (size_t i = 0; i < m_cloud->GetSize(); i++)
    {
      if (count == 1)
      {
        i = 0;
      }
      
      if ((*m_cloud)[i].second == 1)
      {
        m_cloud->RemoveAt((*m_cloud)[i].first);
        i = 0;
      }

      ++count;
    }
  }

  else return;
}

// Name: Export
// Desc: Iterates through m_cloud and exports to file "data:frequency"
// Preconditions: m_cloud is populated
// Postconditions: New export file is created with "data:frequency" one on each line
void WordCloud::Export(){

  ofstream myfile;
  string exportFile;
  int count = 0;

  cout << "\nWhat would you like to call the export file? "
  << endl;

  cin >> exportFile;

  myfile.open(exportFile);

  for (int i = 0; i < m_cloud->GetSize(); i++)
  {
    myfile << m_cloud->operator[](i).first
    << ":" << m_cloud->operator[](i).second
    << endl;
    
    ++count;
  }

  cout << endl << count << " unique words exported to "
  << exportFile << endl << endl;;

  myfile.close();

}

// Name: Start
// Desc: Calls LoadFile, RemoveCommon, Diplay, and Export 
// Preconditions: None (filename is available)
// Postconditions: None
void WordCloud::Start(){

LoadFile();
RemoveCommon();
cout << "\nDisplay after remove common words: " << endl;
m_cloud->Display();
RemoveSingles();
Export();
}
/***************************************************************************
* nameservercpp  -  Program to serve of last name statistics
 *
* copyright : (C) 2009 by Jim Skon
*
* This program runs as a background server to a CGI program, providinging US Census
* Data on the frequency of names in response to requestes.  The rational for this 
* is to demonstrait how a background process can serve up information to a web program,
* saving the web program from the work of intiallizing large data structures for every
* call.
* 
* 
*
***************************************************************************/
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <string>
#include <vector>
#include <ostream>
#include "fifo.h"

using namespace std;


class dataFromWebPage
{
	public: 
	dataFromWebPage(string inputted);
	string returnOutMessage();
	string returnText();
	
	private:
	
	string returnUsername();
	string returnColor();
	string returnPicture();
	// string returnText();
	string censorText();
		string originalInput, outPut, username, color, picture, text;
	friend void find_and_replace(string& source, string const& find, string const& replace);
	
};
// precon: 
//postcon: 
void find_and_replace(string& source, string const& find, string const& replace)
{
    for(string::size_type i = 0; (i = source.find(find, i)) != string::npos;)
    {
        source.replace(i, find.length(), replace);
        i += replace.length();
    }
}

	string dataFromWebPage :: censorText ()
	{
		//string censoredText = text;
		//replace(0, text.size(), "fuck", "****");
		//return censoredText;
		find_and_replace(text, "fuck", "****");
	}

   dataFromWebPage:: dataFromWebPage(string inputted)
 {
	 originalInput = inputted;
	 cout << "working: " << originalInput << endl; 
	 returnText();
	 string returnUsername();
	string returnColor();
	string returnPicture();
	 
 };
 
  string dataFromWebPage:: returnUsername()
 {
	 /*
	 1. find $USERNAME*
	 2. find next *
	 3. find next $
	 4. substr(*,$)
	 5. cout substr
	 */
	 
	 int tagPosition, startPosition, endPosition;
	 //string username;
	 
	 tagPosition = originalInput.find("$USERNAME*");
	 if (tagPosition == -1)
	 {
		 cout << "error 1" << endl;
		 return "error";
	 }
	 startPosition = originalInput.find("*", tagPosition);
	  //cout << originalInput.at(startPosition) << endl;
	 startPosition++;
	
	 endPosition = originalInput.find("$", startPosition);
	//endPosition--;
	//endPosition = 
	endPosition = endPosition - startPosition;
	 	  cout << originalInput.at(endPosition) << endl;
	 username = originalInput.substr(startPosition, endPosition);
	 return username;
 };
 
  string dataFromWebPage:: returnColor()
 {
	 /*
	 1. find $USERNAME*
	 2. find next *
	 3. find next $
	 4. substr(*,$)
	 5. cout substr
	 */
	 
	 int tagPosition, startPosition, endPosition;
	 //string color;
	 
	 tagPosition = originalInput.find("$COLOR*");
	 if (tagPosition == -1)
	 {
		 cout << "error 2" << endl;
		 return "error";
	 }
	 startPosition = originalInput.find("*", tagPosition);
	  cout << originalInput.at(startPosition) << endl;
	 startPosition++;
	 
	 endPosition = startPosition;
	cout << "1end: " << endPosition << endl;
	
	/*
	while (1)
	{
		endPosition++;
		if (originalInput.at(endPosition) == '$')
		{
		break;
		}
		cout << "sploop: " << originalInput.at(endPosition) << endl;
	}
	*/
	endPosition = originalInput.find("$", startPosition);
	endPosition = endPosition - startPosition;
	cout << "end: " << endPosition << endl;
	
	 	  //cout << originalInput.at(endPosition) << endl;
	 color = originalInput.substr(startPosition, endPosition);
	 return color;
 };
 
  string dataFromWebPage:: returnPicture()
 {
	 /*
	 1. find $USERNAME*
	 2. find next *
	 3. find next $
	 4. substr(*,$)
	 5. cout substr
	 */
	 
	 int tagPosition, startPosition, endPosition;
	 
	 
	 tagPosition = originalInput.find("$PICTURE*");
	 if (tagPosition == -1)
	 {
		 cout << "error 3" << endl;
		 return "error";
	 }
	 startPosition = originalInput.find("*", tagPosition);
	  cout << originalInput.at(startPosition) << endl;
	 startPosition++;
	 
	 endPosition = startPosition;
	cout << "1end: " << endPosition << endl;
	
	/*
	while (1)
	{
		endPosition++;
		if (originalInput.at(endPosition) == '$')
		{
		break;
		}
		cout << "sploop: " << originalInput.at(endPosition) << endl;
	}
	*/
	endPosition = originalInput.find("$", startPosition);
	endPosition = endPosition - startPosition;
	cout << "end: " << endPosition << endl;
	
	 	  //cout << originalInput.at(endPosition) << endl;
	 picture = originalInput.substr(startPosition, endPosition);
	 return picture;
 };
 
  string dataFromWebPage:: returnText()
 {
	 /*
	 1. find $USERNAME*
	 2. find next *
	 3. find next $
	 4. substr(*,$)
	 5. cout substr
	 */
	 
	 int tagPosition, startPosition, endPosition;
	
	 
	 tagPosition = originalInput.find("$TEXT*");
	 if (tagPosition == -1)
	 {
		 cout << "error 4" << endl;
		 return "error";
	 }
	 startPosition = originalInput.find("*", tagPosition);
	  cout << originalInput.at(startPosition) << endl;
	 startPosition++;
	 
	 endPosition = startPosition;
	cout << "1end: " << endPosition << endl;
	
	/*
	while (1)
	{
		endPosition++;
		if (originalInput.at(endPosition) == '$')
		{
		break;
		}
		cout << "sploop: " << originalInput.at(endPosition) << endl;
	}
	*/
	endPosition = originalInput.find("$", startPosition);
	endPosition = endPosition - startPosition;
	cout << "end: " << endPosition << endl;
	
	 	  //cout << originalInput.at(endPosition) << endl;
	 text = originalInput.substr(startPosition, endPosition);
	 return text;
 };

  string dataFromWebPage:: returnOutMessage()
  {
	  //string censoredText = censorText();
	  //censorText();
	 return "$USERNAME*Cato$COLOR*red$PICTURE*three$TEXT*" + text + "proof" + "$END";
  }
  
  

  /* Fifo names */
string receive_fifo = "Namerequest";
string send_fifo = "Namereply";
int count = 0;
/* Server main line,create name MAP, wait for and serve requests */
int main() {

string inMessage, outMessage, preventDuplicates;

vector <string> commentVector;
vector <string> testVector;

testVector.push_back("Gastby");
testVector.push_back("believed in the green");
testVector.push_back("light the future that year by ");
testVector.push_back("year receds before us");
testVector.push_back("it eludes us then but it is no matter");
testVector.push_back("tomorrow we'll run faster, stretch out our arms farther.");

  // create the FIFOs for communication
  Fifo recfifo(receive_fifo);
  Fifo sendfifo(send_fifo);
  
  int previousVectorSize = 0;
  int fourFromEnd;
  string lastFour;
  // main while loop 
   while (1) {
inMessage = "";
cout << "start" << endl;
//cout << "1 working: " << inMessage << "vector size: " << commentVector.size() << endl << endl;
	    recfifo.openread();// opens to read
	     inMessage = recfifo.recv(); // takes message in 
		 	sendfifo.openwrite(); // writes 
		cout << "2 message should follow: " << inMessage << "vector size: " << commentVector.size() << endl << endl;
			if (inMessage.size() > 4)
			{
				fourFromEnd = inMessage.size() - 4;
				// tests if it is a new value 
			lastFour = inMessage.substr(fourFromEnd, 4);
			}
			else{
				lastFour = inMessage;
			}
					
			
			cout << "3 working: " << inMessage << "vector size: " << commentVector.size() << "last four: " << lastFour << endl << endl;
			if (lastFour == "$END")
			{
		 
		if ((inMessage.find("***$request") == -1) && (inMessage.find("$END") != -1))
		{
			
				
				//cout << "4 working: " << inMessage << "vector size: " << commentVector.size() << endl << endl;
			
			

		 string stringToProcess;
		 stringToProcess = inMessage.substr(0, fourFromEnd);
		 
cout << "5 working: " << inMessage << " vector size: " << commentVector.size() << endl << endl;
			 
		 
		 
	 // inMessage.erase(commentVector.size() - 4, 4);
		commentVector.push_back(stringToProcess);
		
	//cout << "the back of the vector: " << commentVector.back() << endl << endl;
	//cout << "6 working: " << inMessage << "vector size: " << commentVector.size() << endl << endl;
	
	
	//cout << "allcomments: " << inMessage << endl; //allCommentsInOneString << endl;
	inMessage = "";
//cout << "7 working: " << inMessage << "vector size: " << commentVector.size() << endl << endl;
	// preventDuplicates = inMessage;
		}
	    
	 
	 if ( inMessage.find("***$request") != string :: npos) 
	 {
		 cout << "inside the request stanza" << endl;
		// cout << "comment vector: " << commentVector.size();
		 cout << "previous vector: " << previousVectorSize;
		 if (commentVector.size() > previousVectorSize)
		 {
				for (int i = 0; i < commentVector.size(); i++)
	{
		cout << "8 working: " << inMessage << "vector size: " << commentVector.size() << endl << endl;
		 outMessage = commentVector[i];
		 sendfifo.send(outMessage);
		 cout << "i: " << i << endl;
		 cout <<"has been sent? " << commentVector[i] << " " << i<< endl;
	}
	 
	 sendfifo.send("$END");
	cout << "END HAS BEEN SENT"  << endl << endl;
	 } 
	}


	 }
	  cout << "end" << endl;

	sendfifo.fifoclose();
	 recfifo.fifoclose();
  }
  
  
}

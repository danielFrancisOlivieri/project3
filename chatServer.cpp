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

string inMessage, outMessage;

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
  
  
  
  // main while loop 
   while (1) {

	    recfifo.openread();// opens to read
	     inMessage = recfifo.recv(); // takes message in 
		 	sendfifo.openwrite(); // writes 
			
		if (inMessage.find("***$request") == -1)
		{
			 cout << "inmessage: " << inMessage << endl;
			 
		 int forSubstring = inMessage.size() - 4;
		 
		 inMessage = inMessage.substr(0, forSubstring);
		 
	 // inMessage.erase(commentVector.size() - 4, 4);
		commentVector.push_back(inMessage);
	cout << "smeep: " << commentVector.back() << endl;
	
	
	
	cout << "allcomments: " << inMessage << endl; //allCommentsInOneString << endl;
	inMessage = "";
	 cout << "size: " << commentVector.size() << endl;
	 
		}
	    
	 
	 else {
		 
	for (int i = 0; i < commentVector.size(); i++)
	{
		 sendfifo.send(commentVector[i]);
		 cout << "IT has be sent: " << i<< endl;
	}
	 
	 sendfifo.send("$END");
	
	 }
	 
		// cout << allCommentsInOneString << endl;
		//  	 allCommentsInOneString += "<p>" + inMessage + "</p>";
	 
	 // sendfifo.send(commentVector.front());
	 // if (inMessage.find("***$request") != -1){
		 // sendfifo.send(commentVector.back());
	 // }
		// for (int i = 0; i < commentVector.size(); i++)
		// {
			// sendfifo.send(commentVector[i]);  //(commentVector.back());
		// }
		
	 
	  

	sendfifo.fifoclose();
	 recfifo.fifoclose();
  }
  
  
}

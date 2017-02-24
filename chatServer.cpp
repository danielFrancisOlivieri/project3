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
#include "fifo.h"

using namespace std;


class dataFromWebPage
{
	public: 
	dataFromWebPage(string inputted);
	string returnOutMessage();
	
	private:
	
	string returnUsername();
	string returnColor();
	string returnPicture();
	string returnText();
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
		 cout << "error" << endl;
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
		 cout << "error" << endl;
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
		 cout << "error" << endl;
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
		 cout << "error" << endl;
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
	 return "$USERNAME*Cato$COLOR*red$PICTURE*three$TEXT*" + text + "$END";
  }
  
  

  /* Fifo names */
string receive_fifo = "Namerequest";
string send_fifo = "Namereply";

/* Server main line,create name MAP, wait for and serve requests */
int main() {

string inMessage, outMessage;
  // create the FIFOs for communication
  Fifo recfifo(receive_fifo);
  Fifo sendfifo(send_fifo);
  
  
  
  // main while loop 
   while (1) {

	    recfifo.openread();// opens to read
	     inMessage = recfifo.recv(); // takes message in 
		 
	transform(inMessage.begin(), inMessage.end(), inMessage.begin(),(int (*)(int))tolower); // makes the word lower case
	
	//StemEnglish(inMessage);// stems it 
		cout << "inmessage: " << inMessage << endl;

	//vec = indexSearch(inMessage); // gets the cector of lines 
	
	outMessage = inMessage;
	
	sendfifo.openwrite(); // writes 
	//sendfifo.send("</p>");

	sendfifo.send(outMessage + "meep");

	
	
	//is.close();

	//sendfifo.send("$END");


	sendfifo.fifoclose();
	 recfifo.fifoclose();
  }
  
  
  /*
while (1) {
  recfifo.openread();
    inMessage = recfifo.recv();
	
	dataFromWebPage dataToSend(inMessage);
	
		cout << " Results: " << dataToSend.returnOutMessage() << endl;

	sendfifo.openwrite();
	sendfifo.send(dataToSend.returnOutMessage() + "goofy");
	sendfifo.fifoclose();
	recfifo.fifoclose();
}

/*
string inMessage, reply; // variable to hold the reply gotten from the webpage 

  // create the FIFOs for communication
  Fifo recfifo(receive_fifo);
  Fifo sendfifo(send_fifo);

  recfifo.openread();
  
while (reply.find("$END") != -1)
{
  
  
//  dataFromWebPage ourData(inputtedString); // put string into class 
  
  //cout << ourData.returnOutMessage() << endl;
  cout << "Looping" << endl;
  
	reply = recfifo.recv();
	
	cout << reply << endl;
	
	
}

recfifo.fifoclose();
  sendfifo.openwrite();
	sendfifo.send(reply);
	sendfifo.fifoclose();
	*/
	//recfifo.fifoclose();
	
  
  // send the string out to CGI 
  
  //cout<< dataFromWebPage.originalInput << endl;
  /*
  To do
  
  1. open fifos
  2. read data from cgi
  3. open the object (possibly JSON)
  4. censor
  5. change object to censored form
  6. send to CGI through fifo 
  7. repeat  
  
  */
  

  
}


 
 
 

/***************************************************************************
* chatServer.cpp
 *
* 
*
* This program runs as a background server to a CGI program, providinging a chat
* room where multiple users can send messages to one another.
* 
* 
* 
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
#include <string>
#include "fifo.h"

using namespace std;

/* Fifo names */
string receive_fifo = "Chatrequest";
string send_fifo = "Chatreply";

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
		string originalInput, outPut, username, color, picture, text;
	
	
};

   dataFromWebPage:: dataFromWebPage(string inputted)
 {
	 originalInput = inputted;
	 cout << "working: " << originalInput << endl; 
	 
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
	 username = originalInput.substr(startPosition, endPosition);
	 return username;
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
	  //censoredText = text.replace("damn", "d*mn");
	 return "$USERNAME*Cato$COLOR*red$PICTURE*three$TEXT*" + returnText() + "$END";
  }


/* Server main line,create name MAP, wait for and serve requests */
int main() {

    string inputtedString;
  inputtedString = "$USERNAME*Cato$COLOR*red$PICTURE*three$TEXT*out out damn spot$END";
  
  // FIFO in 
  
  
  dataFromWebPage ourData(inputtedString); // put string into class 
  
  cout << ourData.returnOutMessage() << endl;
  
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


 
 
 

#include <iostream>
// Stuff for AJAX
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"

//Stuff for pipes
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include "fifo.h"

using namespace std;
using namespace cgicc; // Needed for AJAX functions.

//Indeed, myString needs to be a copy of the original string
std::string StringToUpper(std::string myString)
{
  const int length = myString.length();
  for(int i=0; i!=length ; ++i)
    {
      myString[i] = std::toupper(myString[i]);
    }
  return myString;
}


// fifo for communication
string receive_fifo = "Chatreply";
string send_fifo = "Chatrequest";
ofstream JADChatlog;

int main() {
  Cgicc cgi;    // Ajax object

  JADChatlog.open("/tmp/JADChatlog.log",ios::app);
  
  // Create AJAX objects to recieve information from web page.
  form_iterator message = cgi.getElement("message");
    form_iterator outMessageForm_iterator = cgi.getElement("outMessage");
  string inMessage, outMessage;

  cout << "Content-Type: text/plain\n\n"; // prepares the webpage for the text 
  // create the FIFOs for communication
  Fifo recfifo(receive_fifo);
  Fifo sendfifo(send_fifo);
  
  // Call server to get results
  inMessage = **message;
  JADChatlog << "This is the message: " << inMessage << endl;
  outMessage = **outMessageForm_iterator;


  while(1)
	
	{
		
	// open sendfifo to send word to server
  JADChatlog << "preOPEN:" << inMessage << endl;
  sendfifo.openwrite();
  JADChatlog << "presend:" << inMessage << endl;
  string inAndOut = inMessage + outMessage;
  if ( 2> inAndOut.size())
  {
	   JADChatlog << "not sending anything" << inAndOut << endl;
  }
  else
  {
	    sendfifo.send(inAndOut); //sends message to server
  JADChatlog << "sent:" << inAndOut << endl;
  }
  


 // return 0;
  /* Get a message from a server */
  recfifo.openread();
  JADChatlog << "openread" << endl;
  //return 0;	
	outMessage = recfifo.recv(); // puts the results from the server into the results variable
	JADChatlog << "recv: " << outMessage << endl;

	 if (outMessage.find("$END") != string:: npos)
	 {
JADChatlog << "sending to page" << endl;
	   cout << outMessage; // outputs message to webpage
	     return 0;
	   break;
	 }

	cout << "<p>" << outMessage << "</p>";
		
	}
  
  

}

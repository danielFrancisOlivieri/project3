//File Name: testclient.cpp
//Team Members: Daniel Oliveri, Juviand Rivera, & Aidan Murphy
//Email Addresses: olivierid@kenyon.edu, riveraj@kenyon.edu murphy1@kenyon.edu
//Project Number: 3
//Description: A test client for the server of a multi-user chatroom program
//Last Changed: Febuary 24, 2017
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "fifo.h"

using namespace std;
string receive_fifo = "Namereply";
string send_fifo = "Namerequest";

int main() 
{
  string message, name, userInput;
  string reply, inputtedString = "$USERNAME*Cato$COLOR*red$PICTURE*three$TEXT*out out damn spot$END";

  while (1) {
	cout << "Enter a string of text:";
	cin >>  userInput;
	//transform(name.begin(), name.end(), name.begin(), ::toupper);

	message = "$USERNAME*Cato$COLOR*red$PICTURE*three$TEXT*" + userInput + "$END";
	
	// create the FIFOs for communication
	Fifo recfifo(receive_fifo);
	Fifo sendfifo(send_fifo);

	cout << "Send:" << message << endl;
	sendfifo.openwrite();
	sendfifo.send(message);

	/* Get a message from a server */
	recfifo.openread();
	reply = recfifo.recv();
	
	recfifo.fifoclose();
	sendfifo.fifoclose();
	cout << "Server sent: " << reply << endl;
  }


}

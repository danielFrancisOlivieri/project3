//File Name: chatServer.cpp
//Team Members: Daniel Oliveri, Juviand Rivera, & Aidan Murphy
//Email Addresses: olivierid@kenyon.edu, riveraj@kenyon.edu murphy1@kenyon.edu
//Project Number: 3
//Description: The server for a multi-user chat program.
//Last Changed: March 1st, 2017
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

/* Fifo names */
string receive_fifo = "Chatrequest";
string send_fifo = "Chatreply";
int count = 0;
/* Server main line,create name MAP, wait for and serve requests */
int main()
{

    string inMessage, outMessage, preventDuplicates;

    vector<string> commentVector; // holds comments to be outputted

    // create the FIFOs for communication
    Fifo recfifo(receive_fifo);
    Fifo sendfifo(send_fifo);

    int previousVectorSize = 0; // helps to ensure that the vector is only sent if there are new comments to be added
    int fourFromEnd; // helps remove the $END part
    string lastFour;
    // main while loop
    while (1) {
        inMessage = "";

        recfifo.openread(); // opens to read
        inMessage = recfifo.recv(); // takes message in
        sendfifo.openwrite(); // writes

        if (inMessage.size() > 4) // this is to prevent a string that is too short from being cut
        {

            fourFromEnd = inMessage.size() - 4; // gets beginning of cut
            // tests if it is a new value
            lastFour = inMessage.substr(fourFromEnd, 4); // cuts
        }
        else {
            lastFour = inMessage;
        }

        if (lastFour == "$END") {

            if ((inMessage.find("***$request") == -1) && (inMessage.find("$END") != -1)) // makes certain the message isn't the request
            {

                string stringToProcess;
                stringToProcess = inMessage.substr(0, fourFromEnd); // leaves behind only the user's string

                commentVector.push_back(stringToProcess);

                inMessage = "";
            }

            if (inMessage.find("***$request") != string::npos) // checks if it's a request
            {

                if (commentVector.size() > previousVectorSize) // helps to ensure that the vector is only sent if there are new comments to be added
                {
                    for (int i = 0; i < commentVector.size(); i++) {

                        outMessage = commentVector[i];
                        sendfifo.send(outMessage);
                    }

                    sendfifo.send("$END");
                }
            }
        }

        // closing fifos
        sendfifo.fifoclose();
        recfifo.fifoclose();
    }
}

#MakeFile to build and deploy the Sample US CENSUS Name Data using ajax
# For CSC3004 Software Development

# Put your user name below:
USER= olivierid

CC= g++

#For Optimization
#CFLAGS= -O2
#For debugging
CFLAGS= -g

RM= /bin/rm -f

all: chatServer testclient JAD_chatAjax PutCGI PutHTML
#all: chatServer testclient 

testclient.o: testclient.cpp fifo.h
	$(CC) -c $(CFLAGS) testclient.cpp

chatServer.o: chatServer.cpp fifo.h
	$(CC) -c $(CFLAGS) chatServer.cpp

JAD_chatAjax.o: JAD_chatAjax.cpp fifo.h
	$(CC) -c $(CFLAGS) JAD_chatAjax.cpp

testclient: testclient.o fifo.o
	$(CC) testclient.o fifo.o -o testclient

chatServer: chatServer.o fifo.o
	$(CC) chatServer.o  fifo.o -o chatServer

fifo.o:		fifo.cpp fifo.h
		g++ -c fifo.cpp
JAD_chatAjax: JAD_chatAjax.o  fifo.h
	$(CC) JAD_chatAjax.o  fifo.o -o JAD_chatAjax -L/usr/local/lib -lcgicc

PutCGI: JAD_chatAjax
	chmod 757 JAD_chatAjax
	cp JAD_chatAjax /usr/lib/cgi-bin/$(USER)_JAD_chatAjax.cgi 

	echo "Current contents of your cgi-bin directory: "
	ls -l /usr/lib/cgi-bin/

PutHTML:
	cp site.html /var/www/html/class/softdev/$(USER)/project3
	cp name_stats_ajax.css /var/www/html/class/softdev/$(USER)/project3

	echo "Current contents of your HTML directory: "
	ls -l /var/www/html/class/softdev/$(USER)/project3

clean:
	rm -f *.o JAD_chatAjax chatServer testclient

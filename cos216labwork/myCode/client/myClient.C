//Merissa Joubert
//includes first

# include <stdio.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <netinet/in.h> 
# include <netdb.h>
# include <stdlib.h>
# include <iostream>
# include <cstdlib>
# include <linux/netfilter.h> 
# include <unistd.h>
# include <string.h>

using namespace std;

int main(int argc, char* argv[])
{
	//cout<<"Client started"<<endl;
// declare variables to use in various functions
///////////////////////////	
//	cout << "enters main" << endl;	

	int myClientSocket;//stores the socket created by socket()
	struct sockaddr_in myServerAddress;//stores the server address
	struct hostent * myServer;
	char* myMessage;
	unsigned int myMessageLength;
	unsigned int myServerPort;
	char buffer[256];
	char clientName[100];
	char * garbage;
	char message[256];
	int bytesReceived;
	int totalBytesReceived;
	int n;
	int connectf;
	
	
	//check if correct number of arguments were specified by user when starting the program
	
	if(argc<3)
	{
		cout<<"Incorrect number of arguments"<<endl;
		cout<<"Specify a hostname and port number"<<endl;
		exit(1);
	}
	
	else
	{
		cout<<"Client started"<<endl;
		//cout<<"Enter a client name to use"<<endl;
		
		//cin.get(clientName,20);
		//cin.clear();
		//cin.ignore( );
		//getline(cin,garbage);
		myServerPort = atoi(argv[2]);
//1 create a socketusing  socket()
		myClientSocket = socket(AF_INET,SOCK_STREAM,0);//create a socket using socket() 
		
		if (myClientSocket <0)//check for errors in opening a socket
		{
			cout<<"Error opening a socket"<<endl;
		//	exit(1);
		}
		else
		{
//			cout<<"attempting to get hostname"<<endl;
			myServer = gethostbyname(argv[1]);//gets the server address
			if(myServer ==NULL)//checks for errors in hostname
			{
				cout<<"Host not found"<<endl;
		//		exit(1);
			}
			else//not sure what this does have to research later
			{
				//cout<<"just before bzeroe"<<endl;
				bzero((char*)&myServerAddress,sizeof(myServerAddress));
				//cout<<"after bzero"<<endl;
				myServerAddress.sin_family = AF_INET;
				 
				//cout<<"before bcopy"<<endl;
				bcopy((char*)myServer->h_addr,(char*)&myServerAddress.sin_addr.s_addr,myServer->h_length);
				//cout<<"before htons"<<endl;
				myServerAddress.sin_port = htons(myServerPort);
			}
		}
	}
///////////////////////////	
//	cout << "at step 2" << endl;	
//2 use connect() to connect the socket to the address of the server
//cout<<"attempting connect"<<endl;
	connectf = connect(myClientSocket,(struct sockaddr*) &myServerAddress,sizeof(myServerAddress));
	
///////////////////////////	
//	cout << "after connect" << endl;		
	if(connectf<0)
	{
		cout<<"Error connecting to server"<<endl;
		//exit(1);
	}
	
	//display username
	
	bzero(buffer,256);
	//clientName = clientName;
	//strcpy(buffer,clientName);
	//strcpy(buffer,"connected to the server");
///////////////////////////	
//	cout << "before first read" << endl;		
		n= read(myClientSocket,buffer,/*strlen(buffer)*/255);///changed to 255
///////////////////////////	
//	cout << "after first read: " << buffer << "thatwasbuffer"<< endl;	
		//cout<<"written"<<endl;
		if(n<0)
		{
			cout<<"could not write to socket"<<endl;
			//exit(1);
		}
		else
		{
			while (strcmp(message,"ZZZ\r\n")!=0 && strcmp(message,"ZZZ")!=0)///changed to message
			{
///////////////////////////	
//	cout << "enters while" << endl;						
				cout<< buffer;
///////////////////////////	
//	cout << "before bzero" << endl;					
				bzero(message,256);
				cin.ignore();
///////////////////////////	
//	cout << "before cin.get" << endl;	
				cin.get(message,256);///changed to message
				
				
///////////////////////////	
//	cout << "before write: " << message << endl;	
				n = write(myClientSocket,message, strlen(message)); ///changed to message 
///////////////////////////	
//	cout << "after write" << endl;					
				
				if (n<0)
					cout<<"could not write to the socket"<<endl;
				
				else
				{
					bzero(buffer,256);
	//buffer=(char*)"connected";
///////////////////////////	
//	cout << "before read" << endl;						
					n = read(myClientSocket,buffer,/*strlen(buffer)*/255);///changed to 255
///mine cowde
					if (n < 0)
					 ///////////////////////////	
//	cout << "n < 0" << endl;						
///////////////////////////	
//	cout << "after read" << endl;										
					cout<<buffer<<endl;
///////////////////////////	
//	cout << "exits while" << endl;											
				}
			}
		}
	
close(myClientSocket);
///////////////////////////	
//	cout << "at step 3" << endl;			
//3 send and receive data
		//cout<<"just before bzero"<<endl;
		//cout<<"attempting read"<<endl;
	/*	n= read(myClientSocket,buffer,255);
		//cout<<"read"<<endl;
		if(n<0)
		{
			cout<<"could not read from socket"<<endl;
			exit(1);
		}
		cout<<buffer<<endl;
		cout<<"Enter your message: ";
		bzero(buffer,256);
		//cout<<"attempting write"<<endl;
		cin.get(buffer,256);
		//cout<<"fgets done"<<endl;
		n= write(myClientSocket,buffer,strlen(buffer));
		//cout<<"written"<<endl;
		if(n<0)
		{
			cout<<"could not write to socket"<<endl;
			exit(1);
		}
		bzero(buffer,256);
		
	
	
	close(myClientSocket);*/

	return 0;
}
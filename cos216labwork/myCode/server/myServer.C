//Merissa Joubert
# include <stdio.h>
# include <string.h>
//# include <stdlib>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <iostream>
# include <cstdlib>
# include <linux/netfilter.h>
# include <unistd.h>
# include <thread>
# include <vector>
# include <algorithm>


using namespace std;
void error(const char*msg)
{
	perror(msg);
	exit(1);
}

class ChatServer
{
	public:
	ChatServer(unsigned int port,int socket)
	{
		myServerPort = port;
		myServerSocket = socket;
	}
	void myServerRun();
	vector <int> getList();
	void removeSocket(const int );
	
	protected:
	ChatServer();
	
	private:
	vector <int> clientList;
	vector<thread> threads;
	unsigned short myServerPort;
	int myServerSocket;
};

void chatFunction(int, ChatServer*);
void broadcast(char[256],char[256],ChatServer*);
int main(int argc, char  * argv[])

{
	//unsigned short serverPort = 9200;
///////////////////////////	
	cout << "enters main" << endl;
	cout<<"Server started"<<endl;
	//sock fd and newsockfd are file descriptiors.
	//clilen stores size of client address
	//n is the return of read and write calls
	//bindf stores 0 if successfully binded and-1 if not
	//listenf stores 0 if succesfull and -1 i not
	//acceptf stores 0 if a connection between a client and a server was successful and -1 if not
	//readf stores 0 if read successfully and -1 if not
	//writef stores 0 if written successfully and -1 if not
	int sockfd, serverPort,n, bindf,listenf,acceptf,readf,writef;
	//int serverPort = 9200;
	
	const char * myError;
	
	char buffer[256];//read from socket connection into here
	char myMessage[256];
	
	struct sockaddr_in myAddress, clientAddress;
	
	if (argc!=2)
	{
		cout<<"Error, no port provided"<<endl;
		exit(1);
	}
	//1 create a socket using socket()
	sockfd = socket(AF_INET, SOCK_STREAM,0);//creates a socket
	
	if (sockfd<0)//check if a valid socket was specified
	{
		myError = "error opening socket";
		error(myError);
	}
	
	//2 Bind the socket to an address using bind()
	bzero((char*) & myAddress,sizeof(myAddress));
	serverPort = atoi(argv[1]);
	myAddress.sin_family = AF_INET;
	myAddress.sin_addr.s_addr= INADDR_ANY;
	myAddress.sin_port = htons(serverPort);
	bindf =bind(sockfd,(struct sockaddr*)&myAddress,sizeof(myAddress));// binds the socket to he local address
	if (bindf ==-1)//checks if the bind was successful
	{
		myError = "error binding the socket to the address";
		error(myError);
	}
	
	//3 Use listen() for a connection
	listenf = listen(sockfd,5);//listens for coonections	
	if(listenf == -1)//check if listen was successful
	{
		myError = "error listening for connections";
		int closedS = close(sockfd);
		error(myError);
	}
	else
	{
		ChatServer a(serverPort,sockfd);
		cout<<"New chat server created"<<endl;
		a.myServerRun();
		cout<<"server run completed"<<endl;
	}
	close(sockfd);
		close(acceptf);
}
void ChatServer::myServerRun()
{
///////////////////////////	
	cout << "enters myserverrun" << endl;	
	//unsigned short serverPort = 9200;
	unsigned int clilen;
	struct sockaddr_in cli_addr;
	int cliSocket;
	
	cout<<"Server is running on port"<<myServerPort<<endl;
	while(true)
	{
		clilen = sizeof(cli_addr);
		cliSocket = accept(myServerSocket,(struct sockaddr*) &cli_addr , & clilen);
	
		if (cliSocket <0)
		{
			cout<<"error joining server"<<endl;
		}		
		else
		{
			cout<<"New client joined the chat"<<endl;
		
			threads.push_back(thread((*chatFunction),cliSocket,this));
			clientList.push_back(cliSocket);
		}
	}
}

vector<int> ChatServer::getList()
{
	return clientList;
}

void ChatServer::removeSocket(const int socket)
{
	vector<int> ::iterator iter;
	
	iter = find(clientList.begin(),clientList.end(), socket);
	if(iter!=clientList.end())
	{
		clientList.erase(iter);
	}
}


void chatFunction(int socket, ChatServer* a)
{
	char myMessage [256];
	int m;
	char myName[256];
	char buffer[256];
	
	bzero(myMessage,256);
	strcpy(myMessage,"Chatroom entered.\n Type ZZZ to close the server.\n Type Quit to leave.\n Enter a username:");
	
	m = write(socket,myMessage,strlen(myMessage));
	
	if (m<0)
		cout<<"Could not write to the socket"<<endl;
	
	m= read(socket,myName,255);
	
	if(m<0)
		cout<<"could not read from the socket"<<endl;
	bzero(myMessage,256);
	
	strcat(myMessage,"? ");
	
	m = write (socket,myMessage,strlen(myMessage));
	if(m<0)
		cout<<"could not read from socket"<<endl;
	
	bzero(buffer,256);
	m = read (socket,buffer,255);
	
	if (m<0)
		cout<<"could not read from socket"<<endl;
	
	while (!((strcmp(buffer,"ZZZ\r\n")==0)||(strcmp(buffer,"ZZZ")==0)))
	{
		
	///RavenBlood-in this loop, the server must write and read every time.
	///broadcast and send and display only in special cases
		
		/*Juan se code*/
		 char temp[256];
		string command = "BROADCAST";
		strncpy(temp, buffer, 9);
		temp[9] = '\0';
		if (strcmp(command.c_str(), temp) == 0)
		{
			//broadcast
			string toBroadcast = buffer;
			toBroadcast = toBroadcast.substr(9);
			bzero(buffer, 256);
			strcpy(buffer, toBroadcast.c_str());
			broadcast(buffer,myName,a);
		}
	/*	 command = "SEND";
		strncpy(temp, buffer, 4);
		temp[4] = '\0';
		if (strcmp(command.c_str(), temp) == 0)
		{
		//send
			string toSend = buffer;
			toSend = toSend.substr(5);
			bzero(buffer, 256);
			strcpy(buffer, toSend.c_str());
			send(buffer, name,cs);
		}
		command = "DISPLAY";
		strncpy(temp, buffer, 7);
		temp[7] = '\0';
		if (strcmp(command.c_str(), temp) == 0)
		{
		//display
			display(socket, cs);
		}
		command = "QUIT";
		strncpy(temp, buffer, 4);
		temp[4] = '\0';
		if (strcmp(command.c_str(), temp) == 0)
		{
			vector<int> cl = cs->getList();
			for (auto it = std::begin(cl); it!=std::end(cl); ++it) {
			if (*it != socket)
			{
				close(*it);
				cl.erase(it);
			}
		}
	break;
	//Quit*/
	}
		/* stops here */
		cout<<"Enters while"<<endl;
		broadcast(buffer, myName, a);
		
		bzero(myMessage,256);
		
		strcat(myMessage,"? ");
		
		m= write(socket,myMessage,strlen(myMessage));
		
		if(m<0)
			cout<<"could not write to socket"<<endl;
		bzero(buffer,256);
		
		m = read(socket,buffer,255);
		
		if(m<0)
			cout<<"could not read from socket"<<endl;
		
	bzero(myMessage,256);
	strcat(myMessage,"left the server");
	
	broadcast(myMessage,myName,a);
	
	a->removeSocket(socket);
	
	close(socket);
	
}

void broadcast(char message[256],char alias[256],ChatServer * a)
{
///////////////////////////	
	cout << "in broadcast " << endl;			
	char msg[256];
	int m;
	vector <int> clients;
	vector <int> :: iterator it;
	
	bzero(msg,256);
	strcat(msg,alias);
	strcat(msg," - ");
	strcat(msg,message);
	
	clients = a->getList();
	
	for( it = std::begin(clients);it!=std::end(clients);++it)
	{
		m = write(*it,msg,strlen(msg));
		if(m <0)
			cout<<"could not write to socket"<<endl;
	}
	
	cout<<msg<<endl;
}
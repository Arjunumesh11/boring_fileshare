void *clientWorker(void *acceptSocket)
{
    int newSocket = (int)acceptSocket;
    char okStatus[] = "HTTP/1.1 200 OK\r\n"
                      "Content-Type: text/html\r\n"
                      "Connection: close\r\n"
                      "Content-Length: 20\r\n"
                      "\r\n"
                      "s";
    writeLn(newSocket, okStatus);
    const char *fileName = "/home/tyra/Desktop/example.txt";
    sendF(newSocket, fileName);
}

void writeLn(int acceptSocket, const char *buffer)
{
    int n = write(acceptSocket, buffer, strlen(buffer) - 1);
    if (n < 0)
    {
        error("Error while writing");
    }
}

string buffer;
string line;
ifstream myfile(fileName);
struct stat filestatus;
stat(fileName, &filestatus);
int fsize = filestatus.st_size;
if (myfile.is_open())
{
    while (myfile.good())
    {
        getline(myfile, line);
        buffer.append(line);
    }
    cout << buffer << endl;
}
writeLn(acceptSocket, buffer.c_str());
cout << fsize << " bytes\n";
# Offline streamer
A simple video streaming service implemented from scratch using c++

## HTTP
Transfer encoding used Chunked
### Methods ###
```
std::vector<char>  chunk::make_chunk(std::string data,int size)
```
create chunks specified by http standard
```
5\r\n
chunk\r\n
8\r\n
encoding\r\n
8\r\n
for data\r\n
8\r\n
chunking\r\n
0\r\n
\r\n
```
## Directory Listing
### Methods
```
int create_directory(std::string root_folder)
```
Recursively iterate through <root_folder> and create a hash map
```
std::vector<std::string> get_filelist();
```
Returns the List of all files in the directory
```
std::string get_file(std::string filename);
```
Returns the filepath of a specific <filename>
## Router
### Methods
```
std::map<std::string, std::string> get(std::string path, std::string url);
```
#### example
```
get(" /video/:name/:filetype " , " /video/dance/mp4 ")
```
```
returns map
video : dance
filetype : mp4
```
## Serve static files
### Methods
```
int serve_static::servestatic::serve(std::string path, int new_socket)

serve_static::servestatic::servestatic(std::string folder)
```
### example
```
servestatic server("./public");
server.serve("/index.html",sock_fd);
```
### Handle connection
### Methods
```
 void use(void *object, int (*func)(void *context, std::string response, int new_socket))
int call(std::string response, int new_socket)
```
Use function works similar to express.js use method 
### example
```
 handle_connection::handleconnection routes;
    routes.use(&public_folder, serve_static::servestatic::serve);
    routes.use(&test_folder, serve_static::servestatic::serve);
```
Handle Connection has a middleware stack
```
std::vector<std::pair<void *, int (*)(void *, std::string, int)>> funclist;
```
Middleware can be added using use function The call function execute all the function in middleware stack in sequential order of their addition

# Boring_fileshare
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
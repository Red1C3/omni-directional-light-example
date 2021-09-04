#include<helpers.h>
using namespace std;
vector<char> readBin(const char* path){
    vector<char> data;
    fstream fileStream(path, ios::in | ios::binary | ios::ate);
    if(fileStream.is_open()){
        data.resize(fileStream.tellg());
        fileStream.seekg(0, ios::beg);
        fileStream.read(data.data(), data.size());
        fileStream.flush();
        fileStream.close();
    }
    else
    {
        assert("Failed to open a file " && 0);
    }
    return data;
}
//reading function for .fvecs, .ivecs files
//for working properly you need to type in command line fvecs_read "filename"
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;
int main(int argc,char* argv[]){
    //opening the file
    FILE* fd;
    if (strcmp(argv[0],"fvecs_read")==0){
        char* filename= argv[1] ;
        fd=fopen(filename,"r"); //d
        if(fd==0)
            perror("you typed wrongly the file you want to open");
    
    //reading the size of the vector
        int vector_size;
        size_t bytes_read=fread(&vector_size,sizeof(int),1,fd);
        int fvector_size=1*4+vector_size*4;
        fseek(fd,0,SEEK_END);
        long reading_point=ftell(fd) / fvector_size; //number of vectors /b

    }

}
//reading function for .fvecs files
//for working properly you need to type in command line  ./reading ("filename")
//optimally you can type the bounds you want, for example ./reading siftsmall_base.fvecs (bounda) (boundb)
//It's important you type both bounda and boundb in case you want to limit the vectors that are gonna be printed!
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
 #include "reading.h"
using namespace std;
void reading_fvec(int argc,char* argv[]){
    //opening the file
    if (argc < 2) {
        cerr << "Please provide the filename as a command-line argument.\n";
    }
    FILE* fd;
    
    char* filename= argv[1] ;
    fd=fopen(filename,"r"); //d
    if(fd==0){
        cerr<<"something went wrong with opening the file you provided \n";
    }

    //reading the size of the vector
    int vector_size;
    fread(&vector_size,sizeof(int),1,fd); //the first number of the file shows the vector size
    int fvector_size=(vector_size + 1) * sizeof(float); //counting starts from 0 so we add 1
    fseek(fd,0,SEEK_END);
    long vector_num=ftell(fd) / fvector_size; //number of vectors=total size_of_the_file/the vector size
    int bounda,boundb;
    if(argc==4){
        char* a=argv[2];
        bounda=atoi(a);
        cout<< "the bound a is:" << bounda <<"\n";
        char*b=argv[3];
        boundb=atoi(b);
        cout<< "the bound a is:" << boundb <<"\n";
    }
    else if (argc<4){
        bounda=1;
        boundb=4;
    }
    

    if (bounda < 1 || boundb > vector_num || bounda > boundb) {
        cerr << "Invalid bounds provided.\n";
        fclose(fd);
}

    int printed_vectors=boundb-bounda+1;
    fseek(fd,(bounda-1)*fvector_size,SEEK_SET); //back at the start of the vector which is bounded by bounda
    cout<< "printed_vectors are :" << printed_vectors << "\n";
    vector<vector<float>> vec(printed_vectors , vector<float> (vector_size));  
    for(int i=0;i<printed_vectors;i++){
        fseek(fd,4,SEEK_CUR);
        fread(vec[i].data(), sizeof(float), vector_size, fd);

    }



    for(int i=0;i<printed_vectors;i++){
        cout<< "Vector "<< (bounda+i)<< ":" ;
        for(int j=0;j<vector_size;j++){
            cout << vec[i][j]<< " ";
        }
        cout<< "\n \n";
    }

    fclose(fd);
}
//reading function for .fvecs files
//reading_fvecs also returns the 2d vector which contains every vector with the fitted size as the dataset file defines.
#include "reading.h"
using namespace std;
 vector<vector<float>> reading_fvecs(const char* filename,int bounda,int boundb){
   
    FILE* fd;
    
    
    fd=fopen(filename,"r"); //d
    if(fd==0){
        cerr<<"something went wrong with opening the file you provided \n";
    }

    //reading the size of the vector
    int vector_size;
    size_t p = fread(&vector_size,sizeof(int),1,fd); //the first number of the file shows the vector size
    int fvector_size=(vector_size + 1) * sizeof(float); //counting starts from 0 so we add 1
    fseek(fd,0,SEEK_END);
    long vector_num=ftell(fd) / fvector_size; //number of vectors=total size_of_the_file/the vector size
   
    
    //checking if  the bounds that were provided are valid.
    if (bounda < 1 || boundb > vector_num || bounda > boundb) {
        cerr << "Invalid bounds provided.\n";
        fclose(fd);
}

    int printed_vectors=boundb-bounda+1;
    fseek(fd,(bounda-1)*fvector_size,SEEK_SET); //back at the start of the vector which is bounded by bounda
    cout<< "vectors that got read are :" << printed_vectors << "\n";
    vector<vector<float>> vec(printed_vectors);
    for(int i=0;i<printed_vectors;i++){
        vec[i].resize(vector_size);
        fseek(fd,4,SEEK_CUR);
        size_t s =fread(vec[i].data(), sizeof(float), vector_size, fd);

    }

    fclose(fd);
    return vec;
}

vector<vector<int>> reading_ivecs(const char* filename,int bounda,int boundb){
   
    FILE* fd;
    
    
    fd=fopen(filename,"r"); //d
    if(fd==0){
        cerr<<"something went wrong with opening the file you provided \n";
    }

    //reading the size of the vector
    int vector_size;
    size_t a = fread(&vector_size,sizeof(int),1,fd); //the first number of the file shows the vector size
    int fvector_size=(vector_size + 1) * sizeof(int); //counting starts from 0 so we add 1
    fseek(fd,0,SEEK_END);
    long vector_num=ftell(fd) / fvector_size; //number of vectors=total size_of_the_file/the vector size
   
    
    //checking if  the bounds that were provided are valid.
    if (bounda < 1 || boundb > vector_num || bounda > boundb) {
        cerr << "Invalid bounds provided.\n";
        fclose(fd);
}

    int printed_vectors=boundb-bounda+1;
    fseek(fd,(bounda-1)*fvector_size,SEEK_SET); //back at the start of the vector which is bounded by bounda
    cout<< "printed_vectors are :" << printed_vectors << "\n";
    vector<vector<int>> vec(printed_vectors);
    for(int i=0;i<printed_vectors;i++){
        vec[i].resize(vector_size);
        fseek(fd,4,SEEK_CUR);
        size_t o =fread(vec[i].data(), sizeof(int), vector_size, fd);

    }


    fclose(fd);
    return vec;
}
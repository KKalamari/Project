#include <iostream>
#include<vector>
#include "reading.h"
#include "graph_creation.h"

using namespace std;


int main(int argc,char** argv){
    const char* filename="siftsmall_query.fvecs";
    vector<vector<float>>* vec=new vector<vector<float>>;
    vec=reading_fvecs(filename,1,10);  
    int k_neigh;
    int R; //let's say for now
    if(argc>1){
       char* k_num=argv[1];
        k_neigh=atoi(k_num);
        char* R_num=argv[2];
        R=atoi(R_num);
        } //we presume that the user provide the k_neighbors and R from the command line as the first argument after the execution
    else {
        k_neigh=20;
        R=32;
    }
    graph_creation(vec,k_neigh,R);
    cout << "I am before deallocating"<< endl;
    delete vec;
}

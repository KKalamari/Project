#include "acutest.h"
#include "FilteredGreedySearch.h"
#include "euclidean_distance.h"
void FilteredTest(){
    //checking FilteredGreedySearch without an initialized graph
    map<int,list<int>>graph; 
    int xq=1;
    int knn=0;
    int L_sizelist=3;
    map <float,int>M;
    M[6]=3; //setting starting node 0 to filter 1
    vector<float> Fq={6};//filter query
    
    vector<vector<float>>dataset={{6,5,1,4},{1,5,5,3},{6,5,3,4},{6,5,6,1},{1,3,4,2},{6,1,2,2}};
    vector<vector<float>> queries={{5,2,7,9,7,9},{3,6,1,2,1,2}};
    vector<vector<double>> querymatrix(dataset.size(),vector<double>(queries.size()));
    euclidean_distance_of_queries(dataset,queries,querymatrix);

    DistanceComparator comp(querymatrix, xq);

    // the euclidean distance for node 0,query 0 is: 7.81025
    // the euclidean distance for node 0, query 1 is: 2
    // the euclidean distance for node 1, query 0 is: 6.32456
    // the euclidean distance for node 1,query 1 is: 4.12311
    // the euclidean distance for node 2, query 0 is: 6.40312
    // the euclidean distance for node 2, query 1 is: 2.82843
    // the euclidean distance for node 3, query 0 is: 8.06226
    // the euclidean distance for node 3, query 1 is: 5.09902

    //for(int i =0; i<int(querymatrix.size());i++){
        // for(auto distance : querymatrix[i]){
        //     cout <<"the euclidean distance for node " <<i <<" is: "<< distance <<endl;
        // }
    //}
    vector<int> L;
    vector<int> V;
    pair <vector <int>,vector<int>> PairSet;
    // PairSet=FilteredGreedy(graph, xq, knn, L_sizelist,M,Fq,querymatrix,dataset);
    // V=PairSet.second;
    // cout<<"visited nodes are "<<endl;
    // for(auto visited : V){
    //     cout << visited <<" ";
    // }
    // TEST_CHECK(find(V.begin(),V.end(),5)!=V.end());
    // TEST_CHECK(find(V.begin(),V.end(),0)!=V.end());
    // TEST_CHECK(find(V.begin(),V.end(),2)!=V.end());
    // TEST_CHECK(find(V.begin(),V.end(),3)!=V.end());


    //checking FilteredGreedySearch with an initialized graph
    graph[0]={1,3,5};
    graph[1]={0,3,5};
    graph[3]={4,1,0,5};
    graph[2]={4};
    graph[4]={2};
    graph[5]={1,3,0};
    knn=3;
    PairSet=FilteredGreedy(graph, xq, knn, L_sizelist,M,Fq,querymatrix,dataset);
    V=PairSet.second;
    cout<<"visited nodes are "<<endl;
    for(auto visited : V){
        cout << visited <<" ";
    }
    L=PairSet.first;
    cout<<"k neigbors are "<<endl;
    for(auto neighbors : L){
        cout << neighbors <<" ";
    }
    TEST_CHECK(*(L.begin())==5); //the smaller distanced neighbor
    TEST_CHECK(*(L.begin()+1)==0); //the 2nd smaller distanced neighbor
    TEST_CHECK(*(L.begin()+2)==3);//the 3rd smaller distanced neighbor




}
     


TEST_LIST{
    {"FilteredTest",FilteredTest},
    {"NULL",NULL}
};
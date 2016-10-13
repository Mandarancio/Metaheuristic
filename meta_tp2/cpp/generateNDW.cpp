#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <stdlib.h>

int main(int argc, char* argv[]){
  if (argc!=3){
    std::cout<<"Please use: generator N output.dat\n";
    return -1;
  }
  
  int n = atoi(argv[1]);
  std::cout<<"Generating NDW Dat file of size: "<<n<<std::endl;
  std::cout<<"Output: "<<argv[2]<<std::endl;
  int **D= new int*[n];
  int **W= new int*[n];
  for (int i = 0;i<n;i++){
    D[i]=new int[n];
    W[i]=new int[n];
    for (int j=0;j<i+1;j++){
      if (i==j){
        D[i][j]=0;
        W[i][j]=0;
      }else{
        D[i][j]=rand()%n;
        W[i][j]=rand()%n;
      }
    }
  }
  
  std::ofstream of;
  of.open(argv[2]);
  
  of<<n<<"\n\n";
  for (int i = 0;i<n;i++){
    for (int j=0;j<n;j++){
      if (j<=i){
        of<<(D[i][j]<10 ? " ":"")<<D[i][j]<<" ";
      }else {
        of<<(D[j][i]<10 ? " ":"")<<D[j][i]<<" ";
      }
    }
    of<<"\n";
  }
  of <<"\n";
  for (int i = 0;i<n;i++){
    for (int j=0;j<n;j++){
      if (j<=i){
        of <<(W[i][j]<10 ? " ":"")<<W[i][j]<<" ";
      }else {
        of <<(W[j][i]<10 ? " ":"")<<W[j][i]<<" ";
      }
    }
    of<<"\n";
  }
  of.close();
  return 0;
}

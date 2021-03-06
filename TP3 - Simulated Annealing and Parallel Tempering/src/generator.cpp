#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

int main(int argc, char * argv[])
{
  if (argc!=3)
  {
    std::cout<<"generator OUT_FILE_NAME N_CITIES "<<std::endl;
    return -1;
  }
  srand(time(NULL));
  int N = std::atoi(argv[2]);
  std::string path(argv[1]);
  std::cout<<"Generating "<<N<<" random cities"<<std::endl;
  std::cout<<"Saving in "<<path<<std::endl;
  
  double size= 2*rand()%30+10;
  
  std::ofstream of;
  of.open(path.c_str());
  for (int i = 0 ;i<N;i++)
  {
    double x = ((double)rand()/((double)RAND_MAX)-0.5)*size;
    double y = ((double)rand()/((double)RAND_MAX)-0.5)*size;
    of<<"C"<<i<<" "<<x<<" "<<y<<std::endl;
  }
  of.close();
  return 0;
}

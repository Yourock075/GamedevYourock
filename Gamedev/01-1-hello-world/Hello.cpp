#include <iostream>
#include <cstdlib>

int main(int argc, char **argv[])
{
  using namespace std;
  cout<<"Hello, World!"<<endl;
  
  return cout.good() ? EXIT_SUCCESS : EXIT_FAILURE;
}

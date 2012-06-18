#include <string>
#include <iostream>
#include "eventDisplay/CsiDisplay.h"
#include "TApplication.h"

int main(int argc,char**argv){
  TApplication theApp("App", &argc, argv);
  argc = theApp.Argc();
  argv = theApp.Argv();

  if(argc!=3&&argc!=2){ std::cout<<"arg err"<<std::endl; return 0; }
  std::string inputFile = argv[1];
  std::string psfile="tmp.ps";
  if(argc==3) psfile=argv[2];

  CsiDisplay disp(inputFile,psfile);

  disp.displayEvent();
}

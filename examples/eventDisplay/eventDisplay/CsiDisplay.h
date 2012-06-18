#ifndef CsiDisplay_h
#define CsiDisplay_h

#include "csimap/CsiMap.h"
#include "gnana/DigiReader.h"
#include "TBox.h"
#include "TCanvas.h"
#include "TH2D.h"
#include "TAxis.h"

#include <string>
#include <iostream>

class CsiDisplay{
public:
  CsiDisplay(std::string inputFile,std::string psFile);
  ~CsiDisplay();

  TChain *m_inputTree;
  std::string m_psFile;

  int m_currentEntry;
  bool isOpenPSfile;

  TCanvas* m_canvas;
  int const m_nBox;
  TBox* m_box;
  TH2D* m_histSmall;
  TH2D* m_histLarge;

  void displayEvent();
  int  checkInput();
  void draw(int ndigi,int *id, double *E);
};

#endif

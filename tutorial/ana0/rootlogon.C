//
{
  std::cout << "Loading GsimData ..." << std::endl;
  std::string dir=std::getenv("E14_TOP_DIR");
  dir+="/lib/so/libGsimData.so";
  gSystem->Load(dir.c_str());
  gSystem->Load("libEG.so");
  std::cout << "Done." << std::endl;
}


PACKAGE      =     # or package name, as PACKAGE = $(shell basename `pwd`)
MAINS        =     # or exe name
INSTALL_LIBS =     # or no
INSTALL_BINS =     # or no

EXTRALIBS   +=     # for extra libs 

include $(E14_CONFIG_DIR)/Makefile.g4

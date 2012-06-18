# -*- Makefile -*-

MAINS = gsim4test
PACKAGE = $(shell basename `pwd`)
INSTALL_LIBS = no
INSTALL_BINS = yes

include $(E14_CONFIG_DIR)/Makefile.g4

pre::
ifeq "$(G4SYSTEM)" "Darwin-g++"
	@cp REQUIREMENTS REQUIREMENTS.orig && sed "/history/d" REQUIREMENTS.orig > REQUIREMENTS
else
	@if ! grep -q history REQUIREMENTS; then echo "history" >> REQUIREMENTS;fi
endif

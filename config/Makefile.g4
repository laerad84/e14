# -*- Makefile -*-

# $Id$
# $Log$

#
# Define 
#	libs
#	bins
# Geant4 binmake.gmk is used inside.
# Add rules for clean.
#
packagedir = .
ifneq "$(INSTALL_BINS)" "no"
	INSTALL_LIBS = yes
endif

### E14 common
include $(E14_CONFIG_DIR)/Makefile.e14


##########################################
clean::
ifneq "$(PACKAGE)" ""
	@ [ -d $(packagedir)/lib/so ]  && rm -f $(packagedir)/lib/so/* || true
endif



##########################################
### For Geant4
ifneq "$(G4SYSTEM)" ""
### If LDFLAGS, geant4 automatic configuration
###  is skipped. Make LDFLAGS empty here.
###  After includeing binmake.gmk, add -m32.
LDFLAGS  :=

name      := $(PACKAGE)
G4TMP     = tmp
G4BIN     = bin

CPPFLAGS  += -I$(G4INSTALL)/include

G4TARGET  := $(name)

EXLIB := $(shell ls src/*.cc 2> /dev/null)
ifneq "$(EXLIB)" ""
G4EXLIB   = true
endif

EXTRALIBS += $(shell if nm $$G4LIB/$$G4SYSTEM/libG4persistency.$(LIB_EXT)  | grep -q xerces;then echo -lxerces-c -lxerces-depdom;fi)

include $(G4INSTALL)/config/binmake.gmk

FOR32 = $(shell if file $$G4LIB/$$G4SYSTEM/libG4global.so  | grep -q 32;then echo -m32;fi)
LDFLAGS  += $(FOR32)

##########################################
libs: rootdicts
ifneq "$(SUBDIRS)" ""
	@ for dirs in $(SUBDIRS); do \
	echo making $@ in $$dirs; \
	$(MAKE) -C $$dirs $@ || exit 1; \
	done
endif
ifneq "$(PACKAGE)" ""
ifneq "$(EXLIB)" "" 
	@ $(MAKE) lib
	@ mkdir -p lib lib/so
	@ cd lib && \
	for i in `ls ../tmp/$(G4SYSTEM)/$(PACKAGE)/*a 2>/dev/null`; \
	do ln -f -s $$i .; \
	done
	@ cd lib/so && \
	for i in `ls ../../tmp/$(G4SYSTEM)/$(PACKAGE)/*$(LIB_EXT) 2>/dev/null`; \
	do ln -f -s  $$i .; \
	done
endif
endif

##########################################
bins:
ifneq "$(SUBDIRS)" ""
	@ for dirs in $(SUBDIRS); do \
	echo installing $@ in $$dirs; \
	$(MAKE) -C $$dirs $@ || exit 1; \
	done
endif
ifneq "$(MAINS)" ""
	@ $(MAKE) bin
	@ cd bin && ln -f -s $(G4SYSTEM)/* .
endif

else
### Without Geant4 
libs:
bins:
endif




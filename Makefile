#
# Created by gmakemake (Ubuntu Sep  7 2011) on Wed Feb 26 21:29:04 2014
#

#
# Definitions
#

.SUFFIXES:
.SUFFIXES:	.a .o .c .C .cpp .s .S
.c.o:
		$(COMPILE.c) $<
.C.o:
		$(COMPILE.cc) $<
.cpp.o:
		$(COMPILE.cc) $<
.S.s:
		$(CPP) -o $*.s $<
.s.o:
		$(COMPILE.cc) $<
.c.a:
		$(COMPILE.c) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.C.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.cpp.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%

CC =		gcc
CXX =		g++

RM = rm -f
AR = ar
LINK.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)
COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) -c
COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c
CPP = $(CPP) $(CPPFLAGS)
########## Flags from header.mak

CC =		gcc
CFLAGS =	-Wall -ggdb -std=c99
CLIBFLAGS = 	-lm

########## End of flags from header.mak


CPP_FILES =	
C_FILES =	jarvis.c points.c quickhull.c
PS_FILES =	
S_FILES =	
H_FILES =	points.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	points.o 

#
# Main targets
#

all:	jarvis quickhull 

jarvis:	jarvis.o $(OBJFILES)
	$(CC) $(CFLAGS) -o jarvis jarvis.o $(OBJFILES) $(CLIBFLAGS)

quickhull:	quickhull.o $(OBJFILES)
	$(CC) $(CFLAGS) -o quickhull quickhull.o $(OBJFILES) $(CLIBFLAGS)

#
# Dependencies
#

jarvis.o:	points.h
points.o:	points.h
quickhull.o:	points.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm $(OBJFILES) jarvis.o quickhull.o core 2> /dev/null

realclean:        clean
	-/bin/rm -rf jarvis quickhull 

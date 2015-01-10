# Make file for the ABC Tool Box:
# This does not make an executable, it only creates the object files.

# The names of all of the "tools":
TOOLLIST=

# %_OBJ & %_LIB hold, respecively, all the objects and libraries used
# to create % from TOOLLIST, all tools in TOOLLIST must have both.


# Compiler Varaibles:
CXX=gcc
CXXFLAGS=-Wall -MMD -std=c++11

# Is it possible to link in libraries ahead of time,
# As well as join the partally made objects together?
LINK=ld
LINKFLAGS=-Ur

# Directory names:
# Intermediate objects
INTDIR=.tmp
# Completed objects
OBJDIR=objects
# Code Directory
CODEDIR=private

# Special Rules:
.PHONY : all
.SECONDEXPANSION :

# Internal Varaibles.
FIN_OBJ=$(patsubst %,$(INTDIR)/$(TOOLLIST).o)
ALL_OBJ=$(sort $(suffix $(foreach tool,$(TOOLLIST),$(tool_OBJ)),.o))

# Rules:
all : $(TOOLLIST)

$(TOOLLIST) : $$($$@_OBJ)
#object : $(object_OBJ)
#	$(LINK) $(LINKFLAGS) $^ $(object_LIB) -o $@

# Missing the evaluation of all the object lists
$(ALL_OBJ) : $$(subs $$@

# Directory creation. Only INTDIR should ever have to be made.
$(INTDIR) $(OBJDIR) $(CODEDIR) :
	mkdir $@

# Flow:
# List of tools to compile in TOOLLIST. Get the objects the depend of from the
# header files of the same name and compile them into object files of the same
# name (basename in both cases).
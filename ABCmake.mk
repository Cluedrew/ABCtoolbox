# Make file for the ABC Tool Box:
# This does not make an executable, it only creates the object files.

# The names of all of the "tools":
TOOLLIST=

# %_OBJ & %_LIB hold, respecively, all the objects and libraries used to create %.



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

# Transform TOOLLIST into a usable form.

# Rules:
all : $(TOOLLIST)

$(TOOLLIST) : $$@_OBJ
#object : $(object_OBJ)
#	$(LINK) $(LINKFLAGS) $^ $(object_LIB) -o $@

# Missing the evaluation of all the object lists
$(sort $(suffix $(TOOLLIST),_OBJ)) : $$(subs $$@

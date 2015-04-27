# Make file for the ABC Tool Box:
# Not currantly working, WIP

# See DevManual.txt for details.

# The names of all of the tools.
TOOLLIST= hello-world



# Access Link Varibles:
LINKDIR=/usr/local/include
LINKNAME=$(LINKDIR)/ABC
LINKDEST=/home/cluedrew/ABCtoolbox/include # *
# The system is likely to be replaced eventually with a proper install.
# * This should be replaced that finds the location of this file, so it always
#   gets the correct location of /include.



# Compiler Varaibles:
CXX=gcc
CXXFLAGS=-Wall -MMD -std=c++11

# Link Varibles:
LINK=ld
LINKFLAGS=-Ur

# Directory names:
# Code/Source Directory, holds raw files not created by make.
SORDIR=code
# Object/Intermediate Directory, files both generated and used by make
#   which are mostly objects. Also a temperary file.
OBJDIR=.obj
# Library/Target Directory, holds the end results of make.
LIBDIR=include



# Special Rules:
.PHONY : all clean $(TOOLLIST)
.SECONDEXPANSION :

# Misc Varibles:
# All .cpp Files
ALLCPP= $(wildcard $(SORDIR)/*/*.cpp)
# Intermediate Objects
INTOBJ= $(patsubst $(SORDIR)%.cpp,$(OBJDIR)%.o,$(ALLCPP))
# Finished or Linked Objects
FINOBJ= $(patsubst %,$(OBJDIR)/%.o,$(TOOLLIST))
# Dependancy Files
DEPEND= $(INTOBJ:.o=.d)
# Creates a *_OBJ varible for each tool. Each varible holds the intermediate
#   objects for that tool.
$(foreach tool,$(TOOLLIST), \
	$(eval $(tool)_OBJ= $(filter $(OBJDIR)/$(tool)/%.o,$(INTOBJ))))

# Functions:
# Turns the names of tools it is given to the names of the tool's final
#   files, toollib is the library file, toolhead is the public header and
#   end files produces both.
endfiles= $(foreach tool,$(1),$(LIBDIR)/$(tool).hpp $(LIBDIR)/lib$(tool).a)
toollib = $(foreach tool,$(1),$(LIBDIR)/lib$(tool).a)
toolhead= $(foreach tool,$(1),$(LIBDIR)/$(tool).hpp)
# Expands to the contents of the file $(1) if file exists.
#   If the file does not exist expands to the empty string.
safecat= $(shell [ -e $(1) ] && cat $(1))



### Rules:

# Default rule, updates all tools.
all : $(TOOLLIST)

# Tool level rule, create all final files for a tool.
$(TOOLLIST) : $(LIBDIR)/$$@.hpp $(LIBDIR)/lib$$@.a

# Create the static library in the include directory.
$(LIBDIR)/lib%.a : $(OBJDIR)/%.o | $(LIBDIR)
	ar rcs $@ $<

# Copy the public header over to the include directory.
$(LIBDIR)/%.hpp : $(SORDIR)/%/$$*.hpp | $(LIBDIR)
	cp $< $@

# Rule for final objects (objects generated by linking)
$(FINOBJ) : $(OBJDIR)/%.o : $$($$*_OBJ) | $(OBJDIR)
	$(LINK) $(LINKFLAGS) $^ $(call safecat, $(SORDIR)/$*/libs) -o $@

# Rule for intermediate objects (objects created from code)
$(INTOBJ) : $(OBJDIR)/%.o : $(SORDIR)/%.cpp | $(OBJDIR)/$$(dir $$*)
	$(CXX) $(CXXFLAGS) -c $< -o $@



# Rules for link creation and destruction.
# Might require special permitions.
link : $(LINKNAME)

delink :
	rm $(LINKNAME)

$(LINKNAME) :
	ln --symbolic -T $(LINKDEST) $@



# Directory creation.
$(OBJDIR) $(LIBDIR) : ; mkdir $@
$(patsubst %,$(OBJDIR)/%/,$(TOOLLIST)) : | $(OBJDIR) ; mkdir $@



# Add dependancy files.
-include $(DEPEND)

# clean phony rule. Removes all intermetiate files.
clean :
	-rm $(OBJDIR)/*/*.o
	-rm $(OBJDIR)/*/*.d
	-rm $(OBJDIR)/*.o
	-rmdir $(OBJDIR)/*
	-rmdir $(OBJDIR)

# deepclean phony rule. Removes all generated files.
deepclean : clean
	-rm $(call endfiles,$(TOOLLIST))
	-rmdir $(LIBDIR)

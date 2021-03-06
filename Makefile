# Make file for the ABC Tool Box:
# See DevManual.txt for details.



# The names of all of the tools.
TOOLLIST= hello-world filter-it



### Main Variable Declaration:
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
# Testing Directory, not part of main process, has the tests and the test
#   programs which are used to test the compliled tools.
TSTDIR=test



### Special Rules:
.PHONY : all clean deepclean $(TOOLLIST) link delink
.SECONDEXPANSION :



### Functions:
# Expands to the contents of the file $(1) if file exists.
#   If the file does not exist expands to the empty string.
safecat= $(shell [ -e $(1) ] && cat $(1))

# Turns the names of tools it is given to the names of the tool's final
#   files, toollib is the library file, toolhead is the public header and
#   end files produces both.
endfiles= $(foreach tool,$(1),$(LIBDIR)/$(tool).hpp $(LIBDIR)/lib$(tool).a)
toollib = $(foreach tool,$(1),$(LIBDIR)/lib$(tool).a)
toolhead= $(foreach tool,$(1),$(LIBDIR)/$(tool).hpp)

# If $(1) exists than produce the name of $(2).
exists_echo=$(shell [ -e $(1) ] && echo $(2))
# For a tool $(1), produce the name of a destination file if it source exists.
exists_hpp=$(call exists_echo,$(SORDIR)/$(1)/$(1).hpp,$(LIBDIR)/$(1).hpp)
exists_cpp=$(call exists_echo,$(SORDIR)/$(1)/$(1).cpp,$(LIBDIR)/lib$(1).a)
exists_tpp=$(call exists_echo,$(SORDIR)/$(1)/$(1).tpp,$(LIBDIR)/$(1).tpp)
# For a tool $(1), produce all destination files with existing sources.
exists_all=$(foreach dest,hpp cpp tpp,$(call exists_$(dest),$(1)))



### Created Varibles:
# All .cpp Files
ALLCPP= $(wildcard $(SORDIR)/*/*.cpp)
# Intermediate Objects
INTOBJ= $(patsubst $(SORDIR)%.cpp,$(OBJDIR)%.o,$(ALLCPP))
# Finished or Linked Objects
FINOBJ= $(patsubst %,$(OBJDIR)/%.o,$(TOOLLIST))
# Dependancy Files
DEPEND= $(INTOBJ:.o=.d)

# Creates a *_TARGET variable for each tool. Each variable holds the final
#   targets assosated with each tool.
$(foreach tool,$(TOOLLIST), \
	$(eval $(tool)_TARGET= $(call exists_all,$(tool))))

# Creates a *_OBJ varible for each tool. Each varible holds the intermediate
#   object files for that tool.
$(foreach tool,$(TOOLLIST), \
	$(eval $(tool)_OBJ= $(filter $(OBJDIR)/$(tool)/%.o,$(INTOBJ))))



### Rules:

# Default rule, updates all tools.
all : $(TOOLLIST)

# Tool level rule, create all final files for a tool.
$(TOOLLIST) : $$($$@_TARGET)

# Create the static library in the include directory.
$(LIBDIR)/lib%.a : $(OBJDIR)/%.o | $(LIBDIR)
	ar rcs $@ $<

# Copy the public header over to the include directory.
$(LIBDIR)/%.hpp : $(SORDIR)/%/$$*.hpp | $(LIBDIR)
	cp $< $@

# Copy the template file over to the include directory.
$(LIBDIR)/%.tpp : $(SORDIR)/%/$$*.tpp | $(LIBDIR)
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
	-rm $(foreach tool,$(TOOLLIST),$($(tool)_TARGET))
	-rmdir $(LIBDIR)

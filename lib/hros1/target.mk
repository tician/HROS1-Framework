.SUFFIXES:

#ifndef _ARCH
#_ARCH := $(shell print_arch)
#export _ARCH
#endif

#OBJDIR := _$(_ARCH)obj
#OBJDIR := _obj
OBJDIR := ../_hros1_blobs

ifndef MAKECMDGOALS
MAKECMDGOALS = all
endif

#MAKETARGET = $(MAKE) --no-print-directory -C $@ -f $(CURDIR)/makefile \
#				SRCDIR=$(CURDIR) $(MAKECMDGOALS)
MAKETARGET = $(MAKE) -w -C $@ -f $(CURDIR)/makefile \
				SRCDIR=$(CURDIR) $(MAKECMDGOALS)

.PHONY: $(OBJDIR)
$(OBJDIR):
#	@echo $(OBJDIR)
#	@echo $(CURDIR)
#	@echo $(SRCDIR)
	+@[ -d $@ ] || mkdir -p $@
	+@$(MAKETARGET)

Makefile : ;
%.mk :: ;
% :: $(OBJDIR) ; :

.PHONY: clean
clean:
	rm -rf $(OBJDIR)


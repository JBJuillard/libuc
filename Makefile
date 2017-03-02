#
# Makefile for Undefined-C library
#
# Created: 01/29/2017 by Juillard Jean-Baptiste
# Updated: 02/23/2017 by Juillard Jean-Baptiste
#
# This file is a part of free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation; either version 3, or
# (at your option) any later version.
#
# There is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; see the file LICENSE.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street, Fifth
# Floor, Boston, MA 02110-1301, USA.
#


# Default value
SHELL = /bin/sh
override EMPTY :=
CD := $(shell pwd)
.DEFAULT_GOAL := help
prefix = /usr/local
TARGET_ARCH = $(shell echo $$CPUTYPE)


# Flags for recursive call of make
MFLAGS_DEFAULT := --no-print-directory --warn-undefined-variables
MFLAGS := $(EMPTY)
override MFLAGS += $(filter-out $(MAKEFLAGS),$(MFLAGS_DEFAULT))


# Project
NAME = uc


# Default directory name
SRC_PATH = src
INC_PATH = include
MAN_PATH = man
ASM_PATH = asm
OBJ_PATH = obj
LIB_PATH = lib
DBG_PATH = dbg
TEST_PATH = tests
BIN_PATH = bin
LOG_PATH = log
UTILS_PATH = utils
EXAMPLES_PATH = examples


# Source files
SRC =	slst_new.c slst_delelm.c \
		slst_len.c slst_isempty.c \
		slst_previous.c slst_next.c \
		slst_head.c slst_tail.c \
		slst_put.c slst_putn.c \
		slst_get.c slst_getn.c \
		slst_del.c slst_deln.c slst_delp.c slst_delk.c \
		slst_purge.c \
		slst_nsrt.c slst_nsrtn.c slst_nsrtp.c slst_nsrtk.c \
		slst_xtrc.c slst_xtrcn.c slst_xtrcp.c slst_xtrck.c \
		slst_rch.c slst_rrch.c slst_xrch.c slst_rxrch.c \
		slst_cmp.c slst_rcmp.c slst_diff.c slst_rdiff.c \
		slst_cpy.c slst_rcpy.c \
		slst_rev.c \
		slst_cat.c \
		slst_cut.c slst_cutn.c slst_cutp.c slst_cutk.c \
		slst_map.c \
		\
		mslst_purge.c
SRC_FULLPATH = $(addprefix $(SRC_PATH)/,$(SRC))


# Include files
INC =	stdlst.h
INC_FULLPATH = $(addprefix $(INC_PATH)/,$(INC))
INC_INSTALLPATH = $(prefix)/include
INC_INSTALLFULLPATH = $(addprefix $(INC_INSTALLPATH)/,$(INC))


# Assembly files
#
# ASM_EXTENSION can be defined as 's', 'S' or 'asm'
ASM_EXTENSION = S
# ASM_DIALECT must be defined as 'att' or 'intel'
ASM_DIALECT = att
ASM = $(patsubst %.c,%.$(ASM_EXTENSION),$(SRC))
ASM_FULLPATH = $(addprefix $(ASM_PATH)/,$(ASM))


# Object files
OBJ = $(patsubst %.c,%.o,$(SRC))
OBJ_FULLPATH = $(addprefix $(OBJ_PATH)/,$(OBJ))


# Static Library
A_NAME = lib$(NAME).a
A_PATH = $(LIB_PATH)
A_FULLPATH = $(addprefix $(A_PATH)/,$(A_NAME))


# Dynamic Library
SO_MAJOR_VERSION = $(shell cat VERSION | tr -d "$$IFS" | awk 'BEGIN {FS="."} {print $$1}')
SO_MINOR_VERSION = $(shell cat VERSION | tr -d "$$IFS" | awk 'BEGIN {FS="."} {print $$2}')
SO_RELEASE_VERSION = $(shell cat VERSION | tr -d "$$IFS" | awk 'BEGIN {FS="."} {print $$3}')
SO_NAME = lib$(NAME).so
SO_SONAME = $(SO_NAME).$(SO_MAJOR_VERSION)
SO_FULLNAME = $(SO_SONAME).$(SO_MINOR_VERSION).$(SO_RELEASE_VERSION)
SO_PATH = $(LIB_PATH)
SO_FULLPATH = $(SO_PATH)/$(SO_FULLNAME)
SO_INSTALLPATH = $(prefix)/lib
SO_INSTALLFULLPATH =	$(SO_INSTALLPATH)/$(SO_FULLNAME)


# Manpages and documentation
MAN_SECTION = 3
MAN =	$(patsubst %.c,%.$(MAN_SECTION),$(SRC))
MAN_FULLPATH = $(addprefix $(MAN_PATH)/man$(MAN_SECTION)/,$(MAN))
MAN_INSTALLPATH = $(prefix)/man
MAN_INSTALLPATH_MAN = $(MAN_INSTALLPATH)/man$(MAN_SECTION)
MAN_INSTALLPATH_HTML = $(MAN_INSTALLPATH)/html$(MAN_SECTION)
MAN_INSTALLPATH_PDF = $(MAN_INSTALLPATH)/pdf$(MAN_SECTION)
MAN_INSTALLPATH_PS = $(MAN_INSTALLPATH)/ps$(MAN_SECTION)
MAN_INSTALLFULLPATH_MAN = $(addprefix $(MAN_INSTALLPATH_MAN)/,$(MAN))


# Variables overriding filter
OVERRIDES_FILTER =	OPTIMIZATION_LEVEL=% \
					CFLAGS=% \
					CMACRO=% \
					OBJ_PATH=% \
					ASM_PATH=% \
					A_PATH=% \
					SO_PATH=%


# Debugging
DBG_OVERRIDES =	"OPTIMIZATION_LEVEL=g" \
				"CFLAGS=$(CFLAGS)  $(filter-out $(CFLAGS),$(CFLAGS_DEBUG))" \
				"CMACRO=$(CMACRO) $(CMACRO_DEBUG)" \
				"OBJ_PATH=$(DBG_PATH)/$(OBJ_PATH)" \
				"ASM_PATH=$(DBG_PATH)/$(ASM_PATH)" \
				"LIB_PATH=$(DBG_PATH)/$(LIB_PATH)"
DBG_OVERRIDES += $(filter-out $(OVERRIDES_FILTER),$(MAKEOVERRIDES))


# Test
TEST = $(patsubst %.c,%,$(SRC))
TEST_FULLPATH = $(addprefix $(TEST_PATH)/$(BIN_PATH)/,$(TEST))
TEST_OBJ = $(addsuffix .o,$(TEST))
TEST_OBJ_FULLPATH = $(addprefix $(TEST_PATH)/$(OBJ_PATH)/,$(TEST_OBJ))
TEST_OVERRIDES =	"OPTIMIZATION_LEVEL=g" \
					"CFLAGS=$(CFLAGS) $(filter-out $(CFLAGS),$(CFLAGS_DEBUG))" \
					"CMACRO=$(CMACRO) $(CMACRO_DEBUG)" \
					"OBJ_PATH=$(TEST_PATH)/$(OBJ_PATH)" \
					"ASM_PATH=$(TEST_PATH)/$(ASM_PATH)" \
					"LIB_PATH=$(TEST_PATH)/$(LIB_PATH)"
TEST_OVERRIDES += $(filter-out $(OVERRIDES_FILTER),$(MAKEOVERRIDES))
TEST_MAINFILE = $(TEST_PATH)/$(SRC_PATH)/main.c
TEST_SUCCESSFILE = $(addsuffix .log,$(TEST))
TEST_SUCCESSFILE_FULLPATH = $(addprefix $(TEST_PATH)/$(LOG_PATH)/,$(TEST_SUCCESSFILE))
TEST_SIZE_N = 1000000


# C Compiler
OPTIMIZATION_LEVEL = 3
CC =  /usr/bin/gcc
CFLAGS = $(EMPTY)
override CFLAGS_BASEFLAGS := $(filter-out $(CFLAGS),-Wall -Wextra -Werror)
CFLAGS += $(CFLAGS_BASEFLAGS)
CFLAGS_PIC = -fPIC
CFLAGS_OPTIMIZE = -O
CFLAGS_INCLUDE = -I
CFLAGS_LIBNAME = -l
CFLAGS_LIBPATH = -L
CFLAGS_ASM = -S -masm=$(ASM_DIALECT) -fverbose-asm
CFLAGS_OBJ = -c
CFLAGS_SO = -shared -Wl,-soname,$(SO_SONAME)
CFLAGS_OUTPUT = -o
CFLAGS_MACRO = -D
CFLAGS_DEBUG = -g
CFLAGS_BASEINC := $(filter-out $(CFLAGS),$(CFLAGS_INCLUDE)./$(INC_PATH))
CFLAGS += $(CFLAGS_BASEINC)
CMACRO = $(EMPTY)
CMACRO_DEBUG = \"DEBUG=1\"


# Linker
LD = /usr/bin/ld
LDFLAGS =
LDLIBS =


# Dynamic link editor
LDCONFIG = /sbin/ldconfig
LDCONFIGFLAGS = -n


# Static library archiver
AR = /usr/bin/ar
ARFLAGS = -rc


# Archiver indexer
RANLIB = /usr/bin/ranlib
RANLIBFLAGS = -t


# Documentation generation
MAKEINFO = /usr/bin/makeinfo
MAKEINFO_OUTPUT_DOCBOOK =  --docbook
MAKEINFO_OUTPUT_HTML =  --html
MAKEINFO_OUTPUT_XML =  --xml
MAKEINFO_OUTPUT_PLAINTEXT =  --plaintext
MAKEINFO_OUTPUT_DVI =  --dvi
MAKEINFO_OUTPUT_PDF =  --pdf
MAKEINFO_OUTPUT_PS =  --ps


# BISON = bison
# FLEX = flex
# LEX = lex
# TEXT2DVI = texi2dvi
# YACC = yacc


# Installation
INSTALL = /usr/bin/install
INSTALLFLAGS := $(EMPTY)
INSTALLFLAGS_MODE = -m
INSTALLFLAGS_DIRACLS = 644
INSTALLFLAGS_FILEACLS = 644
INSTALLFLAGS_EXECFILEACLS = 755
INSTALLFLAGS_DIRTARGET = -d
INSTALLFLAGS_RECDIRTARGET = -t
INSTALLFLAGS_FILETARGET = -T


# Memory error detector
MEMCHK = /usr/bin/valgrind
MEMCHKFLAGS = -v --leak-check=full --leak-check-heuristics=all --track-origins=yes --show-leak-kinds=all
override MEMCHK_EXITCODE = 1
override MEMCHKFLAGS += --error-exitcode=$(MEMCHK_EXITCODE)
MEMCHKFLAGS_LOG = --log-file=


# Execution Time and Timeout
TIME = /usr/bin/time
TIME_FORMAT =
TIMEFLAGS_FORMAT = -f
TIMEFLAGS_LOG = --output=
TIMEFLAGS = $(EMPTY)
TIMEOUT = /usr/bin/timeout
TIMEOUT_DELAY = 1


# Bin Utils
CPY = /bin/cp
CPY_FLAGS = -uv
RM = /bin/rm
RM_DIR_FLAGS = -Rfv
RM_FILE_FLAGS = -fv
MD = /bin/mkdir
MD_FLAGS = -pv
LN = /bin/ln
LN_SLNKFLAGS = -sf
CHMOD = /bin/chmod


# Git
GIT_URL = https://github.com/JBJuillard/libuc.git


# Protect phony rules
.PHONY:	help \
		make make-asm make-obj make-a \
		clean mostlyclean distclean maintainer-clean \
		clean-obj clean-asm clean-a clean-so \
		install install-strip install-html install-dvi \
		install-pdf install-ps installdirs installcheck \
		uninstall uninstall-strip uninstall-html uninstall-dvi \
		uninstall-pdf uninstall-ps uninstallcheck \
		re all\
		dbg dbg-obj dbg-asm dbg-a dbg-clean dbg-distclean \
		check check-make check-clean check-distclean check-prompt \
		git-clone git-push git-pull update



# Define suffixes list
.SUFFIXES:
.SUFFIXES:	.h .c .$(ASM_EXTENSION) .o .a .so .so.$(SO_MAJOR_VERSION) \
			.so.$(SO_MAJOR_VERSION).$(SO_MINOR_VERSION) \
			.so.$(SO_MAJOR_VERSION).$(SO_MINOR_VERSION).$(SO_RELEASE_VERSION) \
			.$(MAN_SECTION) .html .dvi .pdf .ps \
			.conf


# ====================
# Standart target
# ====================
#
# all
# install install-html install-dvi install-pdf install-ps
# uninstall install-strip
# clean distclean mostlyclean maintainer-clean
# TAGS
# info
# html dvi pdf ps
# dist
# check(test)
# installdirs installcheck
#
# ====================
# A faire
# ====================
#
# help
# TAGS
# info
# html dvi pdf ps
# dist


# User help (default rule)
help:
	@echo "usage: make {rule_0} [... rule_N] [macro]";
	@echo;
	@echo "rules:";
	@echo "\thelp\t\tPrint this help.";
	@echo "\tmake\t\tMake dynamic library.";
	@echo "\t$(NAME)\t\tMake dynamic library (same as make rule).";


# Make rules
make: make-obj $(SO_FULLPATH)
make-asm: $(ASM_FULLPATH)
make-obj: $(OBJ_FULLPATH)
make-a: make-obj | $(A_PATH)
	$(AR) $(ARFLAGS) $(A_FULLPATH) $(OBJ_FULLPATH)
	$(RANLIB) $(RANLIBFLAGS) $(A_FULLPATH)


# Workspace cleaning rules
clean: clean-obj clean-asm
mostlyclean: clean-asm
distclean: clean clean-a clean-so
maintainer-clean: distclean dbg-distclean  check-distclean
clean-obj:
	@if [ -e $(OBJ_PATH) ] ; then \
		$(RM) $(RM_DIR_FLAGS) $(OBJ_PATH) ; \
	fi
clean-asm:
	@if [ -e $(ASM_PATH) ] ; then \
		$(RM) $(RM_DIR_FLAGS) $(ASM_PATH) ; \
	fi
clean-a:
	@if [ -e $(A_FULLPATH) -a ! -e $(SO_FULLPATH) ] ; then \
		$(RM) $(RM_DIR_FLAGS) $(LIB_PATH) ; \
	elif [ -e $(A_FULLPATH) ] ; then \
		$(RM) $(RM_FILE_FLAGS) $(A_FULLPATH) ; \
	fi
clean-so:
	@if [ -e $(SO_FULLPATH) -a ! -e $(A_FULLPATH) ] ; then \
		$(RM) $(RM_DIR_FLAGS) $(LIB_PATH) ; \
	elif [ -e $(SO_FULLPATH) ] ; then \
		$(RM) $(RM_FILE_FLAGS) $(SO_FULLPATH) ; \
		if [ -e $(SO_PATH)/$(SO_NAME) ] ; then \
			$(RM) $(RM_FILE_FLAGS) $(SO_PATH)/$(SO_NAME) ; \
		fi ; \
		if [ -e $(SO_PATH)/$(SO_SONAME) ] ; then \
			$(RM) $(RM_FILE_FLAGS) $(SO_PATH)/$(SO_SONAME) ; \
		fi ; \
	fi


# Install library and manpages
# /usr/local/lib, /usr/local/include, /usr/local/man
install: $(MAN_INSTALLFULLPATH_MAN) $(INC_INSTALLFULLPATH) $(SO_INSTALLFULLPATH)
	$(LDCONFIG) $(LDCONFIGFLAGS) $(SO_INSTALLPATH)
	@cd $(SO_INSTALLPATH) ; \
	$(LN) $(LN_SLNKFLAGS) $(SO_FULLNAME) $(SO_NAME) ; \
	$(CHMOD) --reference=$(SO_FULLNAME) $(SO_NAME) ; \
	$(CHMOD) --reference=$(SO_FULLNAME) $(SO_SONAME)
#install-strip:
#install-html:
#install-dvi:
#install-pdf:
#install-ps:
installdirs: | $(MAN_INSTALLPATH_MAN) $(INC_INSTALLPATH) $(SO_INSTALLPATH)
installcheck:
uninstall:
	@$(RM) $(RM_FILE_FLAGS) $(MAN_INSTALLFULLPATH_MAN)
	@$(RM) $(RM_FILE_FLAGS) $(INC_INSTALLFULLPATH)
	@$(RM) $(RM_FILE_FLAGS) $(SO_INSTALLPATH)/$(SO_NAME)
	@$(RM) $(RM_FILE_FLAGS) $(SO_INSTALLPATH)/$(SO_SONAME)
	@$(RM) $(RM_FILE_FLAGS) $(SO_INSTALLFULLPATH)
	$(LDCONFIG) $(LDCONFIGFLAGS) $(SO_INSTALLPATH)
#uninstall-strip:
#uninstall-html:
#uninstall-dvi:
#uninstall-pdf:
#uninstall-ps:


# Remake dynamic library
re: distclean make
# Make dynamic library, install library and clean compilation's workspace
all: make install clean


# Debugging rules
dbg:
	@$(MAKE) $(MFLAGS) make $(DBG_OVERRIDES)
dbg-obj:
	@$(MAKE) $(MFLAGS) make-obj $(DBG_OVERRIDES) 
dbg-asm:
	@$(MAKE) $(MFLAGS) make-asm $(DBG_OVERRIDES)
dbg-a:
	@$(MAKE) $(MFLAGS) make-a $(DBG_OVERRIDES)
dbg-clean:
	@$(MAKE) $(MFLAGS) clean $(DBG_OVERRIDES)
dbg-distclean:
	@$(MAKE) $(MFLAGS) distclean $(DBG_OVERRIDES)
	@if [ -e $(DBG_PATH) ] ; then \
		$(RM) $(RM_DIR_FLAGS) $(DBG_PATH) ; \
	fi


# Test rules
check: check-make $(TEST_FULLPATH) $(TEST_SUCCESSFILE_FULLPATH)
check-make:
	@$(MAKE) $(MFLAGS) make $(TEST_OVERRIDES)
	@cd $(TEST_PATH)/$(SO_PATH) ; \
	$(LN) $(LN_SLNKFLAGS) $(SO_FULLNAME) $(SO_NAME) ; \
	$(LN) $(LN_SLNKFLAGS) $(SO_FULLNAME) $(SO_SONAME)
check-clean:
	@$(MAKE) $(MFLAGS) clean $(TEST_OVERRIDES)
check-distclean:
	@$(MAKE) $(MFLAGS) distclean $(TEST_OVERRIDES)
	@if [ -e $(TEST_PATH)/$(BIN_PATH) ] ; then \
		$(RM) $(RM_DIR_FLAGS) $(TEST_PATH)/$(BIN_PATH) ; \
	fi
	@if [ -e $(TEST_PATH)/$(LOG_PATH) ] ; then \
		$(RM) $(RM_DIR_FLAGS) $(TEST_PATH)/$(LOG_PATH) ; \
	fi
check-prompt:
	@echo "\n\n\033[0;36;40mUnits tests for Undefined-C Library\033[0m\n\nTest with N = $(TEST_SIZE_N)\n"


# Repository update and local update rules
git-clone:
git-push:
git-pull:


# Object files rules
$(OBJ_FULLPATH): | $(OBJ_PATH)
$(OBJ_PATH):
	@$(MD) $(MD_FLAGS) $@
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	$(CC) $(CFLAGS_OBJ) $(CFLAGS_PIC) $(CFLAGS) $(CFLAGS_OPTIMIZE)$(OPTIMIZATION_LEVEL) $(addprefix $(CFLAGS_MACRO),$(CMACRO)) $(CFLAGS_OUTPUT) $@ $<


# Assembly files rules
$(ASM_FULLPATH): | $(ASM_PATH)
$(ASM_PATH):
	@$(MD) $(MD_FLAGS) $@
$(ASM_PATH)/%.$(ASM_EXTENSION): $(SRC_PATH)/%.c
	$(CC) $(CFLAGS_ASM) $(CFLAGS_PIC) $(CFLAGS) $(CFLAGS_OPTIMIZE)$(OPTIMIZATION_LEVEL) $(addprefix $(CFLAGS_MACRO),$(CMACRO)) $(CFLAGS_OUTPUT) $@ $<


# Shared object file rules
$(SO_FULLPATH): | $(SO_PATH)
$(SO_FULLPATH): $(OBJ_FULLPATH)
	$(CC) $(CFLAGS_PIC) $(CFLAGS_SO) $(CFLAGS) $(CFLAGS_OPTIMIZE)$(OPTIMIZATION_LEVEL) $(CFLAGS_OUTPUT) $@ $(OBJ_FULLPATH)
$(SO_PATH):
	@$(MD) $(MD_FLAGS) $@


# Test rules
$(TEST_FULLPATH): | $(TEST_PATH)/$(BIN_PATH)
$(TEST_PATH)/$(BIN_PATH):
	@$(MD) $(MD_FLAGS) $@
$(TEST_PATH)/$(BIN_PATH)/%: CFLAGS += $(CFLAGS_INCLUDE)./$(TEST_PATH)/$(INC_PATH)
$(TEST_PATH)/$(BIN_PATH)/%: CFLAGS += $(CFLAGS_OPTIMIZE)g
$(TEST_PATH)/$(BIN_PATH)/%: CFLAGS += $(CFLAGS_DEBUG)
$(TEST_PATH)/$(BIN_PATH)/%: CFLAGS += $(CFLAGS_LIBNAME)$(NAME)
$(TEST_PATH)/$(BIN_PATH)/%: CFLAGS += $(CFLAGS_LIBPATH)./$(TEST_PATH)/$(SO_PATH)
$(TEST_PATH)/$(BIN_PATH)/%: CMACRO += INTERFACE_FUNCTION=ut_$(*F)_interface
$(TEST_PATH)/$(BIN_PATH)/%: CMACRO += MEMCHK_FUNCTION=ut_$(*F)_memchk
$(TEST_PATH)/$(BIN_PATH)/%: CMACRO += TIMEOUT_FUNCTION=ut_$(*F)_timeout
$(TEST_PATH)/$(BIN_PATH)/%: CMACRO += $(shell echo -n $(CMACRO_DEBUG))
$(TEST_PATH)/$(BIN_PATH)/%: TEST_MAINFILE += $(TEST_PATH)/$(SRC_PATH)/ut_$(*F).c
$(TEST_PATH)/$(BIN_PATH)/%: TEST_MAINFILE += $(TEST_PATH)/$(SRC_PATH)/extra.c
$(TEST_PATH)/$(BIN_PATH)/%: $(TEST_PATH)/$(SRC_PATH)/ut_%.c
	$(CC) $(CFLAGS) $(addprefix $(CFLAGS_MACRO),$(CMACRO)) $(CFLAGS_OUTPUT) $@ $(TEST_MAINFILE)
$(TEST_SUCCESSFILE_FULLPATH): | $(TEST_PATH)/$(LOG_PATH)
$(TEST_SUCCESSFILE_FULLPATH): | check-prompt
$(TEST_PATH)/$(LOG_PATH):
	@$(MD) $(MD_FLAGS) $@
$(TEST_PATH)/$(LOG_PATH)/%.log: MEMCHKFLAGS += $(MEMCHKFLAGS_LOG)$(TEST_PATH)/$(LOG_PATH)/$(*F).memchk
$(TEST_PATH)/$(LOG_PATH)/%.log: TIMEFLAGS += $(TIMEFLAGS_LOG)$(TEST_PATH)/$(LOG_PATH)/$(*F).time
$(TEST_PATH)/$(LOG_PATH)/%.log: $(TEST_PATH)/$(BIN_PATH)/% $(SRC_PATH)/%.c $(TEST_PATH)/$(SRC_PATH)/ut_%.c
	@export LD_LIBRARY_PATH=./$(TEST_PATH)/$(SO_PATH) ; \
	echo -n "\033[s$(*F)\033[u\033[50C" ; \
	echo -n "\033[s\033[K[ \033[0;34;40mFunction Interface Test\033[0m ]\033[u" ; \
	$(TEST_PATH)/$(BIN_PATH)/$(*F) 1 $(TEST_SIZE_N) ; \
	ERR=$$? ; \
	if [ $$ERR -ne 0 ] ; then \
		echo "\033[s\033[K[ \033[0;31;40mFunction Interface Error: $$ERR\033[0m ]\033[u\t" ; \
		exit ; \
	fi ; \
	echo -n "\033[s\033[K[ \033[0;34;40mMemory Test\033[0m ]\033[u" ; \
	$(MEMCHK) $(MEMCHKFLAGS) $(TEST_PATH)/$(BIN_PATH)/$(*F) 2 $(TEST_SIZE_N) ; \
	ERR=$$? ; \
	if [ $$ERR -eq $(MEMCHK_EXITCODE) ] ; then \
		echo "\033[s\033[K[ \033[0;31;40mMemory Leak\033[0m ]\033[u\t" ; \
		exit ; \
	elif [ $$ERR -ne 0 ] ; then \
		echo "\033[s\033[K[ \033[0;31;40mMemory Error: $$ERR\033[0m ]\033[u\t" ; \
		exit ; \
	fi ; \
	echo -n "\033[s\033[K[ \033[0;34;40mTimeout Test\033[0m ]\033[u" ; \
	$(TIME) $(TIMEFLAGS) $(TIMEOUT) $(TIMEOUT_DELAY)s $(TEST_PATH)/$(BIN_PATH)/$(*F) 3 $(TEST_SIZE_N) ; \
	ERR=$$? ; \
	if [ $$ERR -eq 124 ] ; then \
		echo "\033[s\033[K[ \033[0;31;40mTimeout occurs\033[0m ]\033[u\t" ; \
		exit ; \
	elif [ $$ERR -ne 0 ] ; then \
		echo "\033[s\033[K[ \033[0;31;40mTimeout Error: $$ERR\033[0m ]\033[u" ; \
		exit ; \
	fi ; \
	echo "\033[s\033[K[ \033[0;32;40mOk\033[0m ]\033[u" ; \
	touch $@; \
	echo "\nUnits tests log file of $(*F)" >> $@ ; \
	echo "\n\nInterface test:\n\n\tFunction interface work properly." >> $@ ; \
	echo "\n\nMemory test:\n" >> $@ ; \
	export MEMCHK_LINE=`/bin/grep -n 'HEAP SUMMARY' $(@D)/$(*F).memchk | /usr/bin/awk 'BEGIN {FS=":"} END {print $$1}'` ; \
	/usr/bin/tail -n +$$MEMCHK_LINE $(@D)/$(*F).memchk | /bin/sed -E s/==\[0-9\]+==\ */\	/ >> $@ ; \
	/bin/rm $(@D)/$(*F).memchk ; \
	echo "\n\nExecution time and timeout test:\n" >> $@ ; \
	/bin/cat $(@D)/$(*F).time | /usr/bin/awk 'BEGIN {FS="\n";ORS=""} {print "\t";print $$1;print "\n"}' >> $@ ; \
	echo "\tTimeout don't occur." >> $@ ; \
	/bin/rm $(@D)/$(*F).time


# Installation rules
$(MAN_INSTALLPATH_MAN)/%: INSTALLFLAGS += $(INSTALLFLAGS_MODE)$(INSTALLFLAGS_FILEACLS)
$(MAN_INSTALLPATH_MAN)/%: | $(MAN_INSTALLPATH_MAN)
$(MAN_INSTALLPATH_MAN)/%: man/man$(MAN_SECTION)/%
	$(INSTALL) $(INSTALLFLAGS) $(INSTALLFLAGS_FILETARGET) $< $@
$(MAN_INSTALLPATH_MAN):
	@$(MD) $(MD_FLAGS) $@
$(MAN_INSTALLPATH_MAN)/slst_putn.$(MAN_SECTION):
	@cd $(MAN_INSTALLPATH_MAN) ; \
	$(LN) $(LN_SLNKFLAGS) slst_put.$(MAN_SECTION) $(@F)
$(MAN_INSTALLPATH_MAN)/slst_getn.$(MAN_SECTION):
	@cd $(MAN_INSTALLPATH_MAN) ; \
	$(LN) $(LN_SLNKFLAGS) slst_get.$(MAN_SECTION) $(@F)
$(MAN_INSTALLPATH_MAN)/slst_deln.$(MAN_SECTION):
	@cd $(MAN_INSTALLPATH_MAN) ; \
	$(LN) $(LN_SLNKFLAGS) slst_del.$(MAN_SECTION) $(@F)
$(MAN_INSTALLPATH_MAN)/slst_delk.$(MAN_SECTION):
	@cd $(MAN_INSTALLPATH_MAN) ; \
	$(LN) $(LN_SLNKFLAGS) slst_del.$(MAN_SECTION) $(@F)
$(MAN_INSTALLPATH_MAN)/slst_delp.$(MAN_SECTION):
	@cd $(MAN_INSTALLPATH_MAN) ; \
	$(LN) $(LN_SLNKFLAGS) slst_del.$(MAN_SECTION) $(@F)
$(MAN_INSTALLPATH_MAN)/slst_nsrtn.$(MAN_SECTION):
	@cd $(MAN_INSTALLPATH_MAN) ; \
	$(LN) $(LN_SLNKFLAGS) slst_nsrt.$(MAN_SECTION) $(@F)
$(MAN_INSTALLPATH_MAN)/slst_nsrtp.$(MAN_SECTION):
	@cd $(MAN_INSTALLPATH_MAN) ; \
	$(LN) $(LN_SLNKFLAGS) slst_nsrt.$(MAN_SECTION) $(@F)
$(MAN_INSTALLPATH_MAN)/slst_nsrtk.$(MAN_SECTION):
	@cd $(MAN_INSTALLPATH_MAN) ; \
	$(LN) $(LN_SLNKFLAGS) slst_nsrt.$(MAN_SECTION) $(@F)
$(MAN_INSTALLPATH_MAN)/slst_xtrcn.$(MAN_SECTION):
	@cd $(MAN_INSTALLPATH_MAN) ; \
	$(LN) $(LN_SLNKFLAGS) slst_xtrc.$(MAN_SECTION) $(@F)
$(MAN_INSTALLPATH_MAN)/slst_xtrcp.$(MAN_SECTION):
	@cd $(MAN_INSTALLPATH_MAN) ; \
	$(LN) $(LN_SLNKFLAGS) slst_xtrc.$(MAN_SECTION) $(@F)
$(MAN_INSTALLPATH_MAN)/slst_xtrck.$(MAN_SECTION):
	@cd $(MAN_INSTALLPATH_MAN) ; \
	$(LN) $(LN_SLNKFLAGS) slst_xtrc.$(MAN_SECTION) $(@F)
$(MAN_INSTALLPATH_MAN)/slst_rrch.$(MAN_SECTION):
	@cd $(MAN_INSTALLPATH_MAN) ; \
	$(LN) $(LN_SLNKFLAGS) slst_rch.$(MAN_SECTION) $(@F)
$(MAN_INSTALLPATH_MAN)/slst_rxrch.$(MAN_SECTION):
	@cd $(MAN_INSTALLPATH_MAN) ; \
	$(LN) $(LN_SLNKFLAGS) slst_xrch.$(MAN_SECTION) $(@F)
$(MAN_INSTALLPATH_MAN)/slst_rcmp.$(MAN_SECTION):
	@cd $(MAN_INSTALLPATH_MAN) ; \
	$(LN) $(LN_SLNKFLAGS) slst_cmp.$(MAN_SECTION) $(@F)
$(MAN_INSTALLPATH_MAN)/slst_rdiff.$(MAN_SECTION):
	@cd $(MAN_INSTALLPATH_MAN) ; \
	$(LN) $(LN_SLNKFLAGS) slst_diff.$(MAN_SECTION) $(@F)
$(MAN_INSTALLPATH_MAN)/slst_next.$(MAN_SECTION):
	@cd $(MAN_INSTALLPATH_MAN) ; \
	$(LN) $(LN_SLNKFLAGS) slst_previous.$(MAN_SECTION) $(@F)
$(MAN_INSTALLPATH_MAN)/slst_tail.$(MAN_SECTION):
	@cd $(MAN_INSTALLPATH_MAN) ; \
	$(LN) $(LN_SLNKFLAGS) slst_head.$(MAN_SECTION) $(@F)
$(MAN_INSTALLPATH_MAN)/slst_rcpy.$(MAN_SECTION):
	@cd $(MAN_INSTALLPATH_MAN) ; \
	$(LN) $(LN_SLNKFLAGS) slst_cpy.$(MAN_SECTION) $(@F)
$(MAN_INSTALLPATH_MAN)/slst_cutn.$(MAN_SECTION):
	@cd $(MAN_INSTALLPATH_MAN) ; \
	$(LN) $(LN_SLNKFLAGS) slst_cut.$(MAN_SECTION) $(@F)
$(MAN_INSTALLPATH_MAN)/slst_cutp.$(MAN_SECTION):
	@cd $(MAN_INSTALLPATH_MAN) ; \
	$(LN) $(LN_SLNKFLAGS) slst_cut.$(MAN_SECTION) $(@F)
$(MAN_INSTALLPATH_MAN)/slst_cutk.$(MAN_SECTION):
	@cd $(MAN_INSTALLPATH_MAN) ; \
	$(LN) $(LN_SLNKFLAGS) slst_cut.$(MAN_SECTION) $(@F)
$(INC_INSTALLPATH)/%: INSTALLFLAGS += $(INSTALLFLAGS_MODE)$(INSTALLFLAGS_FILEACLS)
$(INC_INSTALLPATH)/%: | $(INC_INSTALLPATH)
$(INC_INSTALLPATH)/%: $(INC_PATH)/%
	$(INSTALL) $(INSTALLFLAGS) $(INSTALLFLAGS_FILETARGET) $< $@
$(INC_INSTALLPATH):
	@$(MD) $(MD_FLAGS) $@
$(SO_INSTALLPATH)/%: INSTALLFLAGS += $(INSTALLFLAGS_MODE)$(INSTALLFLAGS_EXECFILEACLS)
$(SO_INSTALLPATH)/%: | $(SO_INSTALLPATH)
$(SO_INSTALLPATH)/%: $(SO_PATH)/%
	$(INSTALL) $(INSTALLFLAGS) $(INSTALLFLAGS_FILETARGET) $< $@
$(SO_INSTALLPATH):
	@$(MD) $(MD_FLAGS) $@

#
# A Makefile that compiles all .c and .s files in "src" and "res" 
# subdirectories and places the output in a "obj" subdirectory
#

# If you move this project you can change the directory 
# to match your GBDK root directory (ex: GBDK_HOME = "C:/GBDK/"
ifndef GBDK_HOME
	GBDK_HOME = ../../../
endif

LCC = $(GBDK_HOME)bin/lcc 
PNG2ASSET = $(GBDK_HOME)bin/png2asset 

# GBDK_DEBUG = ON
ifdef GBDK_DEBUG
	LCCFLAGS += -debug -v
endif

# From: https://stackoverflow.com/questions/3774568/makefile-issue-smart-way-to-scan-directory-tree-for-c-files
# Make does not offer a recursive wildcard function, so here's one:
rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))


# You can set the name of the .gb ROM file here
PROJECTNAME    = SuperMarioLand

SRCDIR      = src
OBJDIR      = obj
RESDIR      = res
GENDIR      = gen
BINS	    = $(OBJDIR)/$(PROJECTNAME).gb

# How to recursively find all files that match a pattern
CSOURCES := $(call rwildcard,$(SRCDIR)/,*.c)   $(call rwildcard,$(GENDIR)/,*.c) 

LCCFLAGS += -Iinclude -Iheaders -Igen -autobank

all:	prepare png2asset $(BINS)

png2asset: png2asset-backgrounds png2asset-sprites


png2asset-backgrounds:
	$(PNG2ASSET) $(RESDIR)/backgrounds/World1Tileset.png -c $(GENDIR)/World1Tileset.c -b 255 -map -keep_palette_order -noflip
	$(PNG2ASSET) $(RESDIR)/backgrounds/World1Area1.png -c $(GENDIR)/World1Area1.c -b 255 -source_tileset $(RESDIR)/backgrounds/World1Tileset.png  -map -keep_palette_order -noflip

png2asset-sprites:
	$(PNG2ASSET) $(RESDIR)/sprites/MarioSprites.png -c $(GENDIR)/MarioSprites.c -b 255 -spr8x16 -keep_palette_order -noflip -sw 16 -sh 32

compile.bat: Makefile
	@echo "REM Automatically generated from Makefile" > compile.bat
	@make -sn | sed y/\\//\\\\/ | sed s/mkdir\ -p\/mkdir\/ | grep -v make >> compile.bat


# Link the compiled object files into a .gb ROM file
$(BINS):	$(CSOURCES)
	$(LCC) $(LCCFLAGS) -Wm-yt3 -Wm-yoA -Wm-ya1 -o $(BINS) $(CSOURCES) 

prepare:
	mkdir -p $(OBJDIR)
	mkdir -p $(GENDIR)

clean:
#	rm -f  *.gb *.ihx *.cdb *.adb *.noi *.map
	rm -f  $(OBJDIR)/*.*
	rm -f  $(GENDIR)/*.*


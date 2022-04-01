SRCS = yamldecode.cc yamlencode.cc
OCTS = $(SRCS:.cc=.oct)

MKOCTFILE ?= mkoctfile

all: $(OCTS)

%.oct: %.cc
	$(MKOCTFILE) $< -o $@

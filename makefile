PROG=MakeComplexAr
SRCS=main.c X.c ar.c
OBJS=$(SRCS:%.c=%.c.o)
ALLDEP=$(MAKEFILE_LIST)

INFILE?=/dev/stdin
RM?=rm -rf
WC?=wc -lc

OPTFLAGS?=-Wall -Wextra -ansi -pedantic

all: $(PROG)

$(PROG): $(OBJS) $(ALLDEP)
	$(LINK.o) $(OUTPUT_OPTION) $(OBJS)

%.c.o: %.c $(ALLDEP)
	$(COMPILE.c) $(OUTPUT_OPTION) $(OPTFLAGS) $<

run: $(PROG)
	./$(PROG) <$(INFILE)

.PHONY: clean
clean:
	$(RM) $(PROG) $(OBJS)

.PHONY: line
line:
	$(WC) $(SRCS) $(MAKEFILE_LIST)

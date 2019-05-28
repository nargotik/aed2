SUBDIRS := $(wildcard src/*/.)

all: aed2
aed2:
	$(MAKE) -C ./src/aed2;\
	EXIT_CODE=$$?;\
	echo "Compiler exited with $$EXIT_CODE";\
	exit $$EXIT_CODE
clean:
	find bin/. ! -name 'readme.md' -type f -exec rm -f {} +
.PHONY: $(TOPTARGETS) $(SUBDIRS) aed2

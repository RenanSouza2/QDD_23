DIRS := $(wildcard */.)

LIB_FILES = $(foreach DIR,$(DIRS),$(dir $(DIR))lib.o)
DGB_FILES = $(foreach DIR,$(DIRS),$(dir $(DIR))debug.o)

DGB_MEM_PATH = ../static_utils/mem_report
DGB_MEM_FILE = $(DGB_MEM_PATH)/bin/lib.o

build: lib.o



lib.o: $(LIB_FILES)
	ld -r -o $@ $^
	
debug.o: $(DGB_FILES) $(DGB_MEM_FILE)
	ld -r -o $@ $^



.PHONY: $(LIB_FILES)
$(LIB_FILES):
	$(MAKE) --directory=$(dir $@)

.PHONY: $(DGB_FILES)
$(DGB_FILES):
	$(MAKE) debug.o --directory=$(dir $@)

.PHONY: $(DGB_MEM_FILE)
$(DGB_MEM_FILE):
	echo "Fetching mem_report"
	$(MAKE) --directory=$(DGB_MEM_PATH)



.PHONY: clean
clean:
	rm -rf *.o
	for DIR in $(DIRS) ; do \
		( $(MAKE) clean --directory=$$DIR ) || exit $$? ; \
	done

.PHONY: test
test:
	for DIR in $(DIRS) ; do \
		( $(MAKE) test --directory=$$DIR ) || exit $$? ; \
	done

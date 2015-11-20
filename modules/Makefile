METERS ?= 
LINUX_SRC ?= undefined
TARGETS = common $(METERS)
OBJECTS = $(addsuffix .o,$(TARGETS))

.PHONY: all
all: module

.PHONY: targets
targets:
	rm -f Kbuild_inc
	touch Kbuild_inc
	for target in $(TARGETS); \
	do \
		echo "include \$$(src)/$$target/Kbuild" >> Kbuild_inc; \
	done
	echo $(TARGETS)

.PHONY: clean
clean: module_clean
	rm -f Kbuild_inc

.PHONY: module 
module: targets
	$(MAKE) OBJECTS=$(OBJECTS) -C $(LINUX_SRC) M=$(CURDIR) modules

.PHONY: module_clean
module_clean: targets
	$(MAKE) OBJECTS=$(OBJECTS) -C $(LINUX_SRC) M=$(CURDIR) clean

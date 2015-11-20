METERS ?= ph
LINUX_SRC ?= undefined
TARGETS = common $(METERS)
OBJECTS = $(addsuffix .o,$(TARGETS))

.PHONY: all
all: module

#Sets up our Kbuild_inc file
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
	#Set up our init defines before starting the module build
	EXTERNS=""; INITS="{"; NUMMETERS=0; for meter in $(METERS); do \
		NUMMETERS=`echo $$NUMMETERS + 1 | bc`; \
		EXTERNS="$$EXTERNS extern meter_dev_t $${meter}_meter_dev;" ; \
		INITS="$$INITS &$${meter}_meter_dev," ; \
	done ; INITS="$$INITS }" ; echo "$$EXTERNS"; echo "$$INITS"; echo $$NUMMETERS; \
	$(MAKE) METER_INITS="$$INITS" METER_EXTERNS="$$EXTERNS" METER_NUM=$$NUMMETERS OBJECTS="$(OBJECTS)" -C $(LINUX_SRC) M=$(CURDIR) modules

.PHONY: module_clean
module_clean: targets
	$(MAKE) OBJECTS="$(OBJECTS)" -C $(LINUX_SRC) M=$(CURDIR) clean

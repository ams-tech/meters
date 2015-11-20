LINUX_SRC=$(CURDIR)/linux

.PHONY: all
all: modules

.PHONY: clean
clean: clean_modules
	rm -rf build

install:
	echo "Directory 'install' does not exist.  Creating it..."
	mkdir -p install

linux:
	$(error Directory "linux" does not exist.  You should probably make a symlink to a linux source directory)

.PHONY: modules
modules: linux
	mkdir -p build/modules
	$(MAKE) LINUX_SRC=$(LINUX_SRC) -C modules

.PHONY: clean_modules
clean_modules:
	make -C modules LINUX_SRC=$(LINUX_SRC) clean

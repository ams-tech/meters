LINUX_SRC=$(CURDIR)/linux

.PHONY: all
all: modules apps

.PHONY: clean
clean: clean_modules clean_apps
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

.PHONY: apps
apps:
	$(MAKE) -C apps

.PHONY: clean_modules
clean_modules:
	$(MAKE) -C modules LINUX_SRC=$(LINUX_SRC) clean

.PHONY: clean_apps
clean_apps:
	$(MAKE) -C apps clean

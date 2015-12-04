TARGETS = meter_test
BUILD_DIR = build

.PHONY: all
all: $(TARGETS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

.PHONY: $(TARGETS)
$(TARGETS): $(BUILD_DIR)
	$(MAKE) -C $@ 
	cp $@/$@ $(BUILD_DIR)/.

.PHONY: clean
clean:
	for t in $(TARGETS); do \
		$(MAKE) -C $$t clean; \
	done;
	rm -rf $(BUILD_DIR)

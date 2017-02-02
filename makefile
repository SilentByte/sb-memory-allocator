

SB_BUILD_DIR:=sb/build
SB_TEST_RUNNABLES:=$(wildcard $(SB_BUILD_DIR)/bin/tests/*tests)

.PHONY: all
all:
	mkdir -p $(SB_BUILD_DIR)
	cd $(SB_BUILD_DIR) && cmake ..
	make -C $(SB_BUILD_DIR)

.PHONY: clean
clean:
	rm -rf $(SB_BUILD_DIR)

.PHONY: tests
test: all
	$(foreach test,$(SB_TEST_RUNNABLES),$(test))


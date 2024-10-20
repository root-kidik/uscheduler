CLANG_FORMAT ?= clang-format

# Format the sources
.PHONY: format
format:
	find src include -name '*pp' -type f | xargs $(CLANG_FORMAT) -i

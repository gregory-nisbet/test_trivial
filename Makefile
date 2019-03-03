CLANGXX := clang++
CLANG   := clang
GCCXX   := g++-8
GCC     := gcc-8

INCLUDE_DIRS  := $(shell find ./include -type d)
INCLUDE_FLAGS := $(addprefix -I,$(INCLUDE_DIRS))

CFLAGS   := $(CFLAGS) $(INCLUDE_FLAGS) -Wall -Werror -pedantic -Wextra
CXXFLAGS := $(CFLAGS) $(INCLUDE_FLAGS) -Wall -Werror -pedantic -Wextra

PROJ  := $(PWD)
TESTS := $(PROJ)/tests

TESTS_SRCS := $(shell find $(TESTS) -type f)

export CLANGXX
export CLANG
export GCCXX
export GCC
export PROJ
export TESTS
export TESTS_SRCS
export CFLAGS
export CXXFLAGS
export CPPFLAGS
export LDFLAGS

.NOTMAIN: build-tests
.PHONY: build-tests
build-tests: $(TESTS_SRCS) obj/Makefile
	cd obj && $(MAKE) -f Makefile $(addsuffix .t,$(notdir $(TESTS_SRCS)))

.NOTMAIN: test-once
.PHONY: test-once
test-once: build-tests
	bash test-once.bash

.PHONY: test
test:
	bash test.bash

.NOTMAIN: obj/Makefile
obj/Makefile : obj.mk
	mkdir -p obj
	cp obj.mk obj/Makefile

.NOTMAIN: clean
.PHONY: clean
clean:
	cd obj && $(RM) *.cpp.t *.c.t

.NOTMAIN: realclean
.PHONY: realclean
realclean:
	find ./obj -delete ||true
	rmdir obj ||true

.NOTMAIN: format
.PHONY: format
format:
	find ./include ./tests -type f | grep '[.](h\|c\|cpp)$$' | xargs -I% clang-format -i --style=WebKit %

.NOTMAIN: show-tests
.PHONY: show-tests
show-tests:
	@cd obj && $(MAKE) show-tests

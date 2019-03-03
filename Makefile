PROJ  := $(PWD)
TESTS := $(PROJ)/tests

INCLUDE_DIRS  := $(shell find $(PROJ)/include $(PROJ)/vendor -type d)
INCLUDE_FLAGS := $(addprefix -I,$(INCLUDE_DIRS))

ifndef CFLAGS_SET
CFLAGS   :=   $(CFLAGS) $(INCLUDE_FLAGS) -Wall -Werror -pedantic -Wextra
CFLAGS_SET := t
endif

ifndef CXXFLAGS_SET
CXXFLAGS := $(CXXFLAGS) $(INCLUDE_FLAGS) -Wall -Werror -pedantic -Wextra
CXXFLAGS_SET := t
endif


TESTS_SRCS := $(shell find $(TESTS) -type f -name '*.c' -o -name '*.cpp')

export PROJ
export TESTS
export TESTS_SRCS
export CFLAGS
export CXXFLAGS
export CPPFLAGS
export LDFLAGS
export CFLAGS_SET
export CXXFLAGS_SET

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
	find ./include ./tests ./vendor -type f | xargs -I% clang-format -i --style=WebKit %

.NOTMAIN: show-tests
.PHONY: show-tests
show-tests:
	@cd obj && $(MAKE) show-tests

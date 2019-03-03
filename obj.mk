%.cpp.t : $(TESTS)/cxx/%.cpp
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS)

%.c.t   : $(TESTS)/c/%.c
	$(CC)  -o $@ $^ $(CFLAGS)   $(LDFLAGS)

.NOTMAIN : show-tests
.PHONY: show-tests
show-tests:
	@for item in ./*.t; do \
	  ./"$$item" ; \
	done

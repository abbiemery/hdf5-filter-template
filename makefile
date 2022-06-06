CC:= gcc

OBJDIR = build
DISTDIR = dist

CFLAGS:= -Wall -fPIC -g -O0 --std=gnu89

# You only need these if you installed hdf5 somewhere seperate.
# If your hdf5 is installed normally, remove the following three lines,
# line 34 (export) and their macros in the compiler calls,line 30,35 and 39. 
INCDIR:= -I/path/to/other/usr/include
LIBDIR:= -L/path/to/other/usr/lib
LIB:= -lhdf5

INCDIRDEV:= -I/path/to/this/dir/hdf5-filter-template/dist

HFILES:= $(wildcard *.h)
CFILES:= $(wildcard *.c)
OBJFILES:= $(patsubst %.c,$(OBJDIR)/%.o,$(CFILES))

.PHONY : all lib ex clean

all: $(OBJFILES)

$(OBJFILES): | $(OBJDIR)
$(OBJDIR):
	mkdir $(OBJDIR)

$(OBJDIR)/%.o: %.c $(HFILES) $(CFILES)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCDIR) $(LIBDIR) $(LIB)

lib: $(OBJFILES)
	mkdir -p $(DISTDIR)
	export LD_LIBRARY_PATH=/path/to/other/usr/lib
	$(CC) $(CFLAGS) $(OBJFILES) -shared -o $(DISTDIR)/libh5pass.so $(INCDIR) $(LIBDIR) $(LIB)
	cp $(HFILES) $(DISTDIR)

ex: 
	$(CC) $(CFLAGS) -o example/example_usingFilters example/example_usingFilters.c $(INCDIR) $(LIBDIR) $(LIB) $(INCDIRDEV)

clean:
	rm -rf $(OBJDIR)
	rm -rf $(DISTDIR)
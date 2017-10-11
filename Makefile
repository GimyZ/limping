cc = gcc
source = test.c
out =test 
CINCLUDE = -L./png/prebuilt/mac -L./zlib/prebuilt/mac  -lpng -lz
CFLAGS = -Wall -I./png/include/mac  -I./zlib/include/mac
all:$(source)
	 $(cc) $(CFLAGS) $(CINCLUDE) -v $(source) -o $(out)

clean:
	rm -f $(out) 

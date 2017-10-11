cc = gcc
source = main.c
out =test 
CINCLUDE = -L./png/prebuilt/mac -L./zlib/prebuilt/mac  -lpng -lz
CFLAGS = -Wall -I./png/include/mac  -I./zlib/include/mac
all:$(source)
	 $(cc) $(CFLAGS) $(CINCLUDE)  $(source) -o $(out)

clean:
	rm -f $(out) 

.PHONY: all clean

BINS = hlgenerator hldetector
OBJS_hlgenerator = hlgenerator.o strlcat.o common.o
OBJS_hldetector = hldetector.o strlcat.o hlparser.o common.o

all: $(BINS)

clean:
	rm -f *.o $(BINS)

hlgenerator: $(OBJS_hlgenerator)
	$(CC) -o $@ $(OBJS_hlgenerator)

hldetector: $(OBJS_hldetector)
	$(CC) -o $@ $(OBJS_hldetector)

%.o: %.c
	$(CC) -c $<

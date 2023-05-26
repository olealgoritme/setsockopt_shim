CC=clang
BINS=socket_shim.so
CFLAGS=-Wall
all: $(BINS)

%.so: %.c
	$(CC) $(CFLAGS) -shared -fPIC -o $@ $^ -ldl
clean:
	rm -f $(BINS)

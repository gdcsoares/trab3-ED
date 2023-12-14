CC = gcc
CFLAGS = -g -lm
LDFLAGS = 

# Listagem de arquivos-fonte comuns
COMMON_SRCS = hash.c forward_list.c node.c vector.c

# Listagem de arquivos de cabeçalho comuns
COMMON_HEADERS = hash.h forward_list.h node.h vector.h

# Programa 1
PROGRAMA1_SRCS = main_idx.c index.c $(COMMON_SRCS)
PROGRAMA1_OBJS = $(PROGRAMA1_SRCS:.c=.o)
PROGRAMA1_HEADERS = index.h $(COMMON_HEADERS)
PROGRAMA1_BIN = main_idx

# Programa 2
PROGRAMA2_SRCS = main_search.c search.c $(COMMON_SRCS)
PROGRAMA2_OBJS = $(PROGRAMA2_SRCS:.c=.o)
PROGRAMA2_HEADERS = search.h $(COMMON_HEADERS)
PROGRAMA2_BIN = main_search

all: $(PROGRAMA1_BIN) $(PROGRAMA2_BIN)

$(PROGRAMA1_BIN): $(PROGRAMA1_OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

$(PROGRAMA2_BIN): $(PROGRAMA2_OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c $(COMMON_HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(PROGRAMA1_BIN) $(PROGRAMA2_BIN) $(PROGRAMA1_OBJS) $(PROGRAMA2_OBJS)

run_main_idx: $(PROGRAMA1_BIN)
	./$(PROGRAMA1_BIN)

run_main_search: $(PROGRAMA2_BIN)
	./$(PROGRAMA2_BIN)

.PHONY: all clean run_main_idx run_main_search
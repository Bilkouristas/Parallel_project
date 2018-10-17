
GCC = gcc
CFLAGS = -pthread -O3

CMAIN=qsort

all: qsort-main.o qsort-sequential.o parqsort.o
	$(GCC) $(CFLAGS) $^ -o $(CMAIN)

%.o: %.c
	$(GCC) -c $(CFLAGS) $^

clean:
	rm -f *.o *~ $(CMAIN)


# all: qsort-main.o qsort-sequential.o parqsort.o
# 	$(GCC) $(CFLAGS) $^ -o $(CMAIN)
#
# qsort-sequential.o: qsort-sequential.c
# 	$(GCC) -c -pthread $(CFLAGS) $^
#
# # parqsort.o: parqsort.c qsort-main.o qsort-sequential.o
# # 	gcc -pthread -O3 -o $@ $^

# clean:
# 	rm -f *.o *~ $(CMAIN)

cc=gcc 
LIBS=-lpthread
WARNING_FLAGS= -Wall -Wextra

EXE=prodcomm
SCAN_BUILD_DIR=scan-build-out


all:main.o reader.o munch1.o munch2.o writer.o queue.o 
	$(CC) -o $(EXE) main.o reader.o munch1.o munch2.o writer.o queue.o $(LIBS)

main.o:main.c reader.h munch1.h munch2.h writer.h queue.h
	$(CC) $(WARNING_FLAGS) -c main.c $(LIBS)

reader.o: reader.c reader.h
	$(CC) $(WARNING_FLAGS) -c reader.c $(LIBS)

munch1.o:munch1.c munch1.h
	$(CC) $(WARNING_FLAGS) -c munch1.c $(LIBS)

munch2.o:munch2.c munch2.h
	$(CC) $(WARNING_FLAGS) -c munch2.c $(LIBS)

writer.o: writer.c writer.h
	$(CC) $(WARNING_FLAGS) -c writer.c $(LIBS)

queue.o:queue.c queue.h
	$(CC) $(WARNING_FLAGS) -c queue.c $(LIBS)

pthread.o:pthread.c
	$(CC) $(WARNING_FLAGS) -c pthread.c $(LIBS)
clean:
	rm -f $(EXE) *.o
	rm -rf $(SCAN_BUILD_DIR)

scan-build:clean
	scan-build -o $(SCAN_BUILD_DIR) make

scan-view: scan-build
	firefox -new -window $(SCAN_BUILD_DIR) /*/index.html

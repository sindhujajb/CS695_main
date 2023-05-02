CC=gcc
CFLAGS= -lcurl -lm -I. -DBBBW -DSHELLPRINT -DHTTP
DEPS = core/cs695/basics.h  core/cs695/connectServer/gpio/gpio.c core/cs695/connectServer/apache/simpleBBB.c core/cs695/data/vol/internal.h core/cs695/data/bme280/bme280.h
OBJ = core/cs695/basics.o  core/cs695/connectServer/gpio/gpio.o core/cs695/connectServer/apache/simpleBBB.o core/cs695/data/vol/internal.o core/cs695/data/bme280/bme280.o  main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

BeagleboneB-HTTP: $(OBJ)
	@echo "\nCompiling..."
	$(CC) -o $@ $^ $(CFLAGS) 
	@echo "\nCompiled Finished, now you can run your code with: '$ ./BeagleboneB-HTTP'\n"
	@$ find . -name "*.o" -type f -delete

help:
	@echo "\n'make' to compile"
	@echo "'make clean' to delete .o files\n"

.PHONY: clean
clean:
	@$ find . -name "*.o" -type f -delete

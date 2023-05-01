CC=gcc
CFLAGS= -lcurl -lm -I. -DBBBW -DSHELLPRINT -DHTTP
DEPS = core/beaglebonebw/basics.h core/beaglebonebw/peripherals/gpio/simpleBBB_GPIO.c core/beaglebonebw/peripherals/gpio/gpio.c core/beaglebonebw/peripherals/i2c/simpleBBB_I2C.c core/beaglebonebw/sensors/internal/internal.h core/beaglebonebw/sensors/bme280/bme280.h core/beaglebonebw/protocols/http/http.h
OBJ = core/beaglebonebw/basics.o core/beaglebonebw/peripherals/gpio/simpleBBB_GPIO.o core/beaglebonebw/peripherals/gpio/gpio.o core/beaglebonebw/peripherals/i2c/simpleBBB_I2C.o core/beaglebonebw/sensors/internal/internal.o core/beaglebonebw/sensors/bme280/bme280.o  core/beaglebonebw/protocols/http/http.o main.o

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

# raspbian_SDK makefile

PROG = RASPBRY
OBJS = board.o cli_uart.o spi.o
INC=-I/home/pi/CC3100/cc3100-sdk/simplelink/include -I/home/pi/CC3100/cc3100-sdk/simplelink/source -I/home/pi/CC3100/cc3100-sdk/platform/raspbian_SDK -I/home/pi/CC3100/cc3100-sdk/examples/spi_debug_tool -I/usr/local/include
CC =gcc
CFLAGS = $(INC) -c

.SUFFIXES = .c

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROG)
	
%.o: %.c $(INC)
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm -f *~ $(OBJS) $(PROG)

#End of simplelink source makefile
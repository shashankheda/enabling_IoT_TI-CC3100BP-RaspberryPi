# main makefile spi_debug_tool

PROG = SPIDEB
OBJS = main.o RASPBRY
#OBJS = main.o RASPBRY SIMP_SRC
OBJS_OTHER = /home/pi/CC3100/cc3100-sdk/platform/raspbian_SDK/board.o \
/home/pi/CC3100/cc3100-sdk/platform/raspbian_SDK/cli_uart.o \
/home/pi/CC3100/cc3100-sdk/platform/raspbian_SDK/spi.o \
#/home/pi/CC3100/cc3100-sdk/simplelink/source/driver.o \
#/home/pi/CC3100/cc3100-sdk/simplelink/source/device.o \
#/home/pi/CC3100/cc3100-sdk/simplelink/source/flowcont.o \
#/home/pi/CC3100/cc3100-sdk/simplelink/source/fs.o \
#/home/pi/CC3100/cc3100-sdk/simplelink/source/netapp.o \
#/home/pi/CC3100/cc3100-sdk/simplelink/source/netcfg.o \
#/home/pi/CC3100/cc3100-sdk/simplelink/source/nonos.o \
#/home/pi/CC3100/cc3100-sdk/simplelink/source/socket.o \
#/home/pi/CC3100/cc3100-sdk/simplelink/source/spawn.o \
#/home/pi/CC3100/cc3100-sdk/simplelink/source/wlan.o \

INC=-I/home/pi/CC3100/cc3100-sdk/platform/raspbian_SDK -I/home/pi/CC3100/cc3100-sdk/examples/spi_debug_tool -I/usr/local/include
#INC=-I/home/pi/CC3100/cc3100-sdk/simplelink/include -I/home/pi/CC3100/cc3100-sdk/simplelink/source -I/home/pi/CC3100/cc3100-sdk/platform/raspbian_SDK -I/home/pi/CC3100/cc3100-sdk/examples/spi_debug_tool -I/usr/local/include
CC =gcc
CFLAGS =-lwiringPi -L/usr/local/lib $(INC) 

.SUFFIXES = .c

$(PROG): $(OBJS)
	$(CC) -o $(PROG) main.o $(OBJS_OTHER) $(CFLAGS)
#	export LD_LIBRARY_PATH=/home/pi/CC3100/cc3100-sdk/platform/raspbian_SDK:$LD_LIBRARY_PATH
#	export LD_LIBRARY_PATH=/home/pi/CC3100/cc3100-sdk/simplelink/source:$LD_LIBRARY_PATH
	
%.o: %.c $(INC)
	$(CC) $(CFLAGS) -c $< -o $@ 

RASPBRY:
	cd /home/pi/CC3100/cc3100-sdk/platform/raspbian_SDK ; make RASPBRY;

#IMP_SRC:
#	cd /home/pi/CC3100/cc3100-sdk/simplelink/source ; make SIMP_SRC;

clean:
	rm -f *~ $(OBJS)
	cd /home/pi/CC3100/cc3100-sdk/platform/raspbian_SDK ; make clean
#	cd /home/pi/CC3100/cc3100-sdk/simplelink/source ; make clean

#End of simplelink source makefile
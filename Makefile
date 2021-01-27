
LIB_SRCS = string.cpp port.cpp ip.cpp field.cpp  # library source files
LIB_DST = firewall
EXEC = firewall.exe
EXTERN_LIB = input

CC = g++  # C compiler
CFLAGS = -Wall -Wextra -L. -g #-O2 -g  # C flags
RM = rm -f   # rm command


all:${EXEC}

$(LIB_DST):
	$(CC) ${CFLAGS} -fPIC -shared ${LIB_SRCS} -o lib${LIB_DST}.so


${EXEC}: ${LIB_DST} 
	$(CC) ${CFLAGS} main.cpp -o ${EXEC} -l$(LIB_DST) -l$(EXTERN_LIB)


clean:
	-${RM} ${EXEC} ${LIB_DST} 
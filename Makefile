include config.mk

SRC = cons.c err.c node.c ssc.c util.c
OBJ = ${SRC:.c=.o}

all: options ssc

options:
	@echo scc build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	${CC} -c ${CFLAGS} $<

${OBJ}: config.mk

ssc: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f ssc ${OBJ}

.PHONY: all options clean

CC = gcc
ifdef ComSpec
  SEP2=\\
  MD = mkdirp.bat
  RM = del /F /Q
  RD = rd /S /Q
  CREATE = @(echo ^@echo off & echo ^IF EXIST %%1 GOTO END & echo ^MKDIR %%1 & echo ^:END)> mkdirp.bat
else
  SEP2=/
  MD = mkdir -p
  RM = rm -rf
  RD = rm -rf
  CREATE = 
endif

SEP=$(strip $(SEP2))


ODIR = .$(SEP)build
IDIR = .

CFLAGS=-I$(IDIR)


_DEPS = arvore_b.h cliente.h lista_clientes.h metadados.h no.h lista_nos.h ufftest.h
DEPS = $(patsubst %,$(IDIR)$(SEP)%,$(_DEPS))

_OBJ = arvore_b.o cliente.o lista_clientes.o metadados.o no.o lista_nos.o test_arvore_b.o
OBJ = $(patsubst %,$(ODIR)$(SEP)%,$(_OBJ))

$(ODIR)$(SEP)%.o: $(IDIR)$(SEP)%.c $(DEPS)
	${CREATE}
	${MD} $(ODIR)
	${CC} -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	${CC} -o $(ODIR)$(SEP)$@ $^ $(CFLAGS)

.PHONY: clean

clean:
	${RM} *~ mkdirp.bat
	${RD} $(ODIR)$(SEP)

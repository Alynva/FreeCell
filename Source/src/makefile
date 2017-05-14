# Compilador
CC = g++

# Flags de versao
C_VERSION = -std=c++0x

# Arquivo principal
OBJ_FILE = main.cpp

# Arquivos auxiliares
AUX_FILES = textura.cpp carta.cpp baralho.cpp eventmanager.cpp pilha_inteligente.cpp

# Flags do compilador
CC_FLAGS = -g -Wall

# Linkers do compilador
CC_LINKERS = -lmingw32 -L"../lib"  -lSDL2main -lSDL2_image -lSDL2_mixer -lSDL2

# Arquivo de saída
OUT_FILE = ./freecell.out

all:
	$(CC) $(C_VERSION) $(OBJ_FILE) $(AUX_FILES) $(CC_FLAGS) $(CC_LINKERS) -o $(OUT_FILE)

clean:
	rm $(OUT_FILE)

run:
	$(OUT_FILE)

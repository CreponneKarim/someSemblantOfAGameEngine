external_dependencies=-lglfw -ldl -lassimp -lstdc++fs
CFLAGS=-c
output_file=run
CVERSION=-std=c++17
CC=g++ -g
CURRENTDIR=$(shell pwd)
INCLUDES=-I$(CURRENTDIR)

objDir=obj_files
libsDir=libs
srcDir=src
includesDir=include/someSemblantOfAGameEngine
seekCFiles=$(wildcard $(1)/*.c)
seekCPPFiles=$(wildcard $(1)/*.cpp)
objFiles=$(patsubst $(1)/%.cpp,$(objDir)/%.o,$(call seekCPPFiles,$(1)))
objFiles+=$(patsubst $(1)/%.c,$(objDir)/%.o,$(call seekCFiles,$(1)))

all:$(call objFiles,$(libsDir)) $(call objFiles,$(includesDir)) $(call objFiles,$(srcDir))
	@echo ">>all"
	$(CC) $(CVERSION) $(INCLUDES) $^ -o $(output_file) $(external_dependencies)
	@echo ">>make end"
#libs
$(objDir)/%.o:$(libsDir)/%.c $(libsDir)/%.h
	@echo ">>libs"
	$(CC) $(CVERSION) $(CFLAGS) $(INCLUDES) $(filter $(libsDir)/%.c,$^) -o $@ $(external_dependencies)
$(objDir)/%.o:$(libsDir)/%.cpp $(libsDir)/%.h
	@echo ">>libs"
	$(CC) $(CVERSION) $(CFLAGS) $(INCLUDES) $(filter $(libsDir)/%.cpp,$^) -o $@ $(external_dependencies)

$(objDir)/%.o:$(libsDir)/%.c
	@echo ">>libs"
	$(CC) $(CVERSION) $(CFLAGS) $(INCLUDES) $(filter $(libsDir)/%.c,$^) -o $@ $(external_dependencies)

#includes
$(objDir)/%.o:$(includesDir)/%.cpp $(includesDir)/%.hpp
	@echo ">>includes"
	$(CC) $(CVERSION) $(CFLAGS) $(INCLUDES) $(filter $(includesDir)/%.cpp,$^) -o $@ $(external_dependencies)

#src
$(objDir)/%.o:$(srcDir)/%.cpp $(srcDir)/%.hpp
	@echo ">>src"	
	$(CC) $(CVERSION) $(CFLAGS) $(INCLUDES) $(filter $(srcDir)/%.cpp,$^) -o $@ $(external_dependencies)


clean:
	rm -f $(objDir)/*.o
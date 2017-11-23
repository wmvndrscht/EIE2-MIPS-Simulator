###################################################
## MIPS Compilation path

MIPS_CC = mips-linux-gnu-gcc
MIPS_OBJCOPY = mips-linux-gnu-objcopy

# Turn on all warnings, and enable optimisations
MIPS_CPPFLAGS = -W -Wall -O3 -fno-builtin

# Avoid standard libraries etc. being brought in, and link statically
MIPS_LDFLAGS = -nostdlib -Wl,-melf32btsmip -march=mips1 -nostartfiles -mno-check-zero-division -Wl,--gpsize=0 -static -Wl,-Bstatic
MIPS_LDFLAGS += -Wl,--build-id=none

# Compile an assembly file into a MIPS object file
# %.mips.o : %.s
# 	$(MIPS_CC) $(MIPS_CPPFLAGS) -c $< -o $@c src/decodeinstruction.cpp src/rijstructures.cpp src/simulator.cpp

%.mips.o : %.s
	$(MIPS_CC) $(MIPS_CPPFLAGS) -c $< -o $@


# Compile a C file into a MIPS object file
%.mips.o : %.c
	$(MIPS_CC) $(MIPS_CPPFLAGS) -c $< -o $@

# Link a MIPS object file and place it at the locations required in the
# spec using linker.ld
%.mips.elf : %.mips.o
	$(MIPS_CC) $(MIPS_CPPFLAGS) $(MIPS_LDFLAGS)  $< -o $@

# Extract just the binary instructions from the object file
%.mips.bin : %.mips.elf
	$(MIPS_OBJCOPY) -O binary --only-section=.text $< $@

# For example, if you have testbench/test.c, you can do:
#
# make testbench/test.mips.bin

###################################################
## Simulator

src/%.o: src/%.cpp
	g++ -W -Wall --std=c++11 -c -o $@ $<

OBJ_FILES=src/decode_instruction.o src/rijstructures.o src/simulator.o
	
# Build the simulation binary
bin/mips_simulator : $(OBJ_FILES)
	mkdir -p bin/
	g++ $^ -o bin/mips_simulator



	# g++ -W -Wall --std=c++11 src/simulator.cpp -o bin/mips_simulator #added the --std=c++11


# In order to comply with spec
simulator : bin/mips_simulator

###################################################
## Testbench

testbench :
	echo "No testbench yet"
	exit 1

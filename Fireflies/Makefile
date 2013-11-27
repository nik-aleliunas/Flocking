# This Makefile makes the `canvas' program, from its source and
# header files.
#


# First set up variables we'll use when making things

 CARBON_LIB        = -framework Carbon
  GL_LIBS           = -framework OpenGL $(CARBON_LIB)
  LDLIBS =  -L/usr/X11R6/lib -lGLU  -lGL -lXmu -lXext -lX11 -lm -lglut -lstdc++
  CFLAGS = -g 
########
# Some stuff that's the same for all programs and machines 
########

# The commands to call the C and C++ compilers
CC = cc 
C++ = g++


# Where to find the include files:
INCLUDE = -I/usr/X11R6/include/ -I/sw/include/

########
# Now stuff that depends on the specific program we're compiling
########

# The name of the output program 
PROG = fireflies

# Object files that go into the final executable
OBJS = fireflies.o 

# Header files
HDRS = structures.h

########
# Finally, the commands that actually make stuff
# These commands are of the form:
#   thing:  stuff it depends on
#   <TAB> command to make thing 
########

# re-link the program when the object files change
$(PROG):  $(OBJS)
	$(C++) $(OBJS) $(LDLIBS) -o $(PROG) 

# change an object file whenever the corresponding source file
# or any of the header files changes
%.o : %.c $(HDRS) 
	$(CC) -c $(CFLAGS) $(INCLUDE) $<
# How to update a .o file:
# The %.o and %.c mean any .o file and the corresponding .c file
# All .c's are recompiled if you change one of the header files
# The $< symbol refers to the FIRST dependancy - so don't try to
# put $(HDRS) before %.c!

# change a C++ object file whenever the corresponding source file
# or any of the header files changes
%.o : %.cpp $(HDRS) 
	$(C++) -c $(CFLAGS) $(INCLUDE) $<

clean:
	rm *.o ./fireflies -f

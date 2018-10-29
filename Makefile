# project name
TARGET   = dojo

# compiler
CC       = g++
LINKER   = $(CC) -o
rm       = rm -f

# flags
COMMON = -Wall -g -I.
CFLAGS = $(COMMON) -std=c++11 -fopenmp
LFLAGS = $(COMMON) -lm

# directories
SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin
DEPENDENCIES = /local/allanws/v3o2/dependencies/ext

# files
SOURCES  := $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(SRCDIR)/*/*.cpp)
INCLUDES := $(wildcard $(SRCDIR)/*.h) $(wildcard $(SRCDIR)/*/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o) \
            $(wildcard SOURCES:$(SRCDIR)/*/%.cpp=$(OBJDIR)/*/%.o)	

# includes
GLINCLUDE   = -I$(DEPENDENCIES)/freeglut/include \
              -I$(DEPENDENCIES)/glew/include
OSGINCLUDE  = -I$(DEPENDENCIES)/OSG/include
GLMINCLUDE  = -I$(DEPENDENCIES)/glm
RNGINCLUDE  = -I$(DEPENDENCIES)/range-v3/include
FREIJOINCL  = -I$(DEPENDENCIES)/freijo/include
BOOSTINCL   = -I$(DEPENDENCIES)/boost/include
INCLUDE     = $(OSGINCLUDE) \
              $(GLINCLUDE) \
              $(GLMINCLUDE) \
              $(RNGINCLUDE) \
              $(FREIJOINCL) \
              $(BOOSTINCL)

# libs
OSGLIBS = -L$(DEPENDENCIES)/OSG/lib/Linux64e6 \
          -losg -losgUtil -losgGA -losgDB \
          -losgText -losgViewer -losgSim \
          -lOpenThreads
GLLIB   = -L$(DEPENDENCIES)/freeglut/lib/Linux64e6 \
          -L$(DEPENDENCIES)/glew/lib/Linux64e6 \
          -lGL -lGLU -lglut -lGLEW -lpthread
LIBSDIR = $(OSGLIBS) $(GLLIB)

# rules
$(BINDIR)/$(TARGET) : $(OBJECTS)	
	@$(LINKER) $@ $(LFLAGS) $(OBJECTS) $(INCLUDE) $(LIBSDIR)
	@echo "Linking complete!"
	
$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "Compiled "$<" successfully!"	

.PHONEY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONEY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"

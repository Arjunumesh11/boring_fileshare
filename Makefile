CXXFLAGS=-g -Wall
CXX=g++
LDFLAGS=-pthread
SRCDIR=./src
BUILDDIR=./build
TARGET=./bin/server
INC= -I include

SRCEXT=cpp
SOURCES=$(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS=$(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) $^ -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<
clean:
	rm -r $(BUILDDIR) $(TARGET)
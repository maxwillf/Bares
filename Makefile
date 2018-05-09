Target = parser
INCLUDES = include
CXX = g++
CXXFLAGS = -std=c++11 -g -ggdb -I $(INCLUDES)
DOCS = html latex
SRCDIR = src
OBJDIR = obj

HEADERS := $(wildcard $(INCLUDES) *.h)
SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

all: project #docs
project: $(OBJECTS) 
	@echo "Linkin Files: " $(OBJECTS) $(DRIVER)
	@$(CXX) $(OBJECTS) $(DRIVER)  $(CXXFLAGS) -o $(Target)
	@echo "Linkin complete!"

docs: 
	@echo "Generating Documentation"
	@doxygen Doxyfile
	
$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp $(HEADERS) | $(OBJDIR)
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "Sources $<" 
	@echo "Compiling Files $< to  $@ "
	@echo "Compiled "$<" Succesfully!"

$(OBJDIR):
	mkdir -p $(OBJDIR)

.PHONY: clean  clean_docs clean_proj
clean: clean_proj  clean_docs

clean_proj:
	@rm -r $(OBJDIR)
	@rm $(Target)
	@echo "Cleanup Complete!"

clean_docs: $(DOCS)
	@rm -r $(DOCS)

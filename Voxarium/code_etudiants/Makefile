CXX      =  g++
CXXFLAGS = -Wall -O2 -g -Wno-unused-local-typedefs
LIB      = -ljpeg
INCLUDES = -I ~/eigen/
CXXFLAGS += $(INCLUDES)

OBJ      = ImageException.o Image.o ImageRGB.o ioJPG.o exif.o main.o 
RM       = rm -f
BIN      = hdr
DIRNAME  = $(shell basename $$PWD)
BACKUP   = $(shell date +`basename $$PWD`-%m.%d.%H.%M.tgz)
STDNAME  = $(DIRNAME).tgz

all : $(BIN)

$(BIN) : $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) $(LIB) $(INCLUDES)  -o $(BIN)
	@echo "--------------------------------------------------------------"
	@echo "                 to execute type: ./$(BIN) &"
	@echo "--------------------------------------------------------------"

ImageException.o : ImageException.cpp ImageException.hpp
	@echo "compile ImageException"
	$(CXX) $(CXXFLAGS) -c $<  
	@echo "done..."

Image.o : Image.cpp Image.hpp ImageException.o 
	@echo "compile Image"
	$(CXX) $(CXXFLAGS) -c $<  
	@echo "done..."

ImageRGB.o : ImageRGB.cpp ImageRGB.hpp Image.o ImageException.o
	@echo "compile ImageRGB"
	$(CXX) $(CXXFLAGS) -c $<  
	@echo "done..."

ioJPG.o : ioJPG.cpp ioJPG.hpp Image.o ImageException.o 
	@echo "compile ioJPG"
	$(CXX) $(CXXFLAGS) -c $<  
	@echo "done..."

exif.o : exif.cpp exif.h
	@echo "compile exif"
	$(CXX) $(CXXFLAGS) -c $<  
	@echo "done..."

main.o : main.cpp exif.o ImageRGB.o exif.o ioJPG.o 
	@echo "compile main"
	$(CXX) $(CXXFLAGS) -c $<  
	@echo "done..."

clean :	
	@echo "**************************"
	@echo "CLEAN"
	@echo "**************************"
	$(RM) *~ $(OBJ) $(BIN)  input/*~  

bigclean :
	@echo "**************************"
	@echo "BIG CLEAN"
	@echo "**************************"
	find . -name '*~' -exec rm -fv {} \;
	$(RM) *~ $(OBJ) $(BIN) output/*

tar : clean 
	@echo "**************************"
	@echo "TAR"
	@echo "**************************"
	cd .. && tar cvfz $(BACKUP) $(DIRNAME)



# Nama executable
TARGET = program

# File sumber
SOURCES = main.cpp medis.cpp

# File header
HEADERS = medis.h

# Compiler
CXX = g++
CXXFLAGS = -Wall -g

# Aturan untuk membangun executable
$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

# Aturan untuk membersihkan file yang dihasilkan
clean:
	rm -f $(TARGET)

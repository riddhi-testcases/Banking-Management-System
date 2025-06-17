# Makefile for Riddhi's Advanced Banking System
# Developer: Riddhi Chakraborty

# Compiler settings
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
DEBUG_FLAGS = -std=c++11 -Wall -Wextra -g -DDEBUG
TARGET = banking_system
SOURCES = main.cpp BankSystem.cpp
HEADERS = BankSystem.h

# Default target
all: $(TARGET)

# Build the main executable
$(TARGET): $(SOURCES) $(HEADERS)
	@echo "🔨 Compiling Riddhi's Banking System..."
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)
	@echo "✅ Build successful! Run with: ./$(TARGET)"

# Debug build
debug: $(SOURCES) $(HEADERS)
	@echo "🐛 Building debug version..."
	$(CXX) $(DEBUG_FLAGS) -o $(TARGET)_debug $(SOURCES)
	@echo "✅ Debug build complete! Run with: ./$(TARGET)_debug"

# Clean build files
clean:
	@echo "🧹 Cleaning build files..."
	rm -f $(TARGET) $(TARGET)_debug
	rm -f *.o
	@echo "✅ Clean complete!"

# Clean all generated files (including data files)
clean-all: clean
	@echo "🗑️  Cleaning all generated files..."
	rm -f *.dat
	rm -f statement_*.txt
	@echo "✅ All files cleaned!"

# Install (copy to system directory)
install: $(TARGET)
	@echo "📦 Installing banking system..."
	sudo cp $(TARGET) /usr/local/bin/
	@echo "✅ Installation complete! Run with: banking_system"

# Uninstall
uninstall:
	@echo "🗑️  Uninstalling banking system..."
	sudo rm -f /usr/local/bin/$(TARGET)
	@echo "✅ Uninstallation complete!"

# Run the application
run: $(TARGET)
	@echo "🚀 Starting Riddhi's Banking System..."
	./$(TARGET)

# Run in debug mode
run-debug: debug
	@echo "🐛 Starting debug version..."
	./$(TARGET)_debug

# Create backup of source files
backup:
	@echo "💾 Creating backup..."
	tar -czf banking_system_backup_$(shell date +%Y%m%d_%H%M%S).tar.gz *.cpp *.h *.md Makefile
	@echo "✅ Backup created!"

# Check for memory leaks (requires valgrind)
memcheck: debug
	@echo "🔍 Running memory check..."
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)_debug

# Format code (requires clang-format)
format:
	@echo "🎨 Formatting code..."
	clang-format -i *.cpp *.h
	@echo "✅ Code formatted!"

# Show help
help:
	@echo "🏦 Riddhi's Advanced Banking System - Build Help"
	@echo "================================================"
	@echo "Available targets:"
	@echo "  all        - Build the banking system (default)"
	@echo "  debug      - Build debug version with symbols"
	@echo "  clean      - Remove build files"
	@echo "  clean-all  - Remove all generated files"
	@echo "  install    - Install to system directory"
	@echo "  uninstall  - Remove from system directory"
	@echo "  run        - Build and run the application"
	@echo "  run-debug  - Build and run debug version"
	@echo "  backup     - Create backup of source files"
	@echo "  memcheck   - Run memory leak detection"
	@echo "  format     - Format source code"
	@echo "  help       - Show this help message"
	@echo ""
	@echo "Example usage:"
	@echo "  make           # Build the system"
	@echo "  make run       # Build and run"
	@echo "  make clean     # Clean build files"

# Declare phony targets
.PHONY: all debug clean clean-all install uninstall run run-debug backup memcheck format help
# Название исполняемого файла
TARGET = new_game

# Компилятор
CXX = g++

# Флаги компиляции
CXXFLAGS = -std=c++17 #-Wall -Wextra  -O2

# Путь к заголовочным файлам OpenSSL (например, для MSYS2)
#INCLUDE_DIR = -I/mingw64/include

# Флаги линковки для OpenSSL
LDFLAGS = -L/mingw64/lib -lssl -lcrypto

# Исходные файлы (автоматически определяются все .cpp файлы в текущей директории)
SRCS = $(wildcard *.cpp)

# Объектные файлы (автоматически генерируются из исходных файлов)
OBJS = $(SRCS:.cpp=.o)

# Правило по умолчанию
all: $(TARGET)

# Линковка
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Компиляция .cpp в .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) -c $< -o $@

# Очистка скомпилированных файлов
clean:
	del /Q $(OBJS) $(TARGET)

.PHONY: all clean
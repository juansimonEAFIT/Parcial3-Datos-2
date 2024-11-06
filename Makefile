# Variables del compilador
CXX = g++
CXXFLAGS = -Wall -g

# Nombre del ejecutable
TARGET = arbol_b_mas

# Archivos objeto
OBJS = main.o ArbolBPlus.o Tabla.o AnalizadorSQL.o NodoBPlus.o

# Regla principal: compilar todo
all: $(TARGET)

# Regla para enlazar los archivos objeto y generar el ejecutable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Regla para compilar main.cpp
main.o: main.cpp ArbolBPlus.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# Regla para compilar ArbolBMas.cpp
ArbolBPlus.o: ArbolBPlus.cpp ArbolBPlus.h
	$(CXX) $(CXXFLAGS) -c ArbolBPlus.cpp

# Regla para compilar Tabla.cpp
Tabla.o: Tabla.cpp Tabla.h
	$(CXX) $(CXXFLAGS) -c Tabla.cpp

# Regla para compilar AnalizadorSQL.cpp
AnalizadorSQL.o: AnalizadorSQL.cpp AnalizadorSQL.h
	$(CXX) $(CXXFLAGS) -c AnalizadorSQL.cpp

NodoBPlus.o: NodoBPlus.cpp NodoBPlus.h
	$(CXX) $(CXXFLAGS) -c NodoBPlus.cpp

# Regla para ejecutar el programa
run: $(TARGET)
	./$(TARGET)

# Limpiar archivos objeto y el ejecutable
clean:
	rm -f $(OBJS) $(TARGET)

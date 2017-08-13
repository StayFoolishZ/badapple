INCLUDE = $(shell pkg-config --cflags opencv)  
LIBS = $(shell pkg-config --libs opencv)  
SOURCES = *.cpp  
# 目标文件  
OBJECTS = $(SOURCES:.cpp=.o)  
# 可执行文件  
TARGET = test  
#$(TARGET):$(OBJECTS)  
#	g++ -o $(TARGET) $(OBJECTS) -I $(INCLUDE) $(LIBS) -lwiringPi -lwiringPiDev  
$(OBJECTS):$(SOURCES)  
	g++ -o $(TARGET) $(SOURCES) -I $(INCLUDE) $(LIBS) -lwiringPi -lwiringPiDev
clean:  
	rm $(OBJECTS) $(TARGET)  
# 编译规则 $@代表目标文件 $< 代表第一个依赖文件  
#%.o:%.cpp  
#	g++ -I $(INCLUDE) -o $@ -c $<  

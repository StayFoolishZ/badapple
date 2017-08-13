INCLUDE = $(shell pkg-config --cflags opencv)  
LIBS = $(shell pkg-config --libs opencv)  
SOURCES = *.cpp  
# Ŀ���ļ�  
OBJECTS = $(SOURCES:.cpp=.o)  
# ��ִ���ļ�  
TARGET = test  
#$(TARGET):$(OBJECTS)  
#	g++ -o $(TARGET) $(OBJECTS) -I $(INCLUDE) $(LIBS) -lwiringPi -lwiringPiDev  
$(OBJECTS):$(SOURCES)  
	g++ -o $(TARGET) $(SOURCES) -I $(INCLUDE) $(LIBS) -lwiringPi -lwiringPiDev
clean:  
	rm $(OBJECTS) $(TARGET)  
# ������� $@����Ŀ���ļ� $< �����һ�������ļ�  
#%.o:%.cpp  
#	g++ -I $(INCLUDE) -o $@ -c $<  

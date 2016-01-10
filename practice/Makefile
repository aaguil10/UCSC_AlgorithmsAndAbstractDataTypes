

MAINCLASS  = QueueTest
JAVAC	   = javac
JAVASRC    = $(wildcard *.java)
SOURCES    = $(JAVASRC) makefile 
CLASSES    = $(patsubst %.java, %.class, $(JAVASRC))
JARCLASSES = $(patsubst %.class, %*.class, $(CLASSES))
JARFILE    = $(MAINCLASS)

all: $(JARFILE)

$(JARFILE): $(CLASSES)
	echo Main-class: $(MAINCLASS) > Mainfest


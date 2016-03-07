
CC = g++
HADOOP_INSTALL = /opt/hadoop-1.2.1
PLATFORM = Linux-amd64-64
CPPFLAGS = -I$(HADOOP_INSTALL)/c++/$(PLATFORM)/include

wordcount: wordcount.cpp
	$(CC) $(CPPFLAGS) $< -Wall -g -O2 -o $@ \
	-I$(HADOOP_INSTALL)/src/c++/install/include \
	-L$(HADOOP_INSTALL)/src/c++/install/lib \
	-lhadooputils -lhadooppipes -lcrypto -lssl -lpthread

clean:
	/bin/rm -f wordcount

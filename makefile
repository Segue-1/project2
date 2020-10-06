all: master.exe slave.exe

master.exe: master.cpp
	gcc -g -o master.exe master.cpp
slave.exe: slave.cpp
	gcc -g -o slave.exe slave.cpp
clean:
	@echo "Cleaning up..."
	rm master.exe
	rm slave.exe
	@echo "Finsihed cleaning"

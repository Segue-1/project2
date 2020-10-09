all: master.exe worker.exe

master.exe: master.cpp
	gcc -g -o master.exe master.cpp -std=c++11
worker.exe: worker.cpp
	gcc -g -o worker.exe worker.cpp -std=c++11
clean:
	@echo "Cleaning up..."
	rm master.exe
	rm worker.exe
	@echo "Finsihed cleaning"

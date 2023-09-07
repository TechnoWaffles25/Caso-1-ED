all: comm_progs

comm_progs:
	g++ -o news.o news.cpp -lcurl

# docker run -it --rm -v "C:\Users\Ale\Desktop\Ale's Stuff\2023\C++:/home" gcc bash
# apt update -y
# apt install curl

# g++ caso1_cpp.cpp -o caso1.o -lcurl
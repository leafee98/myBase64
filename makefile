help :
	@echo "    all        build libmyBase64.o in ./out/"
	@echo "    clean      remove direcoty and content in ./out/"

./out/myBase64.o : ./myBase64.cpp
	[ -d ./out/ ] || mkdir ./out/
	g++ -c ./myBase64.cpp -o ./out/myBase64.o

./out/libmyBase64.a : ./out/myBase64.o
	ar -r ./out/libmyBase64.a ./out/myBase64.o

all : ./out/libmyBase64.a

clean :
	rm -rf ./out/

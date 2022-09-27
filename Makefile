build\program.exe: build\main.o build\buffer.o build\sort_functions.o build\comparators.o build\common.o
		g++ -o build\Task2.exe $^
build\main.o: source\main.cpp
		g++ -c -o build\main.o source\main.cpp
build\buffer.o: source\buffer.cpp
		g++ -c -o build\buffer.o source\buffer.cpp
build\sort_functions.o: source\sort_functions.cpp
		g++ -c -o build\sort_functions.o source\sort_functions.cpp
build\comparators.o: source\comparators.cpp
		g++ -c -o build\comparators.o source\comparators.cpp
build\common.o: source\common.cpp
		g++ -c -o build\common.o source\common.cpp

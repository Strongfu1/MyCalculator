OS=$(shell uname)
ifeq ($(OS), Linux)
	CXXFLAGS=-lgtest -g  -lpthread
	LEAKS = valgrind --leak-check=full
else
	CXXFLAGS = -lgtest -g
	LEAKS = CK_FORK=no leaks --atExit --
endif
CXX=g++ -std=c++17 -Wall -Wextra -Werror
BD = ../build/


all: build check

build: clean mk replication
	cd $(BD); qmake Calc.pro
	make -C $(BD)

replication: 
	cp -r Controller CreditCalc DepositCalc Font Icons MathCalc Other Calc.pro main.cpp $(BD)
	
dist: build
	cd $(BD);cd ..; tar -cvf Calc.tar build

install: build
	mkdir $(HOME)/Desktop/Calc/
	cp -rf $(BD)Calc.app $(HOME)/Desktop/Calc/
	make clean

uninstall:
	rm -rf $(HOME)/Desktop/Calc/

mk:
	mkdir ../build

tests:
	@$(CXX) --coverage -O0 -C Tests/MathTests.cpp MathCalc/Model/*.cpp -o math_tests $(CXXFLAGS)
	./math_tests
	
gcov_report: tests
	lcov -t "gcov_report" --no-external -o all_tests.info -c -d .
	genhtml -o gcov_report all_tests.info

check:
	@clang-format -i */*.cpp */*.h */*/*.cpp */*/*.h
	clang-format -n */*.cpp */*.h */*/*.cpp */*/*.h
	cppcheck --enable=all  --language=c++ --force --suppress=unusedStructMember --suppress=useStlAlgorithm  */*.cpp */*.h */*/*.cpp */*/*.h

clean:
	rm -rf *.gcda *.gcno *.o *.info math_tests */*.out */*.dSYM gcov_report
	rm -rf $(BD)*
	rm -rf $(BD)
	rm -rf ../build-*


.PHONY: check gcov_report tests clean
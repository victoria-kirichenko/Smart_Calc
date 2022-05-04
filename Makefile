CC = gcc
CFLAG = -Wall -Wextra -Werror
APP = build/s21_calc.app
BACKEND_FILES = backend/s21_stack.c backend/s21_smart_calc.c
BACKEND_FILES_O = s21_stack.o s21_smart_calc.o

all: install s21_calc.a test
build:
	mkdir build
	cd ./build/ && qmake ../ && make && mv Calc_new.app s21_calc.app

install: build
	@mkdir $(HOME)/Desktop/SmartCalc_v1.0/
	@cp -rf $(APP) $(HOME)/Desktop/SmartCalc_v1.0/
	make clean

uninstall:
	@rm -rf $(HOME)/Desktop/SmartCalc_v1.0/

dvi:
	open dvi.html

check: test
	@cp -f ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	@python ../materials/linters/cpplint.py --extensions=c *.c
	@python ../materials/linters/cpplint.py --extensions=h backend/s21_smart_calc.h
	@rm -rf CPPLINT.cfg
	@CK_FORK=no leaks --atExit -- ./test2.o


dist:
	rm -rf Archive_SmartCalc_v1.0/
	mkdir Archive_SmartCalc_v1.0/
	mkdir Archive_SmartCalc_v1.0/src
	cp Makefile *.c *.h *.pro *.cpp *.ui *.user Archive_SmartCalc_v1.0/src/
	tar cvzf Archive_SmartCalc_v1.0.tgz Archive_SmartCalc_v1.0/
	mv Archive_SmartCalc_v1.0.tgz $(HOME)/Desktop/
	rm -rf Archive_SmartCalc_v1.0/

test:
	$(CC) $(CFLAG) -c s21_test.c -o test1.o
	$(CC) test1.o s21_calc.a -lcheck -o test2.o
	./test2.o

s21_calc.a:
	$(CC) $(CFLAG) -c $(BACKEND_FILES)
	@ar rcs s21_calc.a $(BACKEND_FILES_O)

open:
	open build

gcov_report:
	$(CC) --coverage s21_test.c  -o s21_test -lcheck $(BACKEND_FILES)
	./s21_test
	lcov -t "s21_test" -o s21_test.info -c -d .
	genhtml -o report s21_test.info
	open ./report/index.html

clean:
	rm -rf *.o *.a
	rm -rf *.gcda *.gcno *.info
	rm -rf s21_test report
	rm -rf s21_calc s21_test
	rm -rf ./build*

rebuild: clean all

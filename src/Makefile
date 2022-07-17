CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11
SRC_LIB = s21_calc_back
TESTFILE = test
GCOV_FLAG = -fprofile-arcs -ftest-coverage
ifeq ($(shell uname), Linux)
	LIBS_FOR_CHECK=-lcheck -lsubunit -lrt -lpthread -lm
else
	LIBS_FOR_CHECK=-lcheck
endif
RDIR = ../release/
APP = $(RDIR)s21_SmartCalc.app

all: clean install test
	./$(RDIR)/s21_SmartCalc

install:
	mkdir $(RDIR)
	cd $(RDIR); qmake ../src/S21_CALC/s21_SmartCalc.pro
	cd $(RDIR); make
	cd $(RDIR); make clean
	cp $(RDIR)s21_SmartCalc.app/Contents/MacOS/s21_SmartCalc $(RDIR)s21_SmartCalc

uninstall:
	rm -rf $(RDIR)s21_SmartCalc.app

dist:
	tar -czf $(RDIR)s21_SmartCalc_v1.0.tgz $(RDIR)s21_SmartCalc.app

dvi:
	makeinfo manual.texi --html
	open ./manual/index.html
clean:
	@echo "****** clean trash ******"
	rm -f *.a *.o *.so *.out $(TESTFILE) *.info *.gcno *.gcda main
	rm -rf report manual

test: clean s21_calc_back.a
	$(CC) $(TESTFILE).c $(SRC_LIB).a $(FLAGS) $(LIBS_FOR_CHECK) -o $(TESTFILE)
	./$(TESTFILE)

s21_calc_back.a:
	$(CC) -c $(FLAGS) $(SRC_LIB).c -o $(SRC_LIB).o
	ar rcs $(SRC_LIB).a $(SRC_LIB).o
	ranlib $@

gcov_report: clean
	@echo "****** gcov start ******"
	$(CC) $(FLAGS) $(GCOV_FLAG) $(NAME).c $(TESTFILE).c $(LIBS_FOR_CHECK) -o gcov.out
	./gcov.out
	lcov -o $(TESTFILE).info -c -d .
	genhtml -o report $(TESTFILE).info
	open ./report/index.html

linter:
	@echo "****** linter start ******"
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extensions=c *.c
	python3 ../materials/linters/cpplint.py --extensions=h *.h
	rm -f CPPLINT.cfg

cppcheck:
	@echo "****** cppcheck start ******"
	cppcheck --enable=all --suppress=missingIncludeSystem $(SRC_LIB).c
	cppcheck --enable=all --suppress=missingIncludeSystem *.h

leaks: test
ifeq ($(shell uname), Linux)
	CK_FORK=no valgrind --tool=memcheck --leak-check=full ./$(TESTFILE)
else
	CK_FORK=no leaks --atExit -- ./$(TESTFILE)
endif

#CK_FORK=no valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --show-reachable=yes ./test


scripts = tail-test.sh io-test.sh io-test.c wordcount-test.sh print-help.sh
test_dirs = tail_tests2024 io_tests2024 wordcount_tests2024
.PHONY: all tail io wordcount help clean

all: tail io wordcount clean

tail:
	@clear
	@chmod +x tail-test.sh && ./tail-test.sh

io: io-test
	@chmod +x io-test.sh && ./io-test.sh

io-test: io-test.c io.o
	@gcc -o $@ $^

io.o: io.c io.h
	@gcc -c $< -o $@

wordcount:
	@chmod +x wordcount-test.sh && ./wordcount-test.sh

help:
	@chmod +x print-help.sh && ./print-help.sh

clean:
	@rm -f io-test *.o

zip:
	@zip -r IJC2024_tests_marocc.zip $(scripts) $(test_dirs) Makefile
	
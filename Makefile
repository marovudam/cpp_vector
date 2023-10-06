CXX			=	g++ 
CXXFLAGS	=	-std=c++17 -pedantic -Wall -Wextra -Werror
TEST_FLAGS	=	-lgtest -lgtest_main

all: test

clean:
	rm -f test

test: clean
	$(CXX) $(CXXFLAGS) $(TEST_FLAGS) vector_tests.cc -o test
	./test

style:
	clang-format -i *.cc *.h -style=Google

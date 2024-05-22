all: llang llang-tests

llang: \
		src/main.c \
		src/lexer.c \
		src/lexer.h \
		src/token.c \
		src/token.h \
		src/liststruct.c \
		src/liststruct.h \
		src/reader.c \
		src/reader.h \
		src/writer.c \
		src/writer.h \
		src/eval.c \
		src/eval.h \
		src/environment.c \
		src/environment.h
	clang \
	   -fcolor-diagnostics \
	   -fansi-escape-codes \
	   -g \
	   src/main.c src/lexer.c src/token.c src/liststruct.c src/reader.c src/writer.c src/eval.c src/environment.c \
       -o llang

llang-tests: \
		src/tests.c \
		src/lexer.c \
		src/lexer.h \
		src/token.c \
		src/token.h \
		src/liststruct.c \
		src/liststruct.h \
		src/reader.c \
		src/reader.h \
		src/writer.c \
		src/writer.h \
		src/eval.c \
		src/eval.h \
		src/environment.c \
		src/environment.h
	clang \
	   -fcolor-diagnostics \
	   -fansi-escape-codes \
	   -g \
	   src/tests.c src/lexer.c src/token.c src/liststruct.c src/reader.c src/writer.c src/eval.c src/environment.c \
       -o llang-tests

llang-darwin-arm64: \
		src/main.c \
	    src/lexer.c \
	    src/lexer.h \
		src/token.c \
		src/token.h \
		src/liststruct.c \
		src/liststruct.h \
		src/reader.c \
		src/reader.h \
		src/writer.c \
		src/writer.h \
		src/eval.c \
		src/eval.h \
		src/environment.c \
		src/environment.h
	clang \
	   -fcolor-diagnostics \
	   -fansi-escape-codes \
	   -g \
	   src/main.c src/lexer.c src/token.c src/liststruct.c src/reader.c src/writer.c src/eval.c src/environment.c \
	   -o llang-$(LLANG_VERSION)-darwin-arm64

llang-linux-amd64: \
		src/main.c \
	    src/lexer.c \
	    src/lexer.h \
	    src/token.c \
	    src/token.h \
	    src/liststruct.c \
	    src/liststruct.h \
		src/reader.c \
		src/reader.h \
		src/writer.c \
		src/writer.h \
		src/eval.c \
		src/eval.h \
		src/environment.c \
		src/environment.h
	clang \
	   -fcolor-diagnostics \
	   -fansi-escape-codes \
	   -g \
	   src/main.c src/lexer.c src/token.c src/liststruct.c src/reader.c src/writer.c src/eval.c src/environment.c \
	   -o llang-$(LLANG_VERSION)-linux-amd64

clean:
	rm -rf llang*

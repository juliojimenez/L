all: llang

llang: \
		src/main.c \
		src/lexer.c \
		src/lexer.h \
		src/token.c \
		src/token.h \
		src/liststruct.c \
		src/liststruct.h \
		src/reader.c \
		src/reader.h
	clang \
	   -fcolor-diagnostics \
	   -fansi-escape-codes \
	   -g \
	   src/main.c src/lexer.c src/token.c src/liststruct.c src/reader.c \
       -o llang

llang-darwin-arm64: \
		src/main.c \
	    src/lexer.c \
	    src/lexer.h \
		src/token.c \
		src/token.h \
		src/liststruct.c \
		src/liststruct.h \
		src/reader.c \
		src/reader.h
	clang \
	   -fcolor-diagnostics \
	   -fansi-escape-codes \
	   -g \
	   src/main.c src/lexer.c src/token.c src/liststruct.c src/reader.c \
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
		src/reader.h
	clang \
	   -fcolor-diagnostics \
	   -fansi-escape-codes \
	   -g \
	   src/main.c src/lexer.c src/token.c src/liststruct.c src/reader.c \
	   -o llang-$(LLANG_VERSION)-linux-amd64

clean:
	rm -rf llang*

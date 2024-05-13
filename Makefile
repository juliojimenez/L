all: llang

llang: src/main.c
	clang -fcolor-diagnostics -fansi-escape-codes -g src/main.c -o llang

llang-darwin-arm64: src/main.c
	clang -fcolor-diagnostics -fansi-escape-codes -g src/main.c -o llang-$(LLANG_VERSION)-darwin-arm64

llang-linux-x64: src/main.c
	clang -fcolor-diagnostics -fansi-escape-codes -g src/main.c -o llang-$(LLANG_VERSION)-linux-x64

clean:
	rm -rf llang*

FROM alpine:latest
WORKDIR /llang
RUN wget https://github.com/juliojimenez/L/releases/download/0.0.1/llang-0.0.1-linux-x64
ENTRYPOINT [ "llang-0.0.1-linux-x64" ]
CMD [ "--version" ]

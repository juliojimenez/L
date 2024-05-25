FROM alpine:latest
WORKDIR /llang
RUN wget https://github.com/juliojimenez/L/releases/download/0.0.17/llang-0.0.17-linux-amd64
ENTRYPOINT [ "llang-0.0.17-linux-amd64" ]
CMD [ "--version" ]

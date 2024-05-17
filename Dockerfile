FROM alpine:latest
WORKDIR /llang
RUN wget https://github.com/juliojimenez/L/releases/download/0.0.5/llang-0.0.5-linux-amd64
ENTRYPOINT [ "llang-0.0.5-linux-amd64" ]
CMD [ "--version" ]

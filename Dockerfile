FROM alpine:latest
WORKDIR /llang
RUN wget https://github.com/juliojimenez/L/releases/download/0.0.7/llang-0.0.7-linux-amd64
ENTRYPOINT [ "llang-0.0.7-linux-amd64" ]
CMD [ "--version" ]

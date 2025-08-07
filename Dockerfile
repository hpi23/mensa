FROM rust:slim-bookworm as builder

# RUN pacman -Sy --noconfirm
# RUN pacman -S git rustup gcc curl make gcc bat --noconfirm
RUN rustup default stable

RUN apt update && apt install git make libcurl4-gnutls-dev -y

RUN git clone https://github.com/hpi23/mensa /root/mensa
# RUN git clone https://github.com/hpi23/c-projects /root/sprache/crates/hpi-transpiler-c/hpi-c-tests
WORKDIR /root/mensa

RUN ls
RUN make init -j 1

COPY ./cli.hpi ./mensa.hpi
RUN make lib HPI_FILE=mensa.hpi

# FROM debian:bookworm-slim as builder2

RUN apt update && apt install build-essential libcurl4-gnutls-dev -y

# COPY --from=builder /root/mensa/ /bin/mensa
# WORKDIR /bin/mensa
COPY ./server.c ./server.c
RUN cat server.c
# COPY --from=builder /root/mensa/server.c /bin/server.c

RUN gcc server.c sprache/crates/hpi-transpiler-c/output.c -ggdb \
    sprache/crates/hpi-transpiler-c/libSAP/libSAP.a \
    -lcurl \
    -lm \
    -ggdb3 -o main

FROM debian:bookworm-slim
RUN apt update && apt install libcurl4-gnutls-dev -y
COPY --from=builder /root/mensa/main /bin/mensa

COPY ./run.sh /bin/run.sh
RUN chmod +x /bin/run.sh
ENV BIN=/bin/mensa
CMD ["/bin/run.sh"]

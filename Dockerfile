FROM archlinux as builder

RUN pacman -Sy --noconfirm
RUN pacman -S git rustup gcc curl make gcc bat --noconfirm
RUN rustup default stable

RUN git clone https://github.com/hpi23/mensa /root/mensa
# RUN git clone https://github.com/hpi23/c-projects /root/sprache/crates/hpi-transpiler-c/hpi-c-tests
WORKDIR /root/mensa

RUN ls
RUN make init -j 1

COPY ./cli.hpi ./mensa.hpi

RUN make lib HPI_FILE=mensa.hpi
RUN gcc server.c sprache/crates/hpi-transpiler-c/output.c -ggdb \
    sprache/crates/hpi-transpiler-c/libSAP/libSAP.a \
    -lcurl \
    -lm \
    -ggdb3 -o main

FROM archlinux
COPY --from=builder /root/mensa/main /bin/mensa

CMD ["/bin/mensa"]

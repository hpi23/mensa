FROM archlinux as builder

RUN pacman -Sy --noconfirm
RUN pacman -S git rustup gcc curl make gcc bat --noconfirm

RUN git clone https://github.com/hpi23/sprache /root/sprache
RUN git clone https://github.com/hpi23/c-projects /root/sprache/crates/hpi-transpiler-c/hpi-c-tests
WORKDIR /root/sprache/crates/hpi-transpiler-c/

RUN ls

RUN rustup default stable

COPY ./discord-bot.hpi ./mensa.hpi
RUN make init -j 1 \
    && make main HPI_FILE=mensa.hpi

FROM archlinux
COPY --from=builder /root/sprache/crates/hpi-transpiler-c/main /bin/mensa

CMD ["/bin/mensa"]

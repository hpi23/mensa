init:
	git clone https://github.com/hpi23/sprache || echo "already cloned"
	cd ./sprache/crates/hpi-transpiler-c/ && make init

HPI_FILE=./cli.hpi
LIB_FILE=./lib.hpi

CAT=cat

.PHONY: build

build: $(HPI_FILE)
	cp $(HPI_FILE) ./sprache/crates/hpi-transpiler-c/
	cd ./sprache/crates/hpi-transpiler-c/ && make main HPI_FILE=$(HPI_FILE) && cp ./main ../../../$(HPI_FILE).bin

.PHONY: run

RARGS:=

run: build
	./$(HPI_FILE).bin $(RARGS)

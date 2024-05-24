init:
	git clone https://github.com/hpi23/sprache || echo "already cloned"
	cd ./sprache/crates/hpi-transpiler-c/ && make init

HPI_FILE=./cli.hpi
HPI_FILE_CONCAT:=$(HPI_FILE).concat.hpi
LIB_FILE=./lib.hpi

CAT=cat

.PHONY: build

build: $(HPI_FILE)
	# Include the library
	cat $(LIB_FILE) $(HPI_FILE) > $(HPI_FILE_CONCAT)

	cp $(HPI_FILE_CONCAT) ./sprache/crates/hpi-transpiler-c/
	cd ./sprache/crates/hpi-transpiler-c/ && make main HPI_FILE=$(HPI_FILE_CONCAT) && cp ./main ../../../$(HPI_FILE).bin

.PHONY: run

RARGS:=

run: build
	./$(HPI_FILE).bin $(RARGS)

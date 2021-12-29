.ONESHELL:
.PHONY: cleanbuild build run test

cleanbuild: clean build
test: build t
run: build r

t:
	@echo ""
	cd build
	./graphy test

r:
	@echo ""
	cd build
	./graphy

build:
	mkdir -p build
	cd build
	cmake ..
	mold -run make -j $(shell nproc)

clean:
	rm -rf build
.ONESHELL:
.PHONY: cleanbuild build run test

cleanbuild: clean build
test: test-build t
run: build r

t:
	@echo ""
	cd build/test
	./test_graphy

r:
	@echo ""
	cd build
	./graphy

build:
	mkdir -p build
	cd build
	cmake .. -G Ninja
	ninja -j $(shell nproc)

test-build:
	mkdir -p build
	cd build
	cmake .. -DBUILD_TESTING=true -G Ninja
	ninja -j $(shell nproc)

clean:
	rm -rf build

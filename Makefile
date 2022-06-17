all:
	CWD=$(abspath $(patsubst %/,%,$(dir $(abspath $(lastword $(MAKEFILE_LIST))))))
	@echo $(CWD)
	# Pre-requests
	# sudo apt-get install libantlr4-runtime-dev
	# wget https://repo1.maven.org/maven2/org/antlr/antlr4/4.7.2/antlr4-4.7.2-complete.jar
	# sudo mv antlr4-4.7.2-complete.jar /usr/local/lib
	# build irbackend
	mkdir -p irbackend/build
	cmake -DCMAKE_BUILD_TYPE=Debug -Birbackend/build -Sirbackend -DCMAKE_INSTALL_PREFIX=irbackend/bin
	make -C irbackend/build -j4 install
	# build c1recognize
	mkdir -p c1recognizer/build
	cmake -DCMAKE_BUILD_TYPE=Debug -DANTLR_EXECUTABLE=/usr/local/lib/antlr-4.7.2-complete.jar -DCMAKE_INSTALL_PREFIX=c1recognizer/bin -Bc1recognizer/build -Sc1recognizer
	make -C c1recognizer/build -j4 install
	# build IRbuilder
	mkdir -p IRbuilder/build
	cmake -BIRbuilder/build -SIRbuilder
	sudo make -C IRbuilder/build -j4 install

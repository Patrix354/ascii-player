main: clear module_compile copy_module
	echo "Done :)"

module_compile:
	python3 modules/setup.py build

copy_module:
	cp build/lib.linux-x86_64-cpython-3*/* .
	
clear:
	rm -rf __pycache__
	rm -rf build/*
	rm ASCIImodule.cpython*
.SILENT:

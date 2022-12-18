main: module_compile copy_module
	python3 main.py ASCIIaudio.py ASCIIvideo.py
module_compile:
	python3 modules/setup.py build
copy_module:
	cp build/lib.linux-x86_64-cpython-310/* .
	

.SILENT:

main: mod_compile
	python3 main.py ASCIIaudio.py ASCIIvideo.py

mod_compile:
	python3 modules/setup.py build

.SILENT:
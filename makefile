SRC_MEDIA = media_files/AURORA-Cure_for_me360p.mp4
WIDTH = 100
HEIGHT = 50

main: module_compile copy_module
	python3 main.py -W $(WIDTH) -H $(HEIGHT) -P $(SRC_MEDIA)
module_compile:
	python3 modules/setup.py build
copy_module:
	cp build/lib.linux-x86_64-cpython-310/* .
	

.SILENT:

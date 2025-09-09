# LabWork1
## Author
Каюмов Айрат Хафизович, группа 24Б.81-мм
## Contacts
st128100@student.spbu.ru
## Description
LabWork1 - simle 8bit grayscale BMP redactor. Allows to rotate "source.bmp" image by 90 degrees and application of gaussian filter with matrix size specification. This redactor uses multithreading for memory-intensive and compute-intensive operations. The required operations and parameters are passed as launch parameters.
## Build
make
## Build perfomance tester
make counter
## Clear
- make clean - delete object files
- make cleanall - delete object files, executable, library file and redacted images.
## Run
- ./bmp - to get set of available launch parameters
- ./bmp --rotate-right - rotate image by 90 degrees right
- ./bmp --rotate-left  - rotate image by 90 degrees left
- ./bmp --apply-filter - apply gaussian filter to image
- ./bmp --threads - to enable usage of multiple threads

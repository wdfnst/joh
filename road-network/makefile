CC = icpc
LD = icpc

CCFLAGS = -xMIC-AVX512 -qopt-report-phase=vec -qopt-report=5 -fopenmp -std=c++14 -O3

DEPEND = ../../../src/utils/timer.cc

BUILD = build

.PHONY: run

$(BUILD)/:
	mkdir -p $(BUILD)/
%: %.cc | $(BUILD)/
	$(CC) $(CCFLAGS) -o $(BUILD)/$@ $^ $(DEPEND)
	echo "$@" >> README.md
	./$(BUILD)/$@  | tee -a README.md

run: %
	echo 'Journey Of The Heart'
	# ./$(BUILD)/$@ > /dev/shm/mytempfile && cat /dev/shm/mytempfile >> README.md && trap 'rm /dev/shm/mytempfile' EXIT && ../plot_result.sh


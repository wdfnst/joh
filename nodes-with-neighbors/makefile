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
	./$(BUILD)/$@ > /dev/shm/mytempfile && trap 'rm /dev/shm/mytempfile' EXIT && ../plot_result.sh

run: %
	echo fuck


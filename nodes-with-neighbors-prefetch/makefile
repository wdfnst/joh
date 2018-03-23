CC = icpc
LD = icpc

CCFLAGS = -O3 -xMIC-AVX512 -qopt-prefetch=5 -qopt-report-phase=vec -qopt-report=5 -fopenmp -std=c++14
DEPEND = ../../../src/utils/timer.cc

BUILD = build

.PHONY: run

$(BUILD)/:
	mkdir -p $(BUILD)/
%: %.cc | $(BUILD)/
	$(CC) $(CCFLAGS) -o $(BUILD)/$@ $^ $(DEPEND)
	./$(BUILD)/$@

run: %
	echo fuck


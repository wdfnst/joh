#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

struct nodes {
	int start, weight;
	std::vector<int> ends;
} __attribute__((aligned(64)));

int read_graph(std::string filename = "USA-road-t.NY.gr") {
	std::string graph_type;
	int num_node, num_edge;
	std::ifstream istrm(filename);
  if (!istrm.is_open()) {
    std::cout << "failed to open " << filename << '\n';
  } else {
		std::string line;
		while (std::getline(istrm, line)) {
			std::stringstream ss(line);
			char type;
			int start, end, weight;
			ss >> type;
			if (type == 'p') {
				ss >> graph_type >> num_node >> num_edge;
			}
			istrm >> start >> end >> weight;
			if (type == 'c') 
				continue;
			std::cout << type << " " << start << " " << end << " " << weight << std::endl;
		}
  }

	return 0;
}

int main() {
	std::string filename = "USA-road-t.NY.gr";
	read_graph(filename);
	return 0;
}


#include <fst/fstlib.h>
#include <iostream>
#include <string>

using namespace fst;

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <string>\n";
        return 1;
    }

    std::string input = argv[1];
    StdVectorFst fst;

    int start = fst.AddState();
    fst.SetStart(start);

    int current = start;
    for (char c : input) {
        int next = fst.AddState();
        fst.AddArc(current, StdArc(c, c, TropicalWeight::One(), next));
        current = next;
    }

    fst.SetFinal(current, Tr

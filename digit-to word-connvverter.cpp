#include <fst/fstlib.h>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace fst;

int main() {
    StdVectorFst fst;

    int start = fst.AddState();
    fst.SetStart(start);
    int accept = fst.AddState();
    fst.SetFinal(accept, TropicalWeight::One());

    std::unordered_map<char, std::string> digitWords = {
        {'0', "ZERO"}, {'1', "ONE"}, {'2', "TWO"}, {'3', "THREE"}, {'4', "FOUR"},
        {'5', "FIVE"}, {'6', "SIX"}, {'7', "SEVEN"}, {'8', "EIGHT"}, {'9', "NINE"}
    };

    for (char c = '0'; c <= '9'; ++c)
        fst.AddArc(start, StdArc(c, digitWords[c][0], TropicalWeight::One(), accept));

    for (char c = 'A'; c <= 'Z'; ++c) fst.AddArc(start, StdArc(c, c, TropicalWeight::One(), accept));
    for (char c = 'a'; c <= 'z'; ++c) fst.AddArc(start, StdArc(c, c, TropicalWeight::One(), accept));
    fst.AddArc(start, StdArc(' ', ' ', TropicalWeight::One(), accept));

    std::string input, output;
    std::cout << "Enter a string with digits: ";
    std::getline(std::cin, input);

    for (char c : input) {
        bool found = false;
        ArcIterator<StdVectorFst> aiter(fst, start);
        for (; !aiter.Done(); aiter.Next()) {
            const StdArc &arc = aiter.Value();
            if (arc.ilabel == c) {
                output += (digitWords.count(c) ? digitWords[c] : static_cast<char>(arc.olabel));
                found = true;
                break;
            }
        }
        if (!found) output.push_back(c);
    }

    std::cout << "Converted string: " << output << std::endl;
    return 0;
}

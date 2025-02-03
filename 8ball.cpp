#include <iostream>
#include <cstdlib>
#include <random>
#include <chrono>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <numeric>
#include <algorithm>
#include <filesystem>
#include <windows.h>

using namespace std;
using namespace std::chrono;

int max_width = 50;

int randint(int min, int max) {
    return (rand() % max + min);
}

vector<string> split_string(const string& str) {
    istringstream iss(str);
    string s;
    vector<string> v;

    while (getline(iss, s, ' ')) {
        v.push_back(s);
    }

    return v;
}

string get_quote() {
    char path[MAX_PATH];
    GetModuleFileName(NULL, path, MAX_PATH);
    filesystem::current_path(filesystem::path(path).parent_path().string());
 
    ifstream file("quotes.txt");

    if (!file.is_open()) {
        throw runtime_error("Could not open file");
    }

    vector<string> lines;
    string line;

    while (getline(file, line)) {
        lines.push_back(line);
    }

    file.close();

    return lines[randint(0, lines.size() - 1)];
}

string format_quote(const string& quote) {
    auto words = split_string(quote);

    vector<string> lines;
    string curr_str = " ";

    while (!words.empty()) {
        curr_str += words[0] + " ";
        words.erase(words.begin());

        if (!words.empty()) {
            if (curr_str.size() + words[0].size() >= max_width) {
                lines.push_back(curr_str);

                curr_str = " ";
            }
        }
    }

    if (!curr_str.empty()) {
        lines.push_back(curr_str);
    }

    string fquote = "";
    
    for (auto line : lines) {
        fquote += line + "\n";
    }

    return fquote;
}

int main() {
    srand(high_resolution_clock::now().time_since_epoch().count());

    string quote = get_quote();
    
    max_width = min((int)quote.size() + 2, max_width);

    cout << string(max_width, '_') << endl;

    cout << format_quote(quote);
    
    cout << string(max_width, '-') << endl;
    cout << string(4, ' ') << "\\" << endl;
    cout << string(5, ' ') << "\\" << endl;

    system("type 8ball.txt");
}

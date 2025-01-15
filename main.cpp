#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

// Assings the questions based off poping last value of an array
// expects an vector where each value is repeated thrice
void assign_questions_triple_approach(
    std::vector<int> &questions,
    std::map<std::string, std::set<int>> &q_assignments_map,
    const std::vector<std::string> &names)
{
    int num_questions = std::size(questions);
    int num_names = std::size(names);

    for (int i = 0; !questions.empty(); i++) {
        int question = questions.back();
        const std::string & name = names[i % num_names];
        q_assignments_map[name].insert(question);
        questions.pop_back();
    }
}

// prints out each persons question assingments
void display_assignments(const std::map<std::string, std::set<int>> &q_assignments_map)
{
    // finds the longest name in the map and uses that for io manip
    size_t longest_name = 0;
    for (const std::pair<std::string, std::set<int>> & name : q_assignments_map) {
        longest_name = std::max(longest_name, name.first.size());
    }

    for (const std::pair<std::string, std::set<int>> & name : q_assignments_map)
    {
        std::cout << std::left << std::setw(longest_name) << name.first << ": ";
        for (const int& q : name.second)
        {
            std::cout << q << " ";
        }
        std::cout << std::endl;
    }
}

// reads in the group members names from a file and expects a file formated like:
// Charlotte
// Adeline
// Benny
// Justin
// Simon
void read_names(std::ifstream& file, std::vector<std::string>& names) {
    while (!file.eof()) {
        std::string s;
        std::getline(file, s);
        names.push_back(s);
    }
}

// reads in the questions from a file expects a file fomrmated like:
// 1 2 3 4 5
std::vector<int> read_questions(std::ifstream& file) {
    std::vector<int> v;
    while (!file.eof()) {
        int x;
        file >> x;

        if (file.fail()) {
            throw std::invalid_argument("Non integer in question file");
        }

        // we push everything thrice for equity reasons
        for (int i= 0; i < 3; i++) {
            v.push_back(x);
        }
    }

    return v;
}


int main(int argc, char** arg_v)
{
    int q_count = 0;
    std::vector<std::string> names;
    std::vector<std::vector<int>> questions;

    // checks comand line arguments for file names
    if (argc > 1) {
        // reads in the name file first
        std::ifstream name_file = std::ifstream(arg_v[1]);
        if (name_file.fail()) {
            std::cout << arg_v[1] << " was not a valid file" << std::endl;
            return -1;
        }
        read_names(name_file, names);
        name_file.close();
        
        // then reads in the question names
        for (int i = 2; i < argc; i++) {
            std::ifstream tmp_file = std::ifstream(arg_v[i]);
            if (tmp_file.fail()) {
                std::cout << arg_v[i] << "was not a valid file skipping" << std::endl;
                continue;
            }
            std::vector<int> qs = read_questions(tmp_file);
            q_count += qs.size();
            questions.push_back(qs);
            tmp_file.close();
        }
    } else {
        std::cout << "No file names provided" << std::endl;
        return -1;
    }

    // creates the maping of names to question numbers
    std::map<std::string, std::set<int>> q_assignments_map;
    for (const std::string& name : names)
    {
        q_assignments_map[name] = std::set<int>();
    }

    for (int i = 0; i < questions.size(); i++) {
        assign_questions_triple_approach(questions[i], q_assignments_map, names);
    }


    display_assignments(q_assignments_map);

    return 0;
}

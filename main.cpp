#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

void assign_questions(
    const std::vector<int> &questions,
    std::map<std::string, std::set<int>> &q_assignments_map,
    const std::vector<std::string> &names
) {
    int num_questions = questions.size();
    int num_names = names.size();
    for (int i = 0; i < num_questions; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            const std::string& assigned_name = names[(i + j) % num_names];
            q_assignments_map[assigned_name].insert(questions[i]);
        }
    }
}

void equalize_assignments(
    const int question_count,
    std::map<std::string, std::set<int>>& q_assignments_map
) {
    int max = 0;
    for (const std::pair<std::string, std::set<int>>& p: q_assignments_map) {
        max = std::max(max, (int)p.second.size());
    }

    for ( auto & p: q_assignments_map) {
        if (p.second.size() < max - 2) {
            // asing questions
            int qs_to_assing = (max - 1) - p.second.size();
            for (int i = 0; p.second.size() < max - 2; i++) {
                p.second.insert((i % question_count) + 1);
            }
        }
    }

}

void display_assignments( const std::map<std::string, std::set<int>> &q_assignments_map)
{
    for (const std::pair<std::string, std::set<int>> & name : q_assignments_map)
    {
        std::cout << name.first << ": ";
        for (const int& q : name.second)
        {
            std::cout << q << " ";
        }
        std::cout << std::endl;
    }
}

void read_names(std::ifstream& file, std::vector<std::string>& names) {
    while (!file.eof()) {
        std::string s;
        std::getline(file, s);
        names.push_back(s);
    }
}

std::vector<int> read_questions(std::ifstream& file) {
    std::vector<int> v;
    while (!file.eof()) {
        int x;
        file >> x;

        if (file.fail()) {
            throw std::invalid_argument("Non integer in question file");
        }

        v.push_back(x);
    }

    return v;
}


int main(int argc, char** arg_v)
{
    int q_count = 0;
    std::vector<std::string> names;
    std::vector<std::vector<int>> questions;

    if (argc > 1) {
        std::ifstream name_file = std::ifstream(arg_v[1]);
        if (name_file.fail()) {
            std::cout << arg_v[1] << " was not a valid file" << std::endl;
            return -1;
        }
        read_names(name_file, names);
        name_file.close();
        
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
        return 0;
    }

    std::map<std::string, std::set<int>> q_assignments_map;
    for (const std::string& name : names)
    {
        q_assignments_map[name];
    }

    for (int i = 0; i < questions.size(); i++) {
        assign_questions(questions[i], q_assignments_map, names);
    }

    equalize_assignments(q_count, q_assignments_map);

    display_assignments(q_assignments_map);

    return 0;
}

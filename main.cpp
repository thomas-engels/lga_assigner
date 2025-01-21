#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>

void assign_questions(
    std::vector<int> &questions,
    std::map<std::string, std::vector<int>> &q_assignments_map,
    std::vector<std::string> names,
    int names_size) {
    int num_questions = std::size(questions);
    std::queue<int> triple_questions;
    for (int i = 0; i < num_questions; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            triple_questions.push(questions[i]);
        }
    }

    int i = 0;
    while (!triple_questions.empty())
    {
        int question = triple_questions.front();
        std::string & name = names[i % names_size];
        q_assignments_map[name].push_back(question);
        triple_questions.pop();
        i += 1;
    }
}


void display_assignments(
    const std::map<std::string, std::vector<int>> &q_assignments_map)
{
    int name_width = 10;
    int question_width = 10;
    std::cout << std::setw(name_width) << std::left << "Name"
    << std::setw(question_width) << std::right << "Question" << std::endl;

    std::cout << std::setfill('-');
    std::cout << std::setw(name_width + question_width) << "" << std::endl;
    std::cout << std::setfill(' ');

    for (const auto & name : q_assignments_map)
    {
        std::cout << std::setw(name_width) << std::left << name.first << std::setw(question_width);
        std::string question;
        for (const auto & q : name.second)
        {
            question += " ";
            question += std::to_string(q);
        }
        std::cout << std::right << question;
        std::cout << std::endl;
    }

    std::cout << std::setfill('-');
    std::cout << std::setw(name_width + question_width) << "" << std::endl;
}


void read_names(
    std::ifstream& file,
    std::vector<std::string>& names)
{
    while (!file.eof())
    {
        std::string s;
        std::getline(file, s);
        names.push_back(s);
    }
}

std::vector<int> read_questions(
    std::ifstream& file)
{
    std::vector<int> v;
    while (!file.eof())
    {
        int x;
        file >> x;
        v.push_back(x);
    }
    return v;
}

/* Directions for running this script:
 * Compile main.cpp aka create the executable on the CLI: `g++ --std=c++17 main.cpp -o main`
 * Execute the executable and link your txt files (names, questions): `./main names.txt easy_questions.txt intermediate_questions.txt`
 *
 * Extra notes:
 * - You need at least 1 question set txt file and can add more as you wish. They simply need to be txt files, any file name will work.
 * - Your names.txt file must always be the second argument in the executable.
 * - However, order does not matter for the question sets. E.G. `./main names.txt easy_questions.txt intermediate_questions.txt`
 *   and `./main names.txt intermediate_questions.txt basic_questions.txt` will both achieve your outcome.
*/
int main(
    int argc,
    char** arg_v)
{
    try
    {
        std::vector<std::string> names;
        std::ifstream name_file = std::ifstream(arg_v[1]);
        if (!name_file)
        {
            std::cerr << "Error opening file " << arg_v[1] << std::endl;
            throw std::runtime_error("Error opening file");
        }

        read_names(name_file, names);
        std::map<std::string, std::vector<int> > q_assignments_map;

        int names_size = 0;
        for (const std::string &name: names)
        {
            q_assignments_map[name];
            names_size += 1;
        }

        for (int i = 2; i < argc; ++i)
        {
            std::ifstream question_file = std::ifstream(arg_v[i]);
            if (!question_file)
            {
                std::cerr << "Error opening file " << arg_v[i] << std::endl;
                throw std::runtime_error("Error opening file");
            }

            std::vector<int> questions = read_questions(question_file);
            assign_questions(questions, q_assignments_map, names, names_size);
            std::reverse(names.begin(), names.end());
        }

        display_assignments(q_assignments_map);

        std::cout << std::endl;
        std::cout << "Thank you for using the LGA Assigner script!\n\n"
                     "If you found this script truly useful, please give it a star on Github (https://github.com/thomas-engels/lga_assigner). "
                     "I would be tremendously grateful.\n\n"
                     "If you have any feedback, you can send it directly to tbengels@gmail.com or an open an issue on Github.\n\n"
                     "Thank you,\n"
                     "Tommy Engels" << std::endl;
        std::cout << "" << std::endl;
    }

    catch (const std::exception& e)
    {
        std::cout << "Please review your txt files and executable argument order."
        << std::endl;
        std::cout << "==============Other Helpful Reminders==============" << std::endl;
        std::cout << "Compile the code using: g++ --std=c++17 main.cpp -o main" << std::endl;
        std::cout << "Execute and link the code using: ./main names.txt basic_questions.txt intermediate_questions.txt"
        << std::endl;
        std::cout << "If you are unable to resolve the issue, please send me an email explaining your error at "
                     "tbengels@gmail.com." << std::endl << std::endl;
    }

    return 0;
}

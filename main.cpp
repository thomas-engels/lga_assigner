#include <iostream>
#include <map>

void initialize_data(
    std::vector<int> &basic_questions,
    std::vector<int> &intermediate_questions,
    std::vector<std::string> &names,
    std::map<std::string,std::vector<int>> &q_assignments_map)
{
    basic_questions = {1,2,5,6,7};
    intermediate_questions = {3,4,8,9};
    names = {"Ally", "Marcus", "Julia", "Max", "Tommy"};
    for (const auto & name : names)
    {
        q_assignments_map[name];
    }
}

void assign_questions(
    std::vector<int> &questions,
    std::map<std::string, std::vector<int>> &q_assignments_map,
    std::vector<std::string> &names)
{
    int num_questions = std::size(questions);
    // if using older version of C++, use (sizeof(questions) / size(int)) to get the vector length etc.
    int num_names = std::size(names);
    for (int i = 0; i < num_questions; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            const std::string& assigned_name = names[(i + j) % num_names];
            q_assignments_map[assigned_name].push_back(questions[i]);
        }
    }
}

void display_assignments(
    const std::map<std::string, std::vector<int>> &q_assignments_map)
{
    for (const auto & name : q_assignments_map)
    {
        std::cout << name.first << ": ";
        for (const auto & q : name.second)
        {
            std::cout << q << " ";
        }
        std::cout << std::endl;
    }
}


int main() {

    std::vector<int> intermediate_questions;
    std::vector<int> basic_questions;
    std::vector<std::string> names;
    std::map<std::string, std::vector<int>> q_assignments_map;

    initialize_data(basic_questions, intermediate_questions, names, q_assignments_map);

    assign_questions(basic_questions, q_assignments_map, names);
    assign_questions(intermediate_questions, q_assignments_map, names);

    display_assignments(q_assignments_map);

    return 0;
}

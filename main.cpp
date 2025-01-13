#include <iostream>
#include <map>
#include <queue>

void assign_questions(
    std::vector<int> &questions,
    std::map<std::string, std::vector<int>> &q_assignments_map,
    std::vector<std::string> &names)
{
    int num_questions = std::size(questions);
    int num_names = std::size(names);

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
        std::string & name = names[i % num_names];
        q_assignments_map[name].push_back(question);
        triple_questions.pop();
        i += 1;
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


int main()
{
    std::vector<int> intermediate_questions = {1, 2, 3, 4};
    // std::vector<int> basic_questions = {3, 4, 6};
    std::vector<std::string> names = {"Ally", "Marcus", "Tommy", "Julia", "Max"};
    std::vector<std::string> names_reverse = { "Max", "Julia","Tommy", "Marcus", "Ally"};
    std::map<std::string, std::vector<int>> q_assignments_map;
    for (const auto & name : names)
    {
        q_assignments_map[name];
    }

    // assign_questions(basic_questions, q_assignments_map, names);
    assign_questions(intermediate_questions, q_assignments_map, names_reverse);

    display_assignments(q_assignments_map);

    return 0;
}

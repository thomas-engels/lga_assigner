#include <iostream>
#include <map>
#include <queue>

void assign_questions(
    std::vector<int> &questions,
    std::map<std::string, std::vector<int>> &q_assignments_map,
    std::string names [],
    int names_size)
{
    int num_questions = std::size(questions);
    // int num_names = sizeof(names)/sizeof(std::string);

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
    std::vector<int> intermediate_questions = {2, 3, 4};
    std::vector<int> basic_questions = {1, 5};
    std::string names[] = {"Marcus", "Ally", "Tommy","Max", "Julia"};
    int names_length = std::size(names);
    std::string names_reverse[] = {"Tommy", "Julia", "Max", "Ally", "Marcus"};

    std::map<std::string, std::vector<int>> q_assignments_map;
    for (const auto & name : names)
    {
        q_assignments_map[name];
    }

    assign_questions(basic_questions, q_assignments_map, names, names_length);
    assign_questions(intermediate_questions, q_assignments_map, names_reverse, names_length);

    display_assignments(q_assignments_map);

    return 0;
}

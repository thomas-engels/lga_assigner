#include <iostream>
#include <map>

void assign_questions(
    std::vector<int> &questions,
    std::map<std::string, std::vector<int>> &q_assignments_map,
    std::vector<std::string> &names)
{
    int num_questions = std::size(questions);
    int num_names = std::size(names);



    for (int i = 0; i < num_questions; i++)
    {
        std::string & name = names[i % num_names];
        q_assignments_map[name].push_back(questions[i]);
        // for (int j = 0; j < 3; j++)
        // {
        //     std::string & assigned_name = names[j % num_names];
        //     std::cout << " " << assigned_name << std::endl;
        //     q_assignments_map[assigned_name].push_back(questions[i]);
        // }
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
    std::vector<int> intermediate_questions = {3, 3, 3, 4, 4, 4, 8, 8, 8, 9, 9, 9, 10, 10, 10, 11, 11, 11};
    // std::vector<int> basic_questions = {1, 2, 5, 6, 7, 10};
    std::vector<std::string> names = {"Ally", "Marcus", "Julia", "Max", "Tommy"};
    std::map<std::string, std::vector<int>> q_assignments_map;
    for (const auto & name : names)
    {
        q_assignments_map[name];
    }

    // assign_questions(basic_questions, q_assignments_map, names);
    assign_questions(intermediate_questions, q_assignments_map, names);

    display_assignments(q_assignments_map);

    return 0;
}

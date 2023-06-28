#include <iostream>
#include <vector>

class Command
{
public:
    char commandType;
    int identificator;
};

class Worker
{
    std::string workerName;
    int workerID;
    Command* command;

public:

    std::string getName()
    {
        return workerName;
    }

    int getID()
    {
        return workerID;
    }

    void setCommand(Command* command)
    {
        this->command = command;
    }
    
    Worker(std::string name, int id): workerName(name), workerID(id)
    {
        command = nullptr;
    }
};

class Structure
{
public:
    
    Worker* teamLider;
     
};

class Team : public Structure
{
public:
    int taskCount;
    std::vector<Worker*> workers;

    Team(Worker* leader)
    {
        int tempWorkersCount = 0;
        std::string tempName;
        int tempID;
        std::cout << "Enter workers count: ";
        std::cin >> tempWorkersCount;
        for (int i = 0; i < tempWorkersCount; i++)
        {
            std::cout << "Enter Worker name: ";
            std::cin >> tempName;
            std::cout << "Enter Worker ID: ";
            std::cin >> tempID;
            Worker* worker = new Worker(tempName, tempID);
            workers.push_back(worker);
        }
    }
};

class Company : public Structure
{
    std::vector<Team*> units;

    Company()
    {
        int tempTeamCount = 0;
        std::string tempName;
        int tempID;
        std::cout << "Enter a count of company's teams: ";
        std::cin >> tempTeamCount;
        for (int i = 0; i < tempTeamCount; i++)
        {
            std::cout << "Enter Team Leader's name: ";
            std::cin >> tempName;
            std::cout << "Enter Team Leader's ID: ";
            std::cin >> tempID;
            Worker* teamLider = new Worker(tempName, tempID);
            Team* team = new Team(teamLider);
        }
    }
};



int main()
{
    std::cout << "Company simulation!" << std::endl;
}
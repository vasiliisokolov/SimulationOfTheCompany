#include <iostream>
#include <vector>

class Command
{
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
};

class Team
{
    int teamID;
    Worker* teamLider;
    int taskCount;
    int workerCount;
    std::vector<Worker*> workers;
public:

    
};

int main()
{
    std::cout << "Hello World!\n";
}
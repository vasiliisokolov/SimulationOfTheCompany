#include <iostream>
#include <vector>

class Command
{
public:
    
    int identificator;

    Command(int inId)
    {
        if (inId < 0) inId = 0;
        else if (inId > 100) inId = 100;
        identificator = inId;
    }
};

class Task : public Command
{
public:
    char commandType;

    Task(char inType, int inId): Command(inId)
    {
        if (inType != 'A' && inType != 'B' && inType != 'C')
        {
            inType = 'A';
        }
        commandType = inType;
        
    }
};

class HR
{
    std::string workerName;
    int workerID;
public:

    std::string getName()
    {
        return workerName;
    }

    int getID()
    {
        return workerID;
    }

    

    HR(std::string name, int id) : workerName(name), workerID(id)
    {
        
    }
};

class Manager : public HR
{

    Command* command;

public:
    void setCommand(Command* command)
    {
        this->command = command;
    }

    Manager(std::string name, int id) : HR(name, id)
    {
        command = nullptr;
    }

    Command* getCommand()
    {
        return command;
    }
};
class Worker: public HR
{
    
    Task* task;

public:

    void setTask(Task* task)
    {
        this->task = task;
    }
    
    Worker(std::string name, int id): HR(name, id)
    {
        task = nullptr;
    }
};

class Structure
{
public:
    
    Manager* teamLider;
    bool freeWorkers;
     
};

class Team : public Structure
{
public:
    int taskCount;
    std::vector<Worker*> workers;

    void makeCommand(Command* companyLeaderCommand)
    {
        std::srand(companyLeaderCommand->identificator + teamLider->getID());
        taskCount = rand() % (this->workers.size() + 1);
        for (int i = 0; i < workers.size(); i++)
        {
            
        }
    }

    Worker* getWorker(int i)
    {
        if (i > workers.size()) return nullptr;
        return workers[i];
    }

    Team(Manager* leader)
    {
        freeWorkers = true;
        taskCount = 0;
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
public:
    std::vector<Team*> units;

    void sendCommand()
    {
        for (int i = 0; i < units.size(); i++)
        {
            units[i]->makeCommand(teamLider->getCommand());
        }
    }

    Company()
    {
        freeWorkers = true;
        int tempTeamCount = 0;
        std::string tempName;
        int tempID;
        std::cout << "Enter Company Leader's name: ";
        std::cin >> tempName;
        std::cout << "Enter Company Leader's ID: ";
        std::cin >> tempID;
        teamLider = new Manager(tempName, tempID);
        std::cout << "Enter a count of company's teams: ";
        std::cin >> tempTeamCount;
        for (int i = 0; i < tempTeamCount; i++)
        {
            std::cout << "Enter Team Leader's name: ";
            std::cin >> tempName;
            std::cout << "Enter Team Leader's ID: ";
            std::cin >> tempID;
            Manager* teamLider = new Manager(tempName, tempID);
            Team* team = new Team(teamLider);
            units.push_back(team);
        }
    }

    ~Company()
    {
        delete teamLider;
        for (int i = 0; i < units.size(); i++)
        {
            delete units[i]->teamLider;
            for (int j = 0; j < units[i]->workers.size(); j++)
            {
                delete units[i]->workers[i];
            }
            delete units[i];
        }
    }
};



int main()
{
    std::cout << "Company simulation!" << std::endl;
    Company* company = new Company();
    int tempCommand{};
    
    while(true)
    {
        std::cout << "Enter the command: ";
        std::cin >> tempCommand;
        if (tempCommand == 0) break;
        Command* command = new Command(tempCommand);
        company->teamLider->setCommand(command);
        company->sendCommand();
    }
    delete company;
}
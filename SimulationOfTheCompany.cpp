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

    Task(int inType, int inId): Command(inId)
    {
        switch (inType)
        {
        case 1:
            commandType = 'A';
            break;
        case 2:
            commandType = 'B';
            break;
        case 3:
            commandType = 'C';
            break;
        }
                
    }
};

class HR
{
    std::string workerName;
    int workerID;
public:

    bool free;

    std::string getName()
    {
        return workerName;
    }

    int getID()
    {
        return workerID;
    }

    void setName(std::string name)
    {
        workerName = name;
    }
    
    void setId(int id)
    {
        workerID = id;
    }

    HR(std::string name, int id)
    {
        setName(name);
        setId(id);
        free = true;
    }
};

class Manager : public HR
{

    Command* command;

public:
    void setCommand(Command* command)
    {
        this->command = command;
        std::cout << "Manager " << getName() << " get task: " << getCommand()->identificator << std::endl;
        free = false;
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

    Task* getTask()
    {
        return task;
    }
    void setTask(Task* task)
    {
        this->task = task;
        std::cout << "Worker " << getName() << " get task: " << getTask()->commandType 
            << getTask()->identificator << std::endl;
        free = false;
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

    void checkFreeWorkers()
    {
        int counter = 0;
        for (int i = 0; i < workers.size(); i++)
        {
            if (workers[i]->free) counter++;
        }
        if (counter == 0) this->freeWorkers = false;
    }

    void makeCommand(Command* companyLeaderCommand)
    {
        teamLider->setCommand(companyLeaderCommand);
        int inCommand = companyLeaderCommand->identificator + teamLider->getID();
        std::srand(inCommand);
        taskCount = rand() % (this->workers.size() + 1);
        for (int i = 0; i < workers.size() && taskCount > 0; i++)
        {
            if (getWorker(i)->getTask() == nullptr)
            {
                int inTask = 1 + rand() % 2;
                Task* task = new Task(inTask, inCommand);
                getWorker(i)->setTask(task);
                taskCount--;
            }
        }
        checkFreeWorkers();
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
        teamLider = leader;
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

    void checkFreeTeam()
    {
        int counter = 0;
        for (int i = 0; i < units.size(); i++)
        {
            if (units[i]->freeWorkers) counter++;
        }
        if (counter == 0) this->freeWorkers = false;
    }

    void sendCommand()
    {
        for (int i = 0; i < units.size(); i++)
        {
            if (units[i]->freeWorkers)
            {
                units[i]->makeCommand(teamLider->getCommand());
            }
        }
        checkFreeTeam();
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
            delete units[i]->teamLider->getCommand();
            delete units[i]->teamLider;
            for (int j = 0; j < units[i]->workers.size(); j++)
            {
                delete units[i]->workers[j]->getTask();
                delete units[i]->workers[j];
            }
            delete units[i];
        }
    }
};



int main()
{
    std::cout << "Company simulation!" << std::endl;
    Company* company = new Company();
        
    while(company->freeWorkers)
    {
        int tempCommand = 0;
        std::cout << "Enter the command: ";
        std::cin >> tempCommand;
        if (tempCommand == 0) break;
        Command* command = new Command(tempCommand);
        company->teamLider->setCommand(command);
        company->sendCommand();
        delete command;
    }
    delete company;
}
#include "maze.h"
#include <cstdlib>
#include <ctime>

Maze::Node::Node(int value, std::shared_ptr<Maze::Node> _parent)
    : parent {_parent}
    , mValue {value}
{}

int Maze::Node::getValue() const
{
    return  mValue;
}

bool Maze::Node::getIsWin() const
{
    return isWin;
}

void Maze::Node::setValue(int value)
{
    mValue = value;
}

void Maze::Node::setIsWin(bool w)
{
    isWin = w;
}

Maze::Maze(size_t n, size_t m)
{
    maze.resize(n+2);
    for (size_t i{}; i<n+2; i++)
    {
        maze[i].resize(m+2);
        for (size_t j{}; j<m+2; j++)
        {
            if (i==0 || i==n+1 || j==0 || j==m+1)
            {
                std::shared_ptr<Maze::Node> node {std::make_shared<Maze::Node>(4)};
                maze[i][j] = node;
            }
            else
            {
                std::shared_ptr<Maze::Node> node {std::make_shared<Maze::Node>()};
                maze[i][j] = node;
            }
        }
    }
    root = maze[1][1];
    root->setValue(2);
    maze[1][0]->setValue(5);
    std::srand(std::time(nullptr));

    createMaze(1, 1);
    if (maze[n][m]->getValue() == 2)
    {
        maze[n][m]->setIsWin(true);
        maze[n][m+1]->setValue(6);
    }
    else
    {
        maze[n-1][m]->setIsWin(true);
        maze[n-1][m+1]->setValue(6);
    }
}

void Maze::createMaze(size_t x, size_t y)
{
    std::shared_ptr<Maze::Node> node {maze[x][y]};
    int randNum = std::rand() % 4;
    while(anyEmptyPath(x, y))
    {
        switch (randNum)
        {
        case 0:
            if (maze[x+1][y]->getValue() == 0)
            {
                node->children.push_back(maze[x+1][y]);
                maze[x+1][y]->parent = node;
                maze[x+1][y]->setValue(2);
                placeWall(x+1, y);
                createMaze(x+1,y);
            }
            randNum = std::rand() % 4;
            break;

        case 1:
            if (maze[x-1][y]->getValue() == 0)
            {
                node->children.push_back(maze[x-1][y]);
                maze[x-1][y]->parent = node;
                maze[x-1][y]->setValue(2);
                placeWall(x-1, y);
                createMaze(x-1,y);
            }
            randNum = std::rand() % 4;
            break;

        case 2:
            if (maze[x][y+1]->getValue() == 0)
            {
                node->children.push_back(maze[x][y+1]);
                maze[x][y+1]->parent = node;
                maze[x][y+1]->setValue(2);
                placeWall(x, y+1);
                createMaze(x,y+1);
            }
            randNum = std::rand() % 4;
            break;

        case 3:
            if (maze[x][y-1]->getValue() == 0)
            {
                node->children.push_back(maze[x][y-1]);
                maze[x][y-1]->parent = node;
                maze[x][y-1]->setValue(2);
                placeWall(x, y-1);
                createMaze(x,y-1);
                randNum = std::rand() % 4;
                break;
            }
            randNum = std::rand() % 4;
            break;
        }
    }
}

bool Maze::anyEmptyPath(size_t x, size_t y)
{
    if (maze[x+1][y]->getValue() == 0)
        return true;
    if (maze[x-1][y]->getValue() == 0)
        return true;
    if (maze[x][y+1]->getValue() == 0)
        return true;
    if (maze[x][y-1]->getValue() == 0)
        return true;
    return false;
}

void Maze::placeWall(size_t x, size_t y)
{
    if (maze[x+1][y]->getValue() == 0)
    {
        if(maze[x+2][y]->getValue() == 2)
            maze[x+1][y]->setValue(3);
        if(maze[x+1][y+1]->getValue() == 2)
            maze[x+1][y]->setValue(3);
        if(maze[x+1][y-1]->getValue() == 2)
            maze[x+1][y]->setValue(3);
    }
    if (maze[x-1][y]->getValue() == 0)
    {
        if(maze[x-2][y]->getValue() == 2)
            maze[x-1][y]->setValue(3);
        if(maze[x-1][y+1]->getValue() == 2)
            maze[x-1][y]->setValue(3);
        if(maze[x-1][y-1]->getValue() == 2)
            maze[x-1][y]->setValue(3);
    }
    if (maze[x][y+1]->getValue() == 0)
    {
        if(maze[x][y+2]->getValue() == 2)
            maze[x][y+1]->setValue(3);
        if(maze[x-1][y+1]->getValue() == 2)
            maze[x][y+1]->setValue(3);
        if(maze[x+1][y+1]->getValue() == 2)
            maze[x][y+1]->setValue(3);
    }
    if (maze[x][y-1]->getValue() == 0)
    {
        if(maze[x][y-2]->getValue() == 2)
            maze[x][y-1]->setValue(3);
        if(maze[x-1][y-1]->getValue() == 2)
            maze[x][y-1]->setValue(3);
        if(maze[x+1][y-1]->getValue() == 2)
            maze[x][y-1]->setValue(3);
    }
}

std::vector<std::vector<int>> Maze::solve(size_t algInt)
{
    if (algInt == 1)
        solveDFS(root);
    else if (algInt == 2)
        solveBFS();
    std::vector<std::vector<int>> mazeData;
    mazeData.resize(maze.size());
    for (size_t i{}; i<maze.size(); i++)
    {
        for (size_t j{}; j<maze[i].size(); j++)
        {
            mazeData[i].push_back(maze[i][j]->getValue());
        }
    }
    return mazeData;
}

bool Maze::solveDFS(std::shared_ptr<Maze::Node> node)
{
    bool isWinhere {false};
    isWinhere = node->getIsWin();
    if (!isWinhere)
    {
        for (const auto& child : node->children)
        {
            if (solveDFS(child))
            {
                isWinhere = true;
                break;
            }
        }
    }
    if (isWinhere)
        node->setValue(1);
    return isWinhere;
}

void Maze::solveBFS()
{
    if (root->getIsWin())
    {
        drawPath(root);
        return;
    }
    std::unique_ptr<std::list<std::shared_ptr<Maze::Node>>> tempQueue {std::make_unique<std::list<std::shared_ptr<Maze::Node>>>()};
    tempQueue->merge(root-> children);
    while (true)
    {
        std::unique_ptr<std::list<std::shared_ptr<Maze::Node>>> queue {};
        queue = std::move(tempQueue);
        tempQueue = std::make_unique<std::list<std::shared_ptr<Maze::Node>>>();
        for (auto itr{queue->begin()}; itr!=queue->end(); itr++){
            if ((*itr)->getIsWin())
            {
                drawPath(*itr);
                return;
            }
            tempQueue->merge((*itr)->children);
        }
    }
}

void Maze::drawPath(std::shared_ptr<Maze::Node> node)
{
    node->setValue(1);
    if (node->parent)
    {
        drawPath(node->parent);
    }
}

void Maze::show() const
{
    std::cout << "6:goal position, 5:start position, 4: solid wall, 3: wall, 2: path, 1: solved path \n\n";
    for (size_t i{}; i<maze.size(); i++)
    {
        for (size_t j{}; j<maze[i].size(); j++)
        {
            std::cout << " " << maze[i][j]->getValue();
        }
        std::cout << std::endl;
    }
}

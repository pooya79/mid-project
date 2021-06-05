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
                node->pos.first = i;
                node->pos.second = j;
                maze[i][j] = node;
            }
            else
            {
                std::shared_ptr<Maze::Node> node {std::make_shared<Maze::Node>()};
                node->pos.first = i;
                node->pos.second = j;
                maze[i][j] = node;
            }
        }
    }
    root = maze[1][1];
    root->setValue(2);
    maze[1][0]->setValue(5);
    std::srand(std::time(nullptr));

    createMaze(1, 1);
    while (true)
    {
        if (maze[n][m]->getValue() == 2)
        {
            goal = maze[n][m];
            maze[n][m]->setIsWin(true);
            maze[n][m+1]->setValue(6);
            break;
        }
        n--;
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
                node->neighbors.push_back(maze[x+1][y]);
                maze[x+1][y]->neighbors.push_back(node);
                maze[x+1][y]->setValue(2);
                placeWall(x+1, y);
                createMaze(x+1,y);
            }
            randNum = std::rand() % 4;
            break;

        case 1:
            if (maze[x-1][y]->getValue() == 0)
            {
                node->neighbors.push_back(maze[x-1][y]);
                maze[x-1][y]->neighbors.push_back(node);
                maze[x-1][y]->setValue(2);
                placeWall(x-1, y);
                createMaze(x-1,y);
            }
            randNum = std::rand() % 4;
            break;

        case 2:
            if (maze[x][y+1]->getValue() == 0)
            {
                node->neighbors.push_back(maze[x][y+1]);
                maze[x][y+1]->neighbors.push_back(node);
                maze[x][y+1]->setValue(2);
                placeWall(x, y+1);
                createMaze(x,y+1);
            }
            randNum = std::rand() % 4;
            break;

        case 3:
            if (maze[x][y-1]->getValue() == 0)
            {
                node->neighbors.push_back(maze[x][y-1]);
                maze[x][y-1]->neighbors.push_back(node);
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
    else if (algInt == 3)
        solveBS();
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
    if (node->parent)
        node->neighbors.remove(node->parent);
    placeParent(node->neighbors, node);
    if (!isWinhere)
    {
        for (const auto& child : node->neighbors)
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
    std::list<std::shared_ptr<Maze::Node>> tempQueue {root->neighbors};
    placeParent(tempQueue, root);
    while (true)
    {
        std::list<std::shared_ptr<Maze::Node>> queue {tempQueue};
        tempQueue.clear();
        for (auto itr{queue.begin()}; itr!=queue.end(); itr++){
            if ((*itr)->getIsWin())
            {
                drawPath(*itr);
                return;
            }
            (*itr)->neighbors.remove((*itr)->parent);
            placeParent((*itr)->neighbors, *itr);
            merge(tempQueue, (*itr)->neighbors);
        }
    }
}

void Maze::solveBS()
{

    if (root->getIsWin())
    {
        drawPath(root);
        return;
    }
    int turn {};
    std::shared_ptr<Maze::Node> intersectionNode;
    std::list<std::shared_ptr<Maze::Node>> tempQueue1 {root->neighbors};
    placeParent(tempQueue1, root);
    std::list<std::shared_ptr<Maze::Node>> tempQueue2 {goal->neighbors};
    placeParent(tempQueue2, goal);
    while (true)
    {
        std::list<std::shared_ptr<Maze::Node>> queue1 {tempQueue1};
        std::list<std::shared_ptr<Maze::Node>> queue2 {tempQueue2};
        tempQueue1.clear();
        tempQueue2.clear();
        for (auto itr1{queue1.begin()}, itr2{queue2.begin()}; itr1!=queue1.end() || itr2!=queue2.end(); turn++){
            if (turn%2 && itr1!=queue1.end())
            {
                (*itr1)->neighbors.remove((*itr1)->parent);
                intersectionNode = placeParent((*itr1)->neighbors, *itr1);
                if (intersectionNode)
                {
                    drawPath(intersectionNode);
                    drawPath(*itr1);
                    return;
                }
                merge(tempQueue1, (*itr1)->neighbors);
                itr1++;
            }
            else if (!(turn%2) && itr2!=queue2.end())
            {
                (*itr2)->neighbors.remove((*itr2)->parent);
                intersectionNode = placeParent((*itr2)->neighbors, *itr2);
                if (intersectionNode)
                {
                    drawPath(intersectionNode);
                    drawPath(*itr2);
                    return;
                }
                merge(tempQueue2, (*itr2)->neighbors);
                itr2++;
            }
        }
    }
}

std::shared_ptr<Maze::Node> Maze::placeParent(std::list<std::shared_ptr<Maze::Node>>& _neighbors, std::shared_ptr<Maze::Node> _parent)
{
    for (auto itr{_neighbors.begin()}; itr!=_neighbors.end(); itr++)
    {
        if ((*itr)->parent)
        {
            return *itr;
        }
        (*itr)->parent = _parent;
    }
    return nullptr;
}

void Maze::merge(std::list<std::shared_ptr<Maze::Node>>& l1, std::list<std::shared_ptr<Maze::Node>>& l2)
{
    for (std::shared_ptr<Maze::Node>& neighbor : l2)
    {
        l1.push_back(neighbor);
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

std::shared_ptr<Maze::Node> Maze::getRoot() const
{
    return root;
}

std::shared_ptr<Maze::Node> Maze::getGoal() const
{
    return goal;
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

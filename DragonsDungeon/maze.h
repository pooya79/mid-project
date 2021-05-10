#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <memory>
#include <list>
#include <vector>

class Maze
{
public:
    class Node
    {
    public:
        // constructors
        Node(int value=0, std::shared_ptr<Node> parent=nullptr);

        // getters
        int getValue() const;
        bool getIsWin() const;

        // setters
        void setValue(int val);
        void setIsWin(bool w);

        std::shared_ptr<Node> parent;
        std::list<std::shared_ptr<Node>> children {};

    private:
        int mValue;
        bool isWin {false};
    };
    Maze(size_t n=2, size_t m=2);

    void createMaze(size_t x, size_t y);
    bool anyEmptyPath(size_t x, size_t y);
    void placeWall(size_t x, size_t y);
    std::vector<std::vector<int>> solve(size_t algInt);
    bool solveDFS(std::shared_ptr<Node> node);
    void solveBFS();
    void drawPath(std::shared_ptr<Node> node);
    void show() const;


private:
    std::vector<std::vector<std::shared_ptr<Node>>> maze;
    std::shared_ptr<Node> root;
};

#endif // MAZE_H

#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <memory>
#include <list>
#include <vector>
#include <QPair>

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
        std::list<std::shared_ptr<Node>> neighbors {};

        QPair<int, int> pos;
    private:
        int mValue;
        bool isWin {false};
    };
    Maze(size_t n=2, size_t m=2);

    // creating maze
    void createMaze(size_t x, size_t y);
    bool anyEmptyPath(size_t x, size_t y);
    void placeWall(size_t x, size_t y);

    // solve maze
    std::vector<std::vector<int>> solve(size_t algInt);
    bool solveDFS(std::shared_ptr<Node> node);
    void solveBFS();
    void solveBS();
    std::shared_ptr<Node> placeParent(std::list<std::shared_ptr<Node>>& _neighbors, std::shared_ptr<Node> _parent);
    void merge(std::list<std::shared_ptr<Maze::Node>>&, std::list<std::shared_ptr<Maze::Node>>&);
    void drawPath(std::shared_ptr<Node> node);

    // getter
    std::shared_ptr<Node> getRoot() const;
    std::shared_ptr<Node> getGoal() const;

    // show maze in terminal
    void show() const;

private:
    std::vector<std::vector<std::shared_ptr<Node>>> maze;
    std::shared_ptr<Node> root;
    std::shared_ptr<Node> goal; // used for BS
};

#endif // MAZE_H

#include "maze.h"
#include <cstdlib>

int main(int argc, char **argv)
{
    std::system("clear");
    size_t n{2}, m{2}, alg{1};
    std::cout << "choose your maze dimention (n*m) (n and m are >= 2)\nn: ";
    std::cin >> n;
    std::cout << "m: ";
    std::cin >> m;
    Maze maze {n, m};
    std::system("clear");
    maze.show();
    std::cout << "\n\n\nsolve this with algorithm (1:DFS, 2:BFS): ";
    std::cin >> alg;
    maze.solve(alg);
    system("clear");
    maze.show();
    return 0;
}

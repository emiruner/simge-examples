#ifndef MY_MAZE_HPP_INCLUDED
#define MY_MAZE_HPP_INCLUDED

#include <simge/glut/Point.hpp>

namespace Direction
{
    enum type
    {
        North,
        East,
        South,
        West
    };
}

struct Location
{
    int x;
    int y;

    Location(int nx, int ny)
    : x(nx), y(ny)
    {
    }
    
    Location()
    {
    }
};

inline bool operator==(Location const& lhs, Location const& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

struct Cell
{
    unsigned int north : 1;
    unsigned int east : 1;
    unsigned int visited : 1;
    unsigned int onPath : 1;
    
    Cell()
    : north(0), east(0), visited(0), onPath(0)
    {
    }
};

class Maze
{
public:
    Maze(int width, int height);
    Maze(Maze const& other);
    ~Maze();
    Maze& operator=(Maze const& rhs);

    // Cell state querying functions
    bool isWallPresent(int x, int y, Direction::type dir) const;
    void setWall(int x, int y, Direction::type dir, bool present);
    bool isVisited(int x, int y);
    void setVisited(int x, int y, bool status);
    void setOnPath(int x, int y, bool status);
    bool isOnPath(int x, int y);
    
    int getWidth() const
    {
        return width_;
    }
    
    int getHeight() const
    {
        return height_;
    }

    /**
     * Tries to reach from p to stop.
     * Returns true if a path exist while setting visited and onPath
     * bits correctly.
     */
    bool solve(Location p, Location stop);

private:
    int width_;
    int height_;
    Cell* cells_;
};

#endif

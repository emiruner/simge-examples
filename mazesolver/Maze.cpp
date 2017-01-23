#include "Maze.hpp"
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <new>
#include <sys/time.h>

using namespace simge::glut;

namespace
{
    inline int xyToOffset(int x, int y, int width)
    {
        return y * width + x;
    }

    inline int getMicroseconds()
    {
        timeval tv;
        
        gettimeofday(&tv, 0);
        
        return tv.tv_usec;
    }
} // namespace <unnamed>

Maze::Maze(int width, int height)
: width_(width), height_(height)
{
    int i;

    srand(getMicroseconds());
    const int cellCount = (width_ + 2) * (height_ + 2);
    
    cells_ = new Cell[cellCount];

    // Randomly set walls
    for(i = 0; i < cellCount; ++i)
    {
        cells_[i].north = rand() % 10 > 5;
        cells_[i].east = rand() % 10 > 5;
    }

    // Seal outer walls
    for(i = 0; i < width_; ++i)
    {
        setWall(i, 0, Direction::North, 1);
        setWall(i, height_ - 1, Direction::South, 1);
    }
    
    for(i = 0; i < height_; ++i)
    {
        setWall(0, i, Direction::West, 1);
        setWall(width_ - 1, i, Direction::East, 1);
    }

    // Open holes at south-west and north-east
    setWall(0, 0, Direction::West, 0);
    setWall(width_ - 1, height - 1, Direction::East, 0);
}

Maze::~Maze()
{
    delete[] cells_;
}

Maze::Maze(Maze const& other)
{
    width_ = other.width_;
    height_ = other.height_;
    
    const int cellCount = (width_ + 2) * (height_ + 2);
    
    cells_ = new Cell[cellCount];

    for(int i = 0; i < cellCount; ++i)
    {
        cells_[i] = other.cells_[i];
    }
}

Maze& Maze::operator=(Maze const& rhs)
{
    if(this != &rhs)
    {
        this->~Maze();
        new (this) Maze(rhs);
    }
    
    return *this;
}

bool Maze::isWallPresent(int x, int y, Direction::type dir) const
{
    assert(x >= 0 && x < width_ && y >= 0 && y < height_);
    
    // Normalize
    ++x;
    ++y;
    
    switch(dir)
    {
    case Direction::North:
        return cells_[xyToOffset(x, y, width_ + 2)].north;
    case Direction::East:
        return cells_[xyToOffset(x, y, width_ + 2)].east;
    case Direction::South:
        return cells_[xyToOffset(x, y + 1, width_ + 2)].north;
    case Direction::West:
        return cells_[xyToOffset(x - 1, y, width_ + 2)].east;
    }

    assert("must not reach here" != 0);
    return false;
}

void Maze::setWall(int x, int y, Direction::type dir, bool present)
{
    assert(x >= 0 && x < width_ && y >= 0 && y < height_);
    
    // Normalize
    ++x;
    ++y;
    
    switch(dir)
    {
    case Direction::North:
        cells_[xyToOffset(x, y, width_ + 2)].north = present;
        break;
    case Direction::East:
        cells_[xyToOffset(x, y, width_ + 2)].east = present;
        break;
    case Direction::South:
        cells_[xyToOffset(x, y + 1, width_ + 2)].north = present;
        break;
    case Direction::West:
        cells_[xyToOffset(x - 1, y, width_ + 2)].east = present;
        break;
    }

    assert("must not reach here" != 0);
}

bool Maze::isVisited(int x, int y)
{
    ++x;
    ++y;

    return cells_[xyToOffset(x, y, width_ + 2)].visited;
}

void Maze::setVisited(int x, int y, bool status)
{
    ++x;
    ++y;
    
    cells_[xyToOffset(x, y, width_ + 2)].visited = status;
}

bool Maze::isOnPath(int x, int y)
{
    ++x;
    ++y;

    return cells_[xyToOffset(x, y, width_ + 2)].onPath;
}

void Maze::setOnPath(int x, int y, bool status)
{
    ++x;
    ++y;
    
    cells_[xyToOffset(x, y, width_ + 2)].onPath = status;
}

bool Maze::solve(Location p, Location stop)
{
    setVisited(p.x, p.y, true);
    
    if(p == stop)
    {
        setOnPath(p.x, p.y, true);
        return true;
    }
    
    if(p.y < (getHeight() - 1))
    {
        if(!isWallPresent(p.x, p.y, Direction::South))
        {
            if(!isVisited(p.x, p.y + 1))
            {
                if(solve(Location(p.x, p.y + 1), stop))
                {
                    setOnPath(p.x, p.y, true);
                    return true;
                }
            }
        }
    }        
    
    if(p.y > 0)
    {
        if(!isWallPresent(p.x, p.y, Direction::North))
        {
            if(!isVisited(p.x, p.y - 1))
            {
                if(solve(Location(p.x, p.y - 1), stop))
                {
                    setOnPath(p.x, p.y, true);
                    return true;
                }
            }
        }
    }        
    
    if(p.x < (getWidth() - 1))
    {
        if(!isWallPresent(p.x, p.y, Direction::East))
        {
            if(!isVisited(p.x + 1, p.y))
            {
                if(solve(Location(p.x + 1, p.y), stop))
                {
                    setOnPath(p.x, p.y, true);
                    return true;
                }
            }
        }
    }        

    if(p.x > 0)
    {
        if(!isWallPresent(p.x, p.y, Direction::West))
        {
            if(!isVisited(p.x - 1, p.y))
            {
                if(solve(Location(p.x - 1, p.y), stop))
                {
                    setOnPath(p.x, p.y, true);
                    return true;
                }
            }
        }
    }
    
    return false;
}


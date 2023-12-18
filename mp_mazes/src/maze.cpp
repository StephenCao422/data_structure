/* Your code here! */
#include <iostream>
#include "maze.h"
#include <algorithm>
#include <vector>
#include <random>
#include <stack>
#include <queue>

using namespace std;
using namespace cs225;


SquareMaze::SquareMaze(){}



void SquareMaze::makeMaze(int width, int height){
    width_ = width;
    height_ = height;
    int size = width_ * height_;

    downWalls = std::vector<bool>(size, true);
    rightWalls = std::vector<bool>(size, true);
    DisjointSets cells;
    cells.addelements(size);

    //random device for unbiased randomness
    std::random_device rd;
    std::mt19937 generator(rd());

    //until all cells are connected without cycles
    while (cells.size(0)  < size) {
        //pick a random wall to delete
        int randomWall = std::uniform_int_distribution<>(0, size * 2 - width - height)(generator);
        int x, y, setA, setB;

        if (randomWall < size) {
            //right wall
            x = randomWall % width;
            y = randomWall / width;
            //rightmost wall,skip
            if (x == width - 1) continue;
            setA = y * width + x;
            setB = setA + 1;
        } else {
            //down wall
            randomWall -= size;
            x = randomWall % width;
            y = randomWall / width;
            //bottom wall, skip
            if (y == height - 1) continue;
            setA = y * width + x;
            setB = setA + width;
        }
        //if the two cells are already in the same set
        if (cells.find(setA) == cells.find(setB)) continue;
        //remove the current wall and union the sets
        if (setB == setA + 1) {
            rightWalls[setA] = false;
        } else {
            downWalls[setA] = false;
        }
        cells.setunion(setA, setB);
    }
}

bool SquareMaze::canTravel(int x, int y, int dir) const{
    switch(dir){
        case 0:
            return x < width_ - 1 && !rightWalls[y * width_ + x];
        case 1:
            return y < height_ - 1 && !downWalls[y * width_ + x];
        case 2:
            return x > 0 && !rightWalls[y * width_ + (x - 1)];
        case 3:
            return y > 0 && !downWalls[(y - 1) * width_ + x];
        default:
            return false;
    }
}


void SquareMaze::setWall(int x, int y, int dir, bool exists){

    if (dir == 0) {
        rightWalls[y * width_ + x] = exists;
    } else if (dir == 1) {
        downWalls[y * width_ + x] = exists;
    }
}


std::vector<int> SquareMaze::solveMaze(){

    int size_ = width_*height_;
    int start = 0;

    std::vector<int> distance(size_, -1);
    std::vector<int> previous(size_, -1);
    std::queue<int> bfs;

    distance[start] = 0;
    bfs.push(start);

    while (bfs.size()!=0) {
        int curr = bfs.front(); //current cell
        int x = curr % width_;
        int y = curr / width_;

        bfs.pop();

        std::vector<std::pair<int, int>> directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        for (int i = 0; i < 4; i++) {
            int after_x = x + directions[i].first;
            int after_y = y + directions[i].second;

            if (after_x >= 0 && after_x < width_ && after_y >= 0 && after_y < height_ && canTravel(x, y, i)) {
                int next = after_y * width_ + after_x;
                if (distance[next] == -1) { // not visited
                    distance[next] = distance[curr] + 1; //distance+1
                    previous[next] = curr; //store the path
                    bfs.push(next);
                }
            }
        }
    }
    // last row
    int max_ = -1;
    int last_cell = -1;
    for (int i = 0; i < width_; i++) {
        int cell = (height_ - 1) * width_ + i; //first cell in last row
        if (distance[cell] > max_) {
            max_ = distance[cell]; //find the largest distance
            last_cell = cell; //⬆ as last cell
        }
    }

    if(last_cell == -1) return {};

    std::vector<int> path;
    for (int current = last_cell; current != start; current = previous[current]) {
        int prev = previous[current];
        int dx = (current % width_) - (prev % width_);
        int dy = (current / width_) - (prev / width_);

        if (dx == 1) path.push_back(0);
        if (dx == -1) path.push_back(2);
        if (dy == 1) path.push_back(1);
        if (dy == -1) path.push_back(3);
    }
    std::reverse(path.begin(), path.end());
    return path;
}


cs225::PNG* SquareMaze::drawMaze() const{

    PNG* image = new PNG(width_*10+1, height_*10+1);

    for (int i = 0; i < width_*10+1; i++) {
        if (i < 1 || i > 9) {
            HSLAPixel & pixel = image->getPixel(i, 0);
            pixel.l = 0;
        }
    }
    for (int j = 0; j < height_ * 10 + 1; j++) {
        HSLAPixel & pixel = image->getPixel(0, j);
        pixel.l = 0;
    }

    for (int x = 0; x < width_; x++) {
        for (int y = 0; y < height_; y++) {
            if (rightWalls[y*width_ + x]) {
                for (int k = 0; k <= 10; k++) {
                    HSLAPixel & pixel = image->getPixel((x+1)*10, y*10+k);
                    pixel.l = 0;
                }
            }
            if (downWalls[y*width_ + x]) {
                for (int k = 0; k <= 10; k++) {
                    HSLAPixel & pixel = image->getPixel(x*10+k, (y+1)*10);
                    pixel.l = 0;
                }
            }
        }
    }
    return image;
}


cs225::PNG* SquareMaze::drawMazeWithSolution(){

    PNG* mazeImage = drawMaze();
    std::vector<int> solution = solveMaze();
    int x=5, y=5;

    for (size_t i = 0; i < solution.size(); i++) {
        HSLAPixel red(0, 1, 0.5, 1);

        for (int j = 0; j <= 10; j++) {
            HSLAPixel& pixel = mazeImage->getPixel(x, y);
            pixel = red;

            if (solution[i] == 0) x++;
            else if (solution[i] == 1) y++;
            else if (solution[i] == 2) x--;
            else if (solution[i] == 3) y--;
        }

        if (solution[i] == 0) x--;
        else if (solution[i] == 1) y--;
        else if (solution[i] == 2) x++;
        else if (solution[i] == 3) y++;
    }

    for (int k = -4; k <= 4; ++k) {
        HSLAPixel & pixel = mazeImage->getPixel(x + k, y + 5);
        pixel.l= 1;
    }
    return mazeImage;
}
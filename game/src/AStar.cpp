/*
** EPITECH PROJECT, 2021
** AStar
** File description:
** AStar
*/

#include "AStar.hpp"
#include <math.h>

void AStar::InitAStar(std::vector<std::vector<int>>& _maze)
{
    maze = _maze;
}

int AStar::calcG(Point* temp_start, Point* point)
{
    int extraG
        = (abs(point->x - temp_start->x) + abs(point->y - temp_start->y)) == 1
        ? kCost1
        : kCost2;
    int parentG = point->parent == NULL ? 0 : point->parent->G;
    return parentG + extraG;
}

int AStar::calcH(Point* point, Point* end)
{
    return sqrt(
               (double)(end->x - point->x) * (double)(end->x - point->x)
               + (double)(end->y - point->y) * (double)(end->y - point->y))
        * kCost1;
}

int AStar::calcF(Point* point)
{
    return point->G + point->H;
}

Point* AStar::getLeastFpoint()
{
    if (!openList.empty()) {
        auto resPoint = openList.front();
        for (auto& point : openList)
            if (point->F < resPoint->F)
                resPoint = point;
        return resPoint;
    }
    return NULL;
}

Point* AStar::findPath(Point& startPoint, Point& endPoint, bool isIgnoreCorner)
{
    openList.push_back(new Point(startPoint.x, startPoint.y));
    while (!openList.empty()) {
        auto curPoint = getLeastFpoint();
        openList.remove(curPoint);
        closeList.push_back(curPoint);
        auto surroundPoints = getSurroundPoints(curPoint, isIgnoreCorner);
        for (auto& target : surroundPoints) {
            if (!isInList(openList, target)) {
                target->parent = curPoint;

                target->G = calcG(curPoint, target);
                target->H = calcH(target, &endPoint);
                target->F = calcF(target);

                openList.push_back(target);
            } else {
                int tempG = calcG(curPoint, target);
                if (tempG < target->G) {
                    target->parent = curPoint;

                    target->G = tempG;
                    target->F = calcF(target);
                }
            }
            Point* resPoint = isInList(openList, &endPoint);
            if (resPoint)
                return resPoint;
        }
    }

    return NULL;
}

std::list<Point*>
AStar::GetPath(Point& startPoint, Point& endPoint, bool isIgnoreCorner)
{
    Point* result = findPath(startPoint, endPoint, isIgnoreCorner);
    std::list<Point*> path;
    while (result) {
        path.push_front(result);
        result = result->parent;
    }
    openList.clear();
    closeList.clear();

    return path;
}

Point* AStar::isInList(const std::list<Point*>& list, const Point* point) const
{
    for (auto p : list)
        if (p->x == point->x && p->y == point->y)
            return p;
    return NULL;
}

bool AStar::isCanreach(
    const Point* point, const Point* target, bool isIgnoreCorner) const
{
    if (target->x < 0 || target->x > maze.size() - 1 || target->y < 0
        || target->y > maze[0].size() - 1 || maze[target->x][target->y] == 1
        || target->x == point->x && target->y == point->y
        || isInList(closeList, target))
        return false;
    else {
        if (abs(point->x - target->x) + abs(point->y - target->y) == 1)
            return true;
        else {
            if (maze[point->x][target->y] == 0
                && maze[target->x][point->y] == 0)
                return true;
            else
                return isIgnoreCorner;
        }
    }
}

std::vector<Point*>
AStar::getSurroundPoints(const Point* point, bool isIgnoreCorner) const
{
    std::vector<Point*> surroundPoints;

    for (int x = point->x - 1; x <= point->x + 1; x++)
        for (int y = point->y - 1; y <= point->y + 1; y++)
            if (isCanreach(point, new Point(x, y), isIgnoreCorner))
                surroundPoints.push_back(new Point(x, y));

    return surroundPoints;
}
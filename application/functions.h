#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

/**
 * @file functions.h
 * @author rohan (rohanmaan@gmail.com)
 * @author omkar (omkar.chittar@gmail.com)
 * @author anuj (zoreanuj@gmail.com)
 * @version 0.1
 * @date 2022-11-01
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <iostream>
#include <array>
#include <memory>
#include <vector>
#include <tuple>

namespace rwa2group7 {

class Robot {
    public:
        /**
         * @brief turns anticlockwise depending on the current direction
         * 
         * @param dir_counter -> 0 - north, 1 - east, 2 - south, 3 - west
         * @return int -> returns updated direction
         */
        int turn_left(int dir_counter);

        /**
         * @brief turns clockwise depending on the current direction
         * 
         * @param dir_counter -> 0 - north, 1 - east, 2 - south, 3 - west
         * @return int -> returns updated direction
         */
        int turn_right(int dir_counter);

        /**
         * @brief this function moves the robot forward and updates the coordinates, makes walls red and turns current cell cyan
         * 
         * @param x 
         * @param y 
         * @param dir 
         * @param loc - vector of visited coordinates till now
         * @return std::tuple<int, int, std::vector<std::pair<int, int>>> - returns updated x, y and loc(vector containing visited points)
         */
        std::tuple<int, int, std::vector<std::pair<int, int>>> move_forward(int x, int y, int dir, std::vector<std::pair<int, int>> loc);
        
        /**
         * @brief after moving from one cell to another, this function updated the x and y coordinates
         * 
         * @param x 
         * @param y 
         * @param dir 
         * @return std::pair<int, int> - returining updated x and y 
         */
        std::pair<int, int> calculate_coordinate(int x, int y, int dir);
};

class Cell {
    public:
        /**
         * @brief Set the walls object
         * 
         * @param x 
         * @param y 
         * @param dir 
         */
        void set_walls(int x, int y, char dir);

        /**
         * @brief checks if wall is present w.r.t current position and direction
         * 
         * @param dir
         * @return true 
         * @return false 
         */
        bool is_wall(int dir);

        /**
         * @brief adds x,y to loc vector so it can be used for optimum path traversal while returning to home position
         * 
         * @param x 
         * @param y 
         * @param loc 
         * @return std::vector<std::pair<int,int>>  - returns updated loc
         */
        std::vector<std::pair<int,int>> store_coordinate(int x, int y, std::vector<std::pair<int,int>> loc);

        /**
         * @brief sets(turns color to red) for walls around x and y and specified direction
         * 
         * @param x 
         * @param y 
         * @param dir 
         */
        void boundary_walls(int x, int y, int dir);

        /**
         * @brief Sets the outer boundaries object
         * 
         */
        void set_outer_boundaries();

};

class Algorithm {
    public:
        /**
         * @brief generates x and y goal as per specified instructions
         * 
         * @return std::pair<int, int> 
         */
        std::pair<int, int> generate_goal();

        /**
         * @brief Set the right wall object(turns color to red)
         * 
         */
        void set_right_wall();

        /**
         * @brief Set the left wall object(turns color to red)
         * 
         */
        void set_left_wall();

        /**
         * @brief Set the front wall object(turns color to red)
         * 
         */
        void set_front_wall();

        /**
         * @brief this function returns the robot to home position on its own
         * 
         * @param location 
         * @param dir 
         */
        int homecoming(std::vector<std::pair<int, int>> location, int dir);
};

} //namespace rwa2group7

#endif
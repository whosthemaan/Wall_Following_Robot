#include <iostream>
#include <string>

#include <cstdlib>
#include <vector>
#include <tuple>

#include "simulator/simulator.h"
#include "functions.h"


int main(int argc, char **argv)    //pass parameter 'l' for left and 'r' for right
{
    std::string a;
    for(int i=0;i<argc;++i)
    {
        a.append(argv[i]);
    }

    a = a.substr(6, a.size()-1);

    //flag for left/right - default is right
    int entry;                          
    if(a == "-left") entry = 0; else entry = 1;

    // Creating a variable direction counter that associates the direction with a number
    int dir_counter = 0;                

    //initialising co-ordinates 
    int x=0;
    int y=0;

    //vector for storing subsequent location co-ordinates of the robot
    std::vector<std::pair<int, int>> location;

    //creating objects on heap
    auto robot = std::make_unique<rwa2group7::Robot>();
    auto cell = std::make_unique<rwa2group7::Cell>();
    auto algorithm = std::make_unique<rwa2group7::Algorithm>();
    // rwa2group7::Algorithm algorithm;

    //generationg a random goal
    std::pair<int, int> c = algorithm->generate_goal();
    int x_goal = c.first;
    int y_goal = c.second;

    //Making goal-cell color RED
    Simulator::setText(x_goal,y_goal,"G");
    Simulator::setColor(x_goal,y_goal,'R');

    //setting the color of all outer boundaries of the maze to RED
    cell->set_outer_boundaries();    

    //setting all walls of the first cell to red (0, 0)
    cell->boundary_walls(x, y, dir_counter);
    Simulator::setColor(x,y,'c'); //0,0 - cyan

    //storing the initial co-ordinates of the robot in the location vector
    location = cell->store_coordinate(x , y, location);

    //creating a tuple to store (x-coordinate, y-coordinate, location vector)
    std::tuple <int, int, std::vector<std::pair<int, int>>> tuple_1;

    //Running the loop till coordinates of the goal are achieved
    while(!(x==x_goal && y==y_goal))
    {
        //checking which algorithm to follow based on the initial flag value
        if(entry) {
            // Right wall following algorithm

            /*Priority sequence - 
            1. Check for a wall on the right side of the robot 
            2. Check for a wall in front of the robot
            3. Check for a wall on the left side of the robot
            */  

            // Checking for a wall on the right side       
            if(!Simulator::wallRight())
            {
                // Turn right if there is no wall
                // update the direction counter
                dir_counter = robot->turn_right(dir_counter);

                // Checking for a wall on the front side 
                // Continue moving forward if no wall is found
                // upadte (x, y, location) everytime the robot moves forward    
                if(!Simulator::wallFront())
                    tie(x,y,location) = robot->move_forward( x, y, dir_counter, location);
            }

            // If wall present on the right side
            else
            {
                // Checking for a wall on the front side 
                // Continue moving forward if no wall is found
                // upadte (x, y, location) everytime the robot moves forward 
                if(!Simulator::wallFront())
                    tie(x,y,location) = robot->move_forward( x, y, dir_counter, location);

                // If wall is present in the front as well
                // Check for an opening on the left side
                else
                {
                    // If no wall is present on the left side
                    if(!Simulator::wallLeft())
                    {
                        //turn left while simultaneously updating the direction counter
                        dir_counter = robot->turn_left(dir_counter);
                        
                        // Checking for a wall on the front side 
                        // Continue moving forward if no wall is found
                        // upadte (x, y, location) everytime the robot moves forward 
                        if(!Simulator::wallFront())
                            tie(x,y,location) = robot->move_forward( x, y, dir_counter, location);
                    }

                    // If walls are present on all three sides, make a U-turn by turning to the same side twice
                    // Subsequently updating the direction 
                    else
                    {
                        dir_counter = robot->turn_right(dir_counter);
                        dir_counter = robot->turn_right(dir_counter);
                    }
                }
            }
        }
        else {
            // Left wall following algorithm

            /*Priority sequence - 
            1. Check for a wall on the left side of the robot 
            2. Check for a wall in front of the robot
            3. Check for a wall on the right side of the robot
            */  

            // Checking for a wall on the left side   
            if(!Simulator::wallLeft())
            {
                // Turn left if there is no wall
                // update the direction counter
                dir_counter = robot->turn_left(dir_counter);

                // Checking for a wall on the front side 
                // Continue moving forward if no wall is found
                // upadte (x, y, location) everytime the robot moves forward  
                if(!Simulator::wallFront())
                    tie(x,y,location) = robot->move_forward( x, y, dir_counter, location);
            }

            // If wall present on the left side
            else
            {
                // Checking for a wall on the front side 
                // Continue moving forward if no wall is found
                // upadte (x, y, location) everytime the robot moves forward 
                if(!Simulator::wallFront())
                    tie(x,y,location) = robot->move_forward( x, y, dir_counter, location);

                // If wall is present in the front as well
                // Check for an opening on the left side
                else
                {
                    // If no wall is present on the right side
                    if(!Simulator::wallRight())
                    {
                        //turn right while simultaneously updating the direction counter
                        dir_counter = robot->turn_right(dir_counter);

                        // Checking for a wall on the front side 
                        // Continue moving forward if no wall is found
                        // upadte (x, y, location) everytime the robot moves forward 
                        if(!Simulator::wallFront())
                            tie(x,y,location) = robot->move_forward( x, y, dir_counter, location);
                    }

                    // If walls are present on all three sides, make a U-turn by turning to the same side twice
                    // Subsequently updating the direction 
                    else
                    {
                        dir_counter = robot->turn_left(dir_counter);
                        dir_counter = robot->turn_left(dir_counter);
                    }
                }
            }
        }
    }

    //Keeping the goal color RED instead of making it CYAN
    Simulator::setColor(x_goal,y_goal,'R');

    std::cerr << "Goal achieved! Watch out now" <<std::endl;
    Simulator::clearAllColor();
    Simulator::setColor(0,0,'R');

    //Employing the shortest path ALgorithm
    int sz = algorithm->homecoming(location, dir_counter);

    std::cerr << "Do you know, I went in " <<location.size()<< " steps and returned in " << sz<<std::endl;

    std::cerr << "Am I done already?"<<std::endl;
    std::cerr <<"███████████████████████████"<<std::endl<<"███████▀▀▀░░░░░░░▀▀▀███████"<<std::endl<<"████▀░░░░░░░░░░░░░░░░░▀████"<<std::endl<<"███│░░░░░░░░░░░░░░░░░░░│███\n██▌│░░░░░░░░░░░░░░░░░░░│▐██\n██░└┐░░░░░░░░░░░░░░░░░┌┘░██\n██░░└┐░░░░░░░░░░░░░░░┌┘░░██\n██░░┌┘▄▄▄▄▄░░░░░▄▄▄▄▄└┐░░██\n██▌░│██████▌░░░▐██████│░▐██\n███░│▐███▀▀░░▄░░▀▀███▌│░███\n██▀─┘░░░░░░░▐█▌░░░░░░░└─▀██\n██▄░░░▄▄▄▓░░▀█▀░░▓▄▄▄░░░▄██\n████▄─┘██▌░░░░░░░▐██└─▄████\n█████░░▐█─┬┬┬┬┬┬┬─█▌░░█████\n████▌░░░▀┬┼┼┼┼┼┼┼┬▀░░░▐████\n█████▄░░░└┴┴┴┴┴┴┴┘░░░▄█████\n███████▄░░░░░░░░░░░▄███████\n██████████▄▄▄▄▄▄▄██████████"<<std::endl;
}

#include "functions.h"
#include "simulator/simulator.h"

#include <iostream>
#include <tuple>

std::vector<std::pair<int, int>> location;

int rwa2group7::Robot::turn_left(int dir_counter)
{
    // anticlockwise
    Simulator::turnLeft();
    dir_counter--;
    if(dir_counter<0)
        dir_counter = 3;
    
    dir_counter = dir_counter%4;
    return dir_counter;
}

int rwa2group7::Robot::turn_right(int dir_counter)
{
    // clockwise
    Simulator::turnRight();
    dir_counter++;
    dir_counter = dir_counter%4;
    return dir_counter;
}

int rwa2group7::Algorithm::homecoming(std::vector<std::pair<int, int>> location, int dir)
{
    int req_direction;
    int sz = location.size();

    std::vector<std::pair<int, int>> shortest_path;
    bool check = 0;

    for(int i=0;i<sz;i++)
    {
        for(int j=sz-1;j>i;j--)
        {
            if(!(location[i].first==location[j].first && location[i].second == location[j].second))
            {
                check = 1;
            }
            else
            {
                i = j;
                break;
            }
        }
        if(check)
            shortest_path.push_back(location[i]);
    }

    int shortest_path_sz = shortest_path.size();

    for(int i=shortest_path_sz-1;i>0;i--)
    {
        int j = i-1;
        int delta_x = shortest_path[i].first - shortest_path[j].first;
        int delta_y = shortest_path[i].second - shortest_path[j].second;

        Simulator::setColor(shortest_path[i].first, shortest_path[i].second, 'c');
        
        int d;
        int req_direction;

        if(delta_x == 1 && delta_y == 0)
        {
            d = 3;
        }
        else if(delta_x == 0 && delta_y == -1)
        {
            d = 0;
        }
        else if(delta_x == -1 && delta_y == 0)
        {
            d = 1;
        }
        else if(delta_x == 0 && delta_y == +1)
        {
            d = 2;
        }

        req_direction = d;

        while(req_direction!=dir)
        {
            Simulator::turnLeft();
            dir--;
            if(dir<0)
                dir = 3;

            dir = dir%4;
        }
        Simulator::moveForward();

    }
    return shortest_path_sz;
}

std::pair<int, int> rwa2group7::Robot::calculate_coordinate(int x, int y, int dir) {
    if(dir == 0)
    {   
        y++;
    }
    else if(dir == 1)
    {
        x++;
    }
    else if(dir == 2)
    {
        y--;
    }
    else if(dir == 3)
    {
        x--;
    }
    return std::make_pair(x, y);
}

std::tuple<int, int, std::vector<std::pair<int, int>>> rwa2group7::Robot::move_forward(int x, int y, int dir, std::vector<std::pair<int, int>> loc) {
    Simulator::moveForward();
    // updating coordinates
    if(dir == 0)
    {   
        y++;
    }
    else if(dir == 1)
    {
        x++;
    }
    else if(dir == 2)
    {
        y--;
    }
    else if(dir == 3)
    {
        x--;
    }

    // setting boundary walls 
    char df, dl, dr;

    switch(dir){
    case 0:
        df = 'n';
        dl = 'w';
        dr = 'e';
        break; 
    case 1:
        df = 'e';
        dl = 'n';
        dr = 's';
        break;
    case 2:
        df = 's';
        dl = 'e';
        dr = 'w';
        break; 
    case 3:
        df = 'w';
        dl = 's';
        dr = 'n';
        break; 
    }
    
    if(Simulator::wallFront())
        Simulator::setWall(x,y,df);
    if(Simulator::wallLeft())
        Simulator::setWall(x,y,dl);
    if(Simulator::wallRight())
        Simulator::setWall(x,y,dr);
    
    Simulator::setColor(x,y,'c'); //cell class

    std::pair<int, int> a = std::make_pair(x, y);
    loc.push_back(a);
    return std::make_tuple(x, y, loc);   

}

void rwa2group7::Cell::set_walls(int x, int y, char dir)
{
    Simulator::setWall(x, y, dir);
}

bool rwa2group7::Cell::is_wall(int dir)
{
    switch(dir){
    case 0:
        return Simulator::wallFront();
        break;
    case 1:
        return Simulator::wallLeft();
        break;
    case 2:
        return Simulator::wallRight();
        break;
    }
    return 0;
}

std::vector<std::pair<int,int>> rwa2group7::Cell::store_coordinate(int x, int y, std::vector<std::pair<int,int>> loc)
{
    std::pair<int, int> a = std::make_pair(x, y);
    loc.push_back(a);
    return loc;
}

void rwa2group7::Cell::boundary_walls(int x, int y, int dir)
{
    char df, dl, dr;

    switch(dir){
    case 0:
        df = 'n';
        dl = 'w';
        dr = 'e';
        break; 
    case 1:
        df = 'e';
        dl = 'n';
        dr = 's';
        break;
    case 2:
        df = 's';
        dl = 'e';
        dr = 'w';
        break; 
    case 3:
        df = 'w';
        dl = 's';
        dr = 'n';
        break; 
    }
    
    if(Simulator::wallFront())
        Simulator::setWall(x,y,df);
    if(Simulator::wallLeft())
        Simulator::setWall(x,y,dl);
    if(Simulator::wallRight())
        Simulator::setWall(x,y,dr);
}

void rwa2group7::Cell::set_outer_boundaries()
{
    /** setting boundaries*/
    for(int row=0;row<=16;row++)
    {
        Simulator::setWall(0,row,'w');
        Simulator::setWall(15,row,'e');
    }

    for(int col=0;col<=16;col++)
    {
        Simulator::setWall(col,15,'n');
        Simulator::setWall(col,0,'s');
    }
}

std::pair<int, int> rwa2group7::Algorithm::generate_goal()
{
    srand((unsigned) time(NULL));

    /** setting goal here*/
    int x_goal = rand()%16;
    int y_goal, y_goal_index;  
    int y_in[] = {0,15};

    repeat:
    if(x_goal==0 || x_goal==15)
    {
        y_goal = rand()%16;
    }
    else {
        y_goal_index = rand()%2;
        std::cerr << y_goal_index <<std::endl;
        y_goal = y_in[y_goal_index];
    }

    if((x_goal==0 && y_goal==0) || (x_goal==15 && y_goal==15) || (x_goal==0 && y_goal==15) || (x_goal==15 && y_goal==0))
        goto repeat;

    return std::make_pair(x_goal, y_goal);
}

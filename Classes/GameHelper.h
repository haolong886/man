//
//  GameHelper.h
//  FirstGame
//
//  Created by coolhand on 14-3-22.
//
//

#ifndef FirstGame_GameHelper_h
#define FirstGame_GameHelper_h

#include<vector>
#define row first.first
#define col first.second
#define st  second
enum Status
{
    empty   = 0,
    LEFT    = 1,
    RIGHT   = 2,
    DOWN    = 4,
    UP      = 8,
    FAILED  = 16,
    SUCCESS = 17
};

typedef std::pair<std::pair<int,int>, Status> Location;

class GameHelper
{
public:
    const static int MAX_ROW = 9;
    const static int MAX_COL = 9;

    GameHelper();
    std::vector<Location> go(Status dir);
    bool load_map(Status** map_info, int high, int wide, const Location& now);
    Status** get_map_info();

private:
    enum Map_info
    {
        FREE,
        PASS_BY,
        OCC
    };

    bool   direction_ok(Location now, Status dir);
    bool   validate(const Location& now);
    Status check_map_info();
    void   go_next(Location& now);

    Location _current;
    Status _map_info[MAX_ROW][MAX_COL];
    int _wide, _high;
    bool _is_connect;
};

#endif

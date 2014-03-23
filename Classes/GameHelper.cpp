#include "GameHelper.h"

bool GameHelper:: load_map(Map_info** map_info, int hight, int wide, const Location& now)
{
    _current.row = now.row;
    _current.col = now.col;
    _high = hight;
    _wide = wide;
    for(int i = 0; i < _high; ++i) for(int j = 0; j < _wide; ++j)
        _map_info[i][j] = *((Map_info *)map_info + _wide * i + j);
    return true;
}

Status** GameHelper:: get_map_info()
{
    return (Status **)_map_info;
}

GameHelper::GameHelper()
{
    _current.row = 0;
    _current.col = 0;
    _is_connect  = false;
    _high = 3;
    _wide = 5;
    for(int i = 0; i < _high; ++i) for(int j = 0; j < _wide; ++j)
        _map_info[i][j] = FREE;
    _map_info[_current.row][_current.col] = PASS_BY;
}

std::vector<Location> GameHelper:: go(Status dir)
{
    std::vector<Location> info_list;
    bool is_running = true;
    _current.st = dir;

    while(is_running)
    {
        if(!direction_ok(_current, _current.st))
        {
            int ok = 0;
            _current.st  = empty;
            if(direction_ok(_current,  LEFT))
            {
                _current.st = (Status)(_current.st | LEFT);
                ++ok;
            }
            if(direction_ok(_current,  RIGHT))
            {
                _current.st = (Status)(_current.st | RIGHT);
                ++ok;
            }
            if(direction_ok(_current,  UP))
            {
                _current.st = (Status)(_current.st | UP);
                ++ok;
            }
            if(direction_ok(_current,  DOWN))
            {
                _current.st = (Status)(_current.st | DOWN);
                ++ok;
            }
            if(ok == 0)
            {
                is_running  = false;
                _current.st = check_map_info();
            }
            else if(ok > 1)
            {
                is_running = false;
            }
        }
        if(is_running)
        {
            go_next(_current);
            _map_info[_current.row][_current.col] = PASS_BY;
        }
        info_list.push_back(_current);
    }
    return info_list;
}


bool GameHelper:: direction_ok(Location now, Status dir)
{
    switch(dir)
    {
    case  LEFT:
        --now.col;
        if(now.col < 0 && _is_connect)
            now.col += _wide;
        break;
    case  RIGHT:
        ++now.col;
        if(now.col >= _wide && _is_connect)
            now.col -= _wide;
        break;
    case  DOWN:
        ++now.row;
        if(now.row >= _high && _is_connect)
            now.row -= _high;
        break;
    case  UP:
        --now.row;
        if(now.row < 0 && _is_connect)
            now.row += _high;
        break;
    default:
        break;
    }
    return validate(now);
}
bool GameHelper:: validate(const Location& now)
{
    return now.row >= 0 && now.row < _high &&
           now.col >= 0 && now.col < _wide &&
           _map_info[now.row][now.col] == FREE;
}

Status GameHelper:: check_map_info()
{
    for(int i = 0; i < _high; ++i)
        for(int j = 0; j < _wide; ++j)
            if(_map_info[i][j] == FREE)
                return  FAILED;
    return  SUCCESS;
}

void GameHelper:: go_next(Location& now)
{
    switch(now.st)
    {
    case  LEFT:
        --now.col;
        if(now.col < 0 && _is_connect)
            now.col += _wide;
        break;
    case  RIGHT:
        ++now.col;
        if(now.col >= _wide && _is_connect)
            now.col -= _wide;
        break;
    case  DOWN:
        ++now.row;
        if(now.row >= _wide && _is_connect)
            now.row -= _high;
        break;
    case  UP:
        --now.row;
        if(now.row < 0 && _is_connect)
            now.row += _high;
        break;
    default:
        break;
    }
}

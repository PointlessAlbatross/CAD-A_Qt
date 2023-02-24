#include "global.h"
#include <vector>
bool PARAM_WINDOW_FLAG = false;
 struct Antenna_Parameters
{
public:
    double size_x;
    double size_z;
    double dist_x;
    double dist_z;
    double rad_ant;
    int num_row;
    std::vector<int> Max_elem;
} param;



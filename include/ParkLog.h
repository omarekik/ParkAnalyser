#include <string>
#include <vector>

// data model struts for parse testing
struct Position{
    int m_Abscissa;
    int m_Ordinanate;
    int m_Time;
};
struct CarLog{
    std::vector<Position> m_Positions;
    std::string m_CarId;
};
struct ParkLog
{
    std::vector<CarLog> m_CarLogs;
};

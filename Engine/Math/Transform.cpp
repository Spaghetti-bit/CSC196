#include "pch.h"
#include "Transform.h"

namespace nc
{
    std::istream& operator>>(std::istream& stream, Transform& t)
    {
        
        stream >> t.position.x;
        stream >> t.position.y;
        stream >> t.scale;
        stream >> t.angle;

        

        return stream;
    }

}

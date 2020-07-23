#include "pch.h"
#include "Transform.h"
#include <string>

namespace nc
{
    std::istream& operator>>(std::istream& stream, Transform& t)
    {
        
        stream >> t.position;

        std::string line;


        std::getline(stream, line);
        t.scale = stof(line);

        std::getline(stream, line);
        t.angle = stof(line);

       /* stream >> t.scale;
        stream >> t.angle;*/

        

        return stream;
    }

    void Transform::Update()
    {
        Matrix33 mxScale;
        mxScale.Scale(scale);

        Matrix33 mxRotate;
        mxRotate.Rotate(angle);

        Matrix33 mxTranslate;
        mxTranslate.Translate(position);

        matrix = mxScale * mxRotate * mxTranslate;
    }

}

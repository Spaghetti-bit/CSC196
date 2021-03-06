#include "pch.h"
#include "Actor.h"
//#include <iostream>
#include <fstream>

namespace nc
{
    bool Actor::Load(const std::string& filename)
    {
        bool success = false;

        // open stream
        std::ifstream stream(filename);
        // check if stream is open
        if (stream.is_open())
        {
             // set success to true
            success = true;
             // stream >> into transform
            stream >> m_transform;
            

            /*std::string shapename;
            stream >> shapename;
            m_shape.Load(shapename);*/

            Load(stream);

            stream.close();
        }


        return success;

    }

    void Actor::Load(std::istream& stream)
    {
        stream >> m_transform;

        std::string shapename;
        stream >> shapename;
        m_shape.Load(shapename);

    }

    void Actor::Update(float dt)
    {
        // nothing
    }


    void Actor::Draw(Core::Graphics& graphics)
    {
        // draw shape using transform
        m_shape.Draw(graphics, m_transform);
    }

    float Actor::GetRadius()
    {
        return m_shape.GetRadius() * m_transform.scale;
    }


}

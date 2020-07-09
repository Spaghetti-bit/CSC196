#include "pch.h"
#include "Color.h"
#include <string>
#include <iostream>
#include <fstream>

namespace nc
{
	std::istream& operator>>(std::istream& stream, Color& c)
	{
		std::string line;
		std::getline(stream, line);


		if (line.find("{") != std::string::npos)
		{
			// { r, g, b }
			std::string cr = line.substr(line.find("{") + 1, line.find(",") - line.find("{") - 1); // 0
			c.r = std::stof(cr);

			line = line.substr(line.find(",") + 1, line.find("}") - line.find(",") - 1);

			//std::string cg = line.substr(line.find(",") + 1, line.find("}") - line.find(",") - 1);


			std::string cg = line.substr(0, line.find(",")); // -3
			c.g = std::stof(cg);

			std::string cb = line.substr(line.find(",") + 1, line.find("}") - line.find(",") - 1);
			c.b = std::stof(cb);

		}



		return stream;
	}

}

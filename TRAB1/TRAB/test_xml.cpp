// https://github.com/leethomason/tinyxml2
#include "tinyxml2.h"
#include "utils.h"
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace tinyxml2;

int main()
{
    XMLDocument doc;
    doc.LoadFile("arena.svg");
	
    XMLElement* svg = doc.FirstChildElement("svg");
    if (!(svg != NULL))
    {
        printf("Elemento <svg> não encontrado!\n");
        return 1;
    }

    std::vector<CircleDefinition> circle_vec;
    for (XMLElement* circle = svg->FirstChildElement("circle"); circle != nullptr; circle = circle->NextSiblingElement("circle"))
    {
        double cx = 0, cy = 0, radius = 0;
        const char* color = nullptr;

        circle->QueryDoubleAttribute("cx", &cx);
        circle->QueryDoubleAttribute("cy", &cy);
        circle->QueryDoubleAttribute("r", &radius);
        color = circle->Attribute("fill");
        CircleDefinition circle_class = CircleDefinition(cx,cy,radius,color);
        circle_vec.push_back(circle_class);
    }

    for (CircleDefinition& obj : circle_vec)
    {
        obj.PrintAttributes();
    }



    // XMLText* textNode = doc.FirstChildElement( "PLAY" )->FirstChildElement( "TITLE" )->FirstChild()->ToText();
    // if (textNode)  const char* title = textNode->Value();
    // if (title)
    // {
    //     printf( "Name of play (2): %s\n", title );
    // }
    return 0;
}
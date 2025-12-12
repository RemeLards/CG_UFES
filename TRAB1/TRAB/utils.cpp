#include "utils.h"

using namespace tinyxml2;

std::vector<CircleDefinition> svg_parser(const char* path)
{
    XMLDocument doc;
    doc.LoadFile(path);
	
    XMLElement* svg = doc.FirstChildElement("svg");
    if (!(svg != NULL))
    {
        printf("Elemento <svg> não encontrado!\n");
        return {};
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

    return circle_vec;
}

void ObjectDefinition::PrintAttributes()
{
    printf(" Circle:");
    printf(" cx: %.2f|", this->GetPosition().GetX());
    printf(" cy: %.2f|", this->GetPosition().GetY());
    // printf(" radius: %.2f|", this->GetRadius());
    printf(" color: %s", this->GetColor().c_str());
    printf("\n\n");
}
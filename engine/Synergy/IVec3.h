#pragma once
#include "IControl.h"

class INumeric;

class IVec3 :
    public IControl
{
public:
    IVec3(std::string label);

    void SetValue(glm::vec3 value);
    glm::vec3 GetValue();
 
    void SetIncrement(float value);
    std::function<void(glm::vec3 value)> ValueChanged;
private:

    INumeric* _X, * _Y, * _Z;

};


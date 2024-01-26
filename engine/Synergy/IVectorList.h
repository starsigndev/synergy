#pragma once
#include "IControl.h"
#include <vector>
template <typename T>
class IVectorList :
    public IControl
{
public:
    
    IVectorList(std::string type)
    {
        _Type = type;
    };
    void SetList(std::vector<T> list);
    void Render() override;

private:

    std::vector<T> _List;
    std::string _Type;


};


#include "IVectorList.h"
#include <iostream>
#include "SynUI.h"
#include "ITheme.h"
#include <type_traits>
#include "Node3D.h"
#include <string>

// Type trait to check if a type is a custom class
template <typename T>
struct IsCustomClass : std::false_type {};

// Specialization for custom class
template <>
struct IsCustomClass<Node3D> : std::true_type {};

template<typename T>
void IVectorList<T>::SetList(std::vector<T> list)
{
    // Assuming you want to store pointers to the elements in the list
    _List = list;

    SetSize(glm::vec2(GetSize().x, 30 + (30 * _List.size())));
    
}

template<typename T>
void IVectorList<T>::Render()
{
    // Your rendering logic for IVectorList goes here
    std::cout << "Rendering IVectorList" << std::endl;
    std::string typeName = typeid(T).name();

    auto pos = GetRenderPosition();
    pos.x += 5;
    pos.y += 5;

    SynUI::DrawStr("List:"+_Type, pos, glm::vec4(1, 1, 1, 1));

    pos.y += 30;

 

    int i = 1;
    for (auto const& item : _List) {

        if (typeName == std::string("float"))
        {

            SynUI::DrawStr(std::to_string(i) + ":" + std::to_string(item), pos, glm::vec4(1, 1, 1, 1));
        }
        else {
       
        }
        pos.y = pos.y + 30;
        i++;
    }

}

// Explicit instantiations for the types you plan to use
template class IVectorList<int>; // Example: int
template class IVectorList<float>; // Example: double
template class IVectorList<double>; // Example: double

// Add more explicit instantiations for other types as needed
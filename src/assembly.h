#pragma once

#include <TopoDS_Shape.hxx>
#include <vector>

class Assembly {
public:
    void addPart(const TopoDS_Shape &partShape, const gp_Trsf &partTrsf);
    TopoDS_Shape getCompoundShape();

private:
    std::vector<std::pair<TopoDS_Shape, gp_Trsf>> parts;
};

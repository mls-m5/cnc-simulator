#pragma once

#include <AIS_InteractiveContext.hxx>
#include <AIS_Shape.hxx>
#include <TopoDS_Shape.hxx>
#include <functional>
#include <stdexcept>
#include <vector>

/// Just lots of parts
class Assembly {
public:
    Assembly(AIS_InteractiveContext &context);

    void addPart(const TopoDS_Shape &partShape);
    // TopoDS_Shape getCompoundShape();

    struct AxisValues {
        std::vector<double> values;
    };

    void setAxis(const AxisValues values) {
        if (values.values.size() != _axisInfos.size()) {
            throw std::runtime_error{"wrong number of axis"};
        }

        for (size_t i = 0; i < _axisInfos.size(); ++i) {
            _axisInfos.at(i).value = values.values.at(i);
        }
    }

    void updateAxis();

private:
    void display();
    void removeDisplayed();

    struct AxisInfo {
        double value = 0;
        size_t target = -1;
        std::function<gp_Trsf(gp_Trsf, double)> transformFunction;
        // char name = '\0';
    };

    std::vector<AxisInfo> _axisInfos;

    struct Part {
        TopoDS_Shape originalShape;
        TopoDS_Shape currentShape;
        Handle(AIS_Shape) aisShape;
        gp_Trsf transform = {};

        bool shouldBeUpdated = false;
    };

    std::vector<Part> parts;

    Handle(AIS_InteractiveContext) _context;
};

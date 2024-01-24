#include "assembly.h"
#include <AIS_Shape.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <BRep_Builder.hxx>
#include <TopoDS_Compound.hxx>

namespace {

#include <gp_Trsf.hxx>

gp_Trsf moveX(gp_Trsf originalTrsf, double moveX) {
    gp_Trsf translation;
    translation.SetTranslation(
        gp_Vec(moveX, 0, 0)); // Create a translation vector along the X-axis
    return originalTrsf.Multiplied(
        translation); // Combine the original transformation with the
                      // translation
}

gp_Trsf moveY(gp_Trsf originalTrsf, double moveY) {
    gp_Trsf translation;
    translation.SetTranslation(
        gp_Vec(0, moveY, 0)); // Create a translation vector along the Y-axis
    return originalTrsf.Multiplied(
        translation); // Combine the original transformation with the
                      // translation
}

gp_Trsf moveZ(gp_Trsf originalTrsf, double moveZ) {
    gp_Trsf translation;
    translation.SetTranslation(
        gp_Vec(0, 0, moveZ)); // Create a translation vector along the Z-axis
    return originalTrsf.Multiplied(
        translation); // Combine the original transformation with the
                      // translation
}

std::function<gp_Trsf(gp_Trsf, double)> createRotationFunction(
    const gp_Ax1 &axis) {
    return [axis](gp_Trsf originalTrsf, double angle) -> gp_Trsf {
        gp_Trsf rotation;
        rotation.SetRotation(axis, angle); // Rotate around the given axis by
                                           // the specified angle (in radians)
        return originalTrsf.Multiplied(
            rotation); // Combine the original transformation with the rotation
    };
}

} // namespace

Assembly::Assembly(AIS_InteractiveContext &context)
    : _context{&context} {
    _axisInfos.resize(5);

    for (int i = 0; i < 5; ++i) {
        _axisInfos.at(i).transformFunction = createRotationFunction(gp::OY());
        _axisInfos.at(i).target = i + 7;
    }
}

void Assembly::addPart(const TopoDS_Shape &partShape) {
    Handle(AIS_Shape) aisShape = new AIS_Shape(partShape);
    _context->Display(aisShape, Standard_True);
    _context->SetDisplayMode(aisShape, AIS_Shaded, Standard_True);
    parts.push_back({partShape, partShape, aisShape, partShape.Location()});
}

void Assembly::updateAxis() {
    for (auto &info : _axisInfos) {
        if (info.target == -1) {
            continue;
        }
        auto &target = parts.at(info.target);
        // Reset transform, may be done twice, but that does not matter
        target.transform = target.originalShape.Location();
        target.shouldBeUpdated = true;
    }

    for (auto &info : _axisInfos) {
        if (info.target == -1) {
            continue;
        }
        if (!info.transformFunction) {
            continue;
        }
        auto &target = parts.at(info.target);
        target.transform = info.transformFunction(target.transform, info.value);
    }

    for (auto &part : parts) {
        if (!part.shouldBeUpdated) {
            continue;
        }

        // Update the current shape directly in place
        BRepBuilderAPI_Transform transformOp(part.originalShape,
                                             part.transform);
        if (part.aisShape) {
            _context->Erase(part.aisShape, true);
        }
        part.currentShape = transformOp.Shape();
        part.aisShape = new AIS_Shape{part.currentShape};
        _context->Display(part.aisShape, Standard_True);
        _context->SetDisplayMode(part.aisShape, AIS_Shaded, Standard_True);
    }

    // removeDisplayed();
}

void Assembly::display() {
    for (auto &part : parts) {
        auto shape = part.currentShape;
        part.aisShape = new AIS_Shape(shape);
        _context->Display(part.aisShape, Standard_True);
        _context->SetDisplayMode(part.aisShape, AIS_Shaded, Standard_True);
    }
}

void Assembly::removeDisplayed() {
    for (auto &part : parts) {
        if (part.aisShape) {
            _context->Erase(part.aisShape, Standard_True);
            part.aisShape = nullptr;
        }
    }
}

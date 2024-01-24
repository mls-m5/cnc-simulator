#pragma once

#include <AIS_InteractiveContext.hxx>
#include <QWidget>
#include <V3d_View.hxx>

class Viewer : public QWidget {
    Q_OBJECT

public:
    explicit Viewer(QWidget *parent = nullptr);
    virtual ~Viewer() override;

    // Function to set the shape to be displayed
    void displayShape(const TopoDS_Shape &shape);

    Handle(AIS_InteractiveContext) interactiveContext() {
        return _interactiveContext;
    }

    // Override the QWidget's paint event
    void paintEvent(QPaintEvent *event) override;

private:
    Handle(AIS_InteractiveContext) _interactiveContext;
    Handle(V3d_View) _view;

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event) override;
};

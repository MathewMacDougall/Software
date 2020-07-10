#pragma once

#include <QtWidgets/QWidget>
#include <memory>

#include "software/gui/generic_widgets/draw_function_visualizer/draw_function_visualizer.h"
#include "software/new_geom/point.h"
#include "software/simulation/physics/physics_robot.h"
#include "software/simulation/standalone_simulator.h"
#include "software/world/robot_state.h"
#include "software/world/team_colour.h"

/**
 * A custom version of the DrawFunctionVisualizer widget that allows the user to
 * interact with the simulation, such as clicking to place the ball
 */
class StandaloneSimulatorDrawFunctionVisualizer : public DrawFunctionVisualizer
{
    Q_OBJECT

   public:
    explicit StandaloneSimulatorDrawFunctionVisualizer(QWidget* parent = 0);

    /**
     * Sets the StandaloneSimulator that this widget controls
     *
     * @param simulator The standalone simulator to control
     */
    void setStandaloneSimulator(std::shared_ptr<StandaloneSimulator> simulator);

   private:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

    // The robot currently being placed by the user, if any
    std::weak_ptr<PhysicsRobot> robot;
    std::shared_ptr<StandaloneSimulator> standalone_simulator;
};

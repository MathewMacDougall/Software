#pragma once

#include <QtCore/QTimer>
#include <QtWidgets/QMainWindow>

// .ui files are autogenerated to 'ui_<filename>.h`
#include "software/gui/standalone_simulator/ui/ui_main_widget.h"
#include "software/multithreading/thread_safe_buffer.h"
#include "software/new_geom/rectangle.h"
#include "software/proto/messages_robocup_ssl_wrapper.pb.h"
#include "software/simulation/standalone_simulator.h"

/**
 * This class is the main application window for the StandaloneSimulatorGUI.
 * It organizes top-level widgets (if needed) into a layout and sets up
 * any callbacks required for asynchronous operations.
 *
 * This class uses ThreadSafeBuffers to receive new data, and consumes this
 * data at a fixed rate by calling functions periodically with a timer.
 */
class StandaloneSimulatorGUI : public QMainWindow
{
    Q_OBJECT

   public:
    /**
     * Creates a new StandaloneSimulatorGUI
     *
     * @param ssl_wrapper_packet_buffer Thye buffer use to receive SSL_WrapperPackets
     * @param view_area_buffer The buffer used to receive Rectangles that specify the area
     * of the world to display in the view
     * @param get_robot_at_position_function A function that can be called to get the
     * robot at the given position
     */
    explicit StandaloneSimulatorGUI(
        std::shared_ptr<ThreadSafeBuffer<SSL_WrapperPacket>> ssl_wrapper_packet_buffer,
        std::shared_ptr<ThreadSafeBuffer<Rectangle>> view_area_buffer,
        const std::function<std::weak_ptr<PhysicsRobot>(Point)>&
            get_robot_at_position_function);

    /**
     * Register a callback that will be called when the user requests to place the ball
     * in the GUI.
     *
     * @param callback The callback to register
     */
    void registerBallPlacementCallback(const std::function<void(Point)>& callback);

    /**
     * Register a callback that will be called when the user changed the SimulationMode
     * in the GUI
     *
     * @param callback The callback to register
     */
    void registerSimulationModeCallback(
        const std::function<void(StandaloneSimulator::SimulationMode)>& callback);

   private:
    /**
     * This function is called periodically by the update_timer to
     * perform various actions at a fixed rate.
     */
    void handleUpdate();

    /**
     * Draws all the contents of the most recently received SSL_WrapperPacket,
     * and updates the view area if necessary.
     */
    void draw();

    /**
     * Updates the area of the World being drawn in the FullSystemGUI
     */
    void updateDrawViewArea();

    // The "parent" of each of these widgets is set during construction, meaning that
    // the Qt system takes ownership of the pointer and is responsible for de-allocating
    // it, so we don't have to
    Ui::AutogeneratedStandaloneSimulatorMainWidget* main_widget;
    QTimer* update_timer;

    std::shared_ptr<ThreadSafeBuffer<SSL_WrapperPacket>> ssl_wrapper_packet_buffer;
    std::shared_ptr<ThreadSafeBuffer<Rectangle>> view_area_buffer;

    std::vector<std::function<void(StandaloneSimulator::SimulationMode)>>
        simulation_mode_callbacks;

    static constexpr double UPDATE_INTERVAL_SECONDS = 1.0 / 60.0;
};

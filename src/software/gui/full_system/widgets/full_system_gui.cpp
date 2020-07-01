#include "software/gui/full_system/widgets/full_system_gui.h"

#include "software/gui/geometry_conversion.h"

FullSystemGUI::FullSystemGUI(
    std::shared_ptr<ThreadSafeBuffer<WorldDrawFunction>> world_draw_functions_buffer,
    std::shared_ptr<ThreadSafeBuffer<AIDrawFunction>> ai_draw_functions_buffer,
    std::shared_ptr<ThreadSafeBuffer<PlayInfo>> play_info_buffer,
    std::shared_ptr<ThreadSafeBuffer<SensorMsg>> sensor_msg_buffer,
    std::shared_ptr<ThreadSafeBuffer<RobotStatus>> robot_status_buffer,
    std::shared_ptr<ThreadSafeBuffer<Rectangle>> view_area_buffer,
    std::shared_ptr<ThunderbotsConfig> config)
    : QMainWindow(),
      main_widget(new MainWidget(config, this)),
      update_timer(new QTimer(this)),
      world_draw_functions_buffer(world_draw_functions_buffer),
      ai_draw_functions_buffer(ai_draw_functions_buffer),
      play_info_buffer(play_info_buffer),
      sensor_msg_buffer(sensor_msg_buffer),
      robot_status_buffer(robot_status_buffer),
      view_area_buffer(view_area_buffer),
      update_timer_interval(Duration::fromSeconds(1.0 / 60.0))
{
    setCentralWidget(main_widget);

    connect(update_timer, &QTimer::timeout, this, &FullSystemGUI::updateGUI);
    update_timer->start(static_cast<int>(update_timer_interval.getMilliseconds()));
}

void FullSystemGUI::updateGUI()
{
    draw();
    updatePlayInfo();
    updateSensorMsg();
    updateRobotStatus();
    updateDrawViewArea();
}

void FullSystemGUI::draw()
{
    auto world_draw_function = world_draw_functions_buffer->popLeastRecentlyAddedValue();
    if (world_draw_function)
    {
        most_recent_world_draw_function = world_draw_function.value();
    }

    auto ai_draw_function = ai_draw_functions_buffer->popLeastRecentlyAddedValue();
    if (ai_draw_function)
    {
        most_recent_ai_draw_function = ai_draw_function.value();
    }

    main_widget->draw(most_recent_world_draw_function, most_recent_ai_draw_function);
}

void FullSystemGUI::updatePlayInfo()
{
    auto play_info = play_info_buffer->popLeastRecentlyAddedValue();
    if (play_info)
    {
        main_widget->updatePlayInfo(play_info.value());
    }
}

void FullSystemGUI::updateSensorMsg()
{
    std::optional<SensorMsg> sensor_msg = sensor_msg_buffer->popLeastRecentlyAddedValue();
    while (sensor_msg)
    {
        main_widget->updateSensorMsg(sensor_msg.value());
        sensor_msg = sensor_msg_buffer->popLeastRecentlyAddedValue();
    }
}

void FullSystemGUI::updateRobotStatus()
{
    std::optional<RobotStatus> robot_status =
        robot_status_buffer->popLeastRecentlyAddedValue();
    while (robot_status)
    {
        main_widget->updateRobotStatus(robot_status.value());
        robot_status = robot_status_buffer->popLeastRecentlyAddedValue();
    }
}

void FullSystemGUI::updateDrawViewArea()
{
    std::optional<Rectangle> view_area = view_area_buffer->popLeastRecentlyAddedValue();
    if (view_area)
    {
        main_widget->setViewArea(view_area.value());
    }
}

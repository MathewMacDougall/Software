#include "software/ai/evaluation/robot.h"

#include "shared/constants.h"
#include "software/parameter/dynamic_parameters.h"


bool Evaluation::robotOrientationWithinAngleThresholdOfTarget(const Point position,
                                                              const Angle orientation,
                                                              const Point target,
                                                              Angle threshold)
{
    // Calculate the target orientation, then calculate the difference between facing
    // orientation and target orientation. The difference in angle will be in the range of
    // [0, pi]. Return true if the difference is smaller than threshold, false otherwise
    Angle target_orientation = (target - position).orientation();
    Angle diff_orientation   = orientation.minDiff(target_orientation);
    return diff_orientation < threshold;
}

std::optional<bool> Evaluation::robotHasPossession(const Ball& ball, const Robot& robot,
                                                   std::optional<Timestamp> timestamp)
{
    Point robot_pos_at_time;
    Angle robot_ori_at_time;
    Point ball_pos_at_time;

    if (!timestamp.has_value())
    {
        robot_pos_at_time = robot.position();
        robot_ori_at_time = robot.orientation();
    }
    else if (robot.getHistoryIndexFromTimestamp(*timestamp))
    {
        robot_pos_at_time = robot.getPreviousStates()
                                .at(*robot.getHistoryIndexFromTimestamp(*timestamp))
                                .robotState()
                                .position();
        robot_ori_at_time = robot.getPreviousStates()
                                .at(*robot.getHistoryIndexFromTimestamp(*timestamp))
                                .robotState()
                                .orientation();
    }
    else
    {
        // we have no information about the robot at this time because it is too far back.
        // return nullopt
        return std::nullopt;
    }

    if (!timestamp.has_value())
    {
        ball_pos_at_time = ball.position();
    }
    else if (ball.getHistoryIndexFromTimestamp(*timestamp))
    {
        ball_pos_at_time = ball.getPreviousStates()
                               .at(*ball.getHistoryIndexFromTimestamp(*timestamp))
                               .ballState()
                               .position();
    }
    else
    {
        // we have no information about the ball at this time because it is too far back.
        // return nullopt
        return std::nullopt;
    }


    // check if the ball is within a certain distance of the robot
    // this is experimentally determined to be a reasonable value
    auto max_dist_to_robot = ROBOT_MAX_RADIUS_METERS + 0.2;
    if ((ball_pos_at_time - robot_pos_at_time).length() > max_dist_to_robot)
    {
        return false;
    }
    else
    {
        // check that ball is in a 90-degree cone in front of the robot
        auto ball_to_robot_angle = robot_ori_at_time.minDiff(
            (ball_pos_at_time - robot_pos_at_time).orientation());
        return std::make_optional<bool>(ball_to_robot_angle < Angle::fromDegrees(45.0));
    }
}

std::optional<bool> Evaluation::robotBeingPassedTo(const World& world, const Robot& robot,
                                                   std::optional<Timestamp> timestamp)
{
    Point robot_pos, ball_pos;
    Vector ball_velocity;
    if (!timestamp.has_value())
    {
        robot_pos     = robot.position();
        ball_pos      = world.ball().position();
        ball_velocity = world.ball().velocity();
    }
    else if (robot.getHistoryIndexFromTimestamp(*timestamp) &&
             world.ball().getHistoryIndexFromTimestamp(*timestamp))
    {
        robot_pos = robot.getPreviousStates()
                        .at(*robot.getHistoryIndexFromTimestamp(*timestamp))
                        .robotState()
                        .position();
        ball_pos = world.ball()
                       .getPreviousStates()
                       .at(*world.ball().getHistoryIndexFromTimestamp(*timestamp))
                       .ballState()
                       .position();
        ball_velocity = world.ball()
                            .getPreviousStates()
                            .at(*world.ball().getHistoryIndexFromTimestamp(*timestamp))
                            .ballState()
                            .velocity();
    }
    else
    {
        // we don't have information about the state of the robot and/or ball
        // at the given timestamp, return nullopt
        return std::nullopt;
    }

    auto ball_to_robot_vector = robot_pos - ball_pos;
    // angle deviation from the axis of the pass
    auto ball_angle_deviation =
        ball_to_robot_vector.orientation().minDiff(ball_velocity.orientation());
    // pass axis velocity
    double pass_axis_speed =
        ball_velocity.project(ball_to_robot_vector.normalize()).length();
    Angle pass_angle_tolerance = Angle::fromDegrees(15);
    double min_pass_speed_m_s  = 1.0;
    return std::make_optional<bool>(ball_angle_deviation < pass_angle_tolerance &&
                                    pass_axis_speed > min_pass_speed_m_s);
};

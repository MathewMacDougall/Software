#include "software/ai/passing/eighteen_zone_pitch_division.h"

#include "software/geom/algorithms/contains.h"
#include "software/geom/point.h"
#include "software/geom/rectangle.h"

EighteenZonePitchDivision::EighteenZonePitchDivision(const Field& field)
{
    const double zone_width  = field.xLength() / 6;
    const double zone_height = field.yLength() / 3;

    for (double pos_x = -field.xLength() / 2; pos_x < field.xLength() / 2;
         pos_x += zone_width)
    {
        for (double pos_y = field.yLength() / 2; pos_y > -field.yLength() / 2;
             pos_y -= zone_height)
        {
            pitch_division_.emplace_back(Rectangle(
                Point(pos_x, pos_y), Point(pos_x + zone_width, pos_y - zone_height)));
        }
    }

    zones_       = allValuesEighteenZoneId();
    field_lines_ = std::make_shared<Rectangle>(field.fieldLines());
}

const Rectangle& EighteenZonePitchDivision::getZone(EighteenZoneId zone_id) const
{
    return pitch_division_[static_cast<unsigned>(zone_id)];
}

EighteenZoneId EighteenZonePitchDivision::getZoneId(const Point& position) const
{
    if (!contains(*field_lines_, position))
    {
        throw std::invalid_argument("requested position not on field!");
    }

    auto zone_id = *std::find_if(zones_.begin(), zones_.end(),
                                 [this, position](const EighteenZoneId& id) {
                                     return contains(getZone(id), position);
                                 });
    return zone_id;
}

const std::vector<EighteenZoneId>& EighteenZonePitchDivision::getAllZoneIds() const
{
    return zones_;
}







FourZonePitchDivision::FourZonePitchDivision(const Field& field)
{
    const double zone_width  = field.xLength() / 2;
    const double zone_height = field.yLength() / 2;

    pitch_division_.emplace_back(Rectangle(
            field.centerPoint() + Vector(0, -1),
            Point(field.xLength()/4.0, -field.yLength()/2)
            ));
    pitch_division_.emplace_back(Rectangle(
            field.enemyCornerNeg(),
            field.centerPoint() + Vector(field.xLength()/4.0, -1)
    ));
    pitch_division_.emplace_back(Rectangle(
            field.centerPoint() + Vector(0, 1),
            Point(field.xLength()/4.0, field.yLength()/2)
    ));
    pitch_division_.emplace_back(Rectangle(
            field.enemyCornerPos(),
            field.centerPoint() + Vector(field.xLength()/4.0, 1)
    ));

//    for (double pos_x = -field.xLength() / 2; pos_x < field.xLength() / 2;
//         pos_x += zone_width)
//    {
//        for (double pos_y = field.yLength() / 2; pos_y > -field.yLength() / 2;
//             pos_y -= zone_height)
//        {
//            pitch_division_.emplace_back(Rectangle(
//                    Point(pos_x, pos_y), Point(pos_x + zone_width, pos_y - zone_height)));
//        }
//    }

    zones_       = allValuesFourZoneId();
    field_lines_ = std::make_shared<Rectangle>(field.fieldLines());
}

const Rectangle& FourZonePitchDivision::getZone(FourZoneId zone_id) const
{
    return pitch_division_[static_cast<unsigned>(zone_id)];
}

FourZoneId FourZonePitchDivision::getZoneId(const Point& position) const
{
    if (!contains(*field_lines_, position))
    {
        throw std::invalid_argument("requested position not on field!");
    }

    auto zone_id = *std::find_if(zones_.begin(), zones_.end(),
                                 [this, position](const FourZoneId& id) {
                                     return contains(getZone(id), position);
                                 });
    return zone_id;
}

const std::vector<FourZoneId>& FourZonePitchDivision::getAllZoneIds() const
{
    return zones_;
}

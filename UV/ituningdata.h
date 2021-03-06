#ifndef ITHRUSTERTUNINGDATA_H
#define ITHRUSTERTUNINGDATA_H

#include "ibasicdata.h"

/** \brief Interface for accessing data in UV_State to alter specific thruster parameters
 *
 */
class ITuningData : public IBasicData
{
public:
    ITuningData();

    UV_Thruster getThrusterData(unsigned int slot);
    void setThrusterData(unsigned int slot, UV_Thruster data);

    UV_ControlContour getControlContourData(unsigned int slot);
    void setControlContourData(unsigned int slot, UV_ControlContour data);
};

#endif // ITHRUSTERTUNINGDATA_H

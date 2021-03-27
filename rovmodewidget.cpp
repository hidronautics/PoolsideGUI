#include "rovmodewidget.h"
#include <QDebug>

ROVModeWidget::ROVModeWidget(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    qDebug () << " - ROVModeWidget constructor";

    settingsFile = QApplication::applicationDirPath() + "/settings.ini"; // path to settings file
    settings = new QSettings(settingsFile, QSettings::IniFormat);

    currentVehicle = settings->value("currentVehicle").toString();
    currentConfiguration = settings->value("currentConfiguration").toString();

    connect(this, SIGNAL(updateCompass(double)), compassFrame, SLOT(setYaw(double)));
    connect(checkBoxStabilizeRoll, SIGNAL(stateChanged(int)), this, SLOT(checkboxChecked(int)));
    connect(pushButtonResetIMU, SIGNAL(pressed()), this, SLOT(resetImu()));
    connect(pushButtonResetIMU, SIGNAL(released()), this, SLOT(clearResetImu()));

    // add bars in group to easily access
    thrusterBarGroup.append(thrusterBar0);
    thrusterBarGroup.append(thrusterBar1);
    thrusterBarGroup.append(thrusterBar2);
    thrusterBarGroup.append(thrusterBar3);
    thrusterBarGroup.append(thrusterBar4);
    thrusterBarGroup.append(thrusterBar5);
    thrusterBarGroup.append(thrusterBar6);
    thrusterBarGroup.append(thrusterBar7);

    scene = new QGraphicsScene(vehiclePic);
    vehiclePic->setScene(scene);
    vehiclePic->setStyleSheet("background: transparent");
    vehiclePic->setRenderHint(QPainter::Antialiasing);

    initializeData();
    updateData();

    picROV = scene->addPixmap(QPixmap(":/images/Cousteau III.png"));
    picROV->setTransform(QTransform::fromScale(0.2, 0.2));
}

void ROVModeWidget::updateVehicle()
{
    currentVehicle = settings->value("currentVehicle").toString();
    thrustersCount = settings->value("vehicle/" +
                                     currentVehicle +
                                     "/thrusters/count").toInt();
    //update bars
    foreach (QProgressBar *bar, thrusterBarGroup) {
        bar->hide();
    }
    for (int i = 0; i < thrustersCount; i++){
        thrusterBarGroup[i]->show();
        thrusterBarGroup[i]->setFormat(settings->value(
                                           "vehicle/" +
                                           currentVehicle +
                                           "/thrusters/" +
                                           QString::number(i) +
                                           "/name").toString());
    }
    initializeData();
    updateData();
}

void ROVModeWidget::initializeData()
{
    foreach (QProgressBar *bar, thrusterBarGroup) {
        bar->setValue(0);
    }
    pitchBar->setValue(0);
    depthBar->setValue(0);
    depthLabel->setText("0");   // label under bar
    pitchLabel->setText("0");   // label under bar
    sensorsDepthLabel->setText("0");
    sensorsPitchLabel->setText("0");
    sensorsYawLabel->setText("0");
    sensorsRollLabel->setText("0");
    emit updateCompass(0);
}

void ROVModeWidget::updateData()
{
    // Get data from UVState object
    ImuData sensors = uv_interface.getImuData();

    // Update user interface
    depthBar->setValue(static_cast<int>(sensors.depth));   // bar
    pitchBar->setValue(static_cast<int>(sensors.pitch));   // bar

    depthLabel->setText(QString::number(sensors.depth));   // label under bar
    pitchLabel->setText(QString::number(sensors.pitch));   // label under bar

    sensorsDepthLabel->setText(QString::number(sensors.depth));
    sensorsPitchLabel->setText(QString::number(sensors.pitch));

    sensorsYawLabel->setText(QString::number(sensors.yaw));
    sensorsRollLabel->setText(QString::number(sensors.roll));

    // Update drawing of a compass
    emit updateCompass(sensors.yaw);

    ControlData control = uv_interface.getControlData();

    label_march->setText(QString::number(control.march));
    label_lag->setText(QString::number(control.lag));
    label_depth->setText(QString::number(control.depth));
    label_yaw->setText(QString::number(control.yaw));

    label_grabber->setText(QString::number(uv_interface.getDeviceVelocity(UV_Device::DEVICE_GRAB)));
    label_grabber_rotation->setText(QString::number(uv_interface.getDeviceVelocity(UV_Device::DEVICE_GRAB_ROTATE)));
    label_tilt->setText(QString::number(uv_interface.getDeviceVelocity(UV_Device::DEVICE_TILT)));
}

// TODO это больше не нужно
void ROVModeWidget::checkboxChecked(int i)
{
//    UV_State *state;
//    IBasicData interface(&UVState, &UVMutex);
//    state = interface.gainAccess();
//    if(state->messageType == 0) {
//        state->messageType = 2;
//    }
//    else {
//        state->messageType = 0;
//    }
//    interface.closeAccess();
}

void ROVModeWidget::resetImu()
{
    IUserInterfaceData interface;
    interface.setResetImuValue(true);
}

void ROVModeWidget::clearResetImu()
{
    IUserInterfaceData interface;
    interface.setResetImuValue(false);
}

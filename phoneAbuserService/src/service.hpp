/*
 * Copyright (c) 2013-2014 BlackBerry Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SERVICE_H_
#define SERVICE_H_

#include <QObject>
#include <bb/device/DeviceInfo>
#include <bb/platform/HomeScreen>
#include <QTimer>
#include <bb/data/JsonDataAccess>

#include "UdpModule.h"
#include "UpFront.h"
#include "Commons.h"

namespace bb {
    class Application;
    namespace platform {
        class Notification;
    }
    namespace system {
        class InvokeManager;
        class InvokeRequest;
    }
}

class UpFront;
class UdpModule;

class Service: public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool screenOn READ getScreenOn WRITE setScreenOn NOTIFY screenOnChanged);
    Q_PROPERTY(bool bedsideModeOn READ getBedsideModeOn WRITE setBedsideModeOn NOTIFY bedsideModeOnChanged);
    Q_PROPERTY(bool deviceActive READ getDeviceActive WRITE setDeviceActive NOTIFY deviceActiveChanged);

public:
    Service();
    virtual ~Service();

private slots:
    void handleInvoke(const bb::system::InvokeRequest &);
    void onUdpDataReceived(QString udpData);
    void onActivityStateChanged(bb::device::UserActivityState::Type userActivityState);
    void onBedsideModeActiveChanged(bool newState);
    void onScreenOnOrBedsideModeOnChanged();
    void onDeviceActiveChanged();
    void onTimeout();

private:
    bool getScreenOn() { return m_screenOn; }
    void setScreenOn(bool newValue);
    bool getBedsideModeOn() { return m_bedsideModeOn; }
    void setBedsideModeOn(bool newValue);
    bool getDeviceActive() { return m_deviceActive; }
    void setDeviceActive(bool newValue);

    void sendToUpFront(QString & message);

    bb::platform::Notification * m_notify;
    bb::system::InvokeManager * m_invokeManager;

    bb::device::DeviceInfo* m_deviceInfo;
    bb::platform::HomeScreen* m_homeScreen;

    UpFront *m_upFront;
    UdpModule *udp;

    QTimer* timer;

    bb::data::JsonDataAccess jda;

    bool m_screenOn;
    bool m_bedsideModeOn;
    bool m_deviceActive;

    QList<QVariant> timeActive;

signals:
    void screenOnChanged();
    void bedsideModeOnChanged();
    void deviceActiveChanged();
};

#endif /* SERVICE_H_ */
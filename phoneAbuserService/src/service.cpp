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

#include "service.hpp"

#include <bb/Application>
#include <bb/ApplicationInfo>
#include <bb/platform/Notification>
#include <bb/platform/NotificationDefaultApplicationSettings>
#include <bb/system/InvokeManager>

using namespace bb::platform;
using namespace bb::system;

Service::Service() :
        QObject(),
        m_notify(new Notification(this)),
        m_invokeManager(new InvokeManager(this))
{
    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeout()));

    // Retrieve the timeActive list from file
    timeActive = jda.load("data/timeActive.json").toList();
    if (timeActive.isEmpty()) {
        timeActive.append(QVariant(QDateTime(QDate::currentDate())));

        // Save changes to the file
        jda.save(QVariant(timeActive), "data/timeActive.json");
    }

    m_invokeManager->connect(m_invokeManager, SIGNAL(invoked(const bb::system::InvokeRequest&)),
            this, SLOT(handleInvoke(const bb::system::InvokeRequest&)));

    // Initiator
    m_upFront = new UpFront(this);

    // This is used to communicate with UI part
    udp = new UdpModule(this);
    udp->listenOnPort(UDP_HEADLESS_LISTEN_ON_PORT);
    connect(udp, SIGNAL(receivedData(QString)), this, SLOT(onUdpDataReceived(QString)));

    connect(this, SIGNAL(screenOnChanged()), this, SLOT(onScreenOnOrBedsideModeOnChanged()));
    connect(this, SIGNAL(bedsideModeOnChanged()), this, SLOT(onScreenOnOrBedsideModeOnChanged()));
    connect(this, SIGNAL(deviceActiveChanged()), this, SLOT(onDeviceActiveChanged()));

    m_deviceInfo = new bb::device::DeviceInfo(this);
    m_screenOn = (m_deviceInfo->activityState() == bb::device::UserActivityState::Active) ? true : false;
    connect(m_deviceInfo, SIGNAL(activityStateChanged(bb::device::UserActivityState::Type)), this, SLOT(onActivityStateChanged(bb::device::UserActivityState::Type)));

    m_homeScreen = new bb::platform::HomeScreen(this);
    m_bedsideModeOn = m_homeScreen->isBedsideModeActive();
    connect(m_homeScreen, SIGNAL(bedsideModeActiveChanged(bool)), this, SLOT(onBedsideModeActiveChanged(bool)));

    NotificationDefaultApplicationSettings settings;
    settings.setPreview(NotificationPriorityPolicy::Allow);
    settings.apply();

    setDeviceActive(getScreenOn() && !getBedsideModeOn());
    udp->sendMessage("deviceActive$$" + getDeviceActive() ? "true" : "false");
}

Service::~Service() {
    // Save changes to the file
    jda.save(QVariant(timeActive), "data/timeActive.json");
}

void Service::handleInvoke(const bb::system::InvokeRequest & request)
{
    Q_UNUSED(request);
    if (request.action().compare("com.RogerLeblanc.phoneAbuserService.START") == 0) {
        setDeviceActive(getScreenOn() && !getBedsideModeOn());
        udp->sendMessage("deviceActive$$" + getDeviceActive() ? "true" : "false");
    }
}

void Service::onUdpDataReceived(QString udpData) {
    qDebug() << "Received this from UI :" << udpData;

    QStringList allData = udpData.split("$$");
    if (allData.size() < 2)
        return;

    QString command = allData[0];
    QString data = allData[1];

    if (command == "shutdown")
        bb::Application::instance()->quit();
}

void Service::setScreenOn(bool newValue) {
    qDebug() << "setScreenOn() :" << newValue;
    if (m_screenOn != newValue) {
        m_screenOn = newValue;
        emit screenOnChanged();
    }
}

void Service::setBedsideModeOn(bool newValue) {
    qDebug() << "setBedsideModeOn() :" << newValue;
    if (m_bedsideModeOn != newValue) {
        m_bedsideModeOn = newValue;
        emit bedsideModeOnChanged();
    }
}

void Service::setDeviceActive(bool newValue) {
    qDebug() << "setDeviceActive() :" << newValue;
    if (m_deviceActive != newValue) {
        m_deviceActive = newValue;
        emit deviceActiveChanged();
    }
}

void Service::onDeviceActiveChanged() {
    qDebug() << "onDeviceActiveChanged()";

    // Signal UI
    udp->sendMessage("deviceActive$$" + getDeviceActive() ? "true" : "false");

    if (getDeviceActive())
        timer->start();
    else
        timer->stop();
}

void Service::onScreenOnOrBedsideModeOnChanged() {
    qDebug() << "onScreenOnOrBedsideModeOnChanged() :" << getScreenOn() << getBedsideModeOn();
    if (getScreenOn() && !getBedsideModeOn()) {
        if (!getDeviceActive())
            setDeviceActive(true);
    }
    else {
        if (getDeviceActive())
            setDeviceActive(false);
    }
}

void Service::onActivityStateChanged(bb::device::UserActivityState::Type userActivityState) {
    qDebug() << "onActivityStateChanged() :" << userActivityState;
    setScreenOn((userActivityState == bb::device::UserActivityState::Active) ? true : false);
}

void Service::onBedsideModeActiveChanged(bool newState) {
    qDebug() << "onBedsideModeActiveChanged() :" << newState;
    setBedsideModeOn(newState);
}

void Service::onTimeout() {
    if (timeActive.isEmpty())
        timeActive.append(QVariant(QDateTime(QDate::currentDate())));

    if (getDeviceActive())
        timeActive[0] = QVariant(timeActive[0].toDateTime().addSecs(1));

    // If we passed midnight
    if (timeActive[0].toDateTime().date() != QDate::currentDate()) {
        // Prepend a new timer
        timeActive.prepend(QVariant(QDateTime(QDate::currentDate())));

        // Keep the list to 7
        if (timeActive.size() > 7)
            timeActive.removeLast();
    }

    QString timeToSend;
    for (int i = 0; i < timeActive.size(); i++) {
        timeToSend += timeActive[i].toDateTime().toString("dddd h:mm:ss");
        if (i < (timeActive.size() - 1))
            timeToSend += "\n";
    }

    // Signal UI
    udp->sendMessage("timeActive$$" + timeToSend);

    // Update UpFront every minute of activity
    if (timeActive[0].toDateTime().time().second() == 0)
        sendToUpFront(timeToSend);
}

void Service::sendToUpFront(QString & message) {
    // Send to UpFront, fill backgroundZ image (url), image (url), title, message, color (bb::cascades::Color)
    bb::ApplicationInfo appInfo;
    QString backgroundZ = "";
    QString backgroundQ = "";
    QString icon = "http://s26.postimg.org/vnzpmqqcl/no_phone_zone_38_38.png";
    QString seconds = ""; // leave blank
    QString sendToT2w = ""; // leave blank
    QString textColor = "White"; // Choose any color available in QML
    QString other = "FontSize:Small";

    QString command = appInfo.signingHash() + "##" + appInfo.title() + "##" + backgroundZ + "##" + backgroundQ + "##" + icon + "##" + message + "##" + seconds + "##" + sendToT2w + "##" + textColor + "##" + other;
    m_upFront->updateUpFront(command);
    qDebug() << "sendToUpFront:" << command;
}

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

#include "applicationui.hpp"

#include <bb/Application>
#include <bb/cascades/Application>
#include <bb/cascades/AbstractCover>
#include <bb/cascades/MultiCover>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/LocaleHandler>
#include <bb/system/InvokeManager>

using namespace bb::cascades;
using namespace bb::system;

ApplicationUI::ApplicationUI() :
        QObject(),
        m_translator(new QTranslator(this)),
        m_localeHandler(new LocaleHandler(this)),
        m_invokeManager(new InvokeManager(this)),
        settings(new Settings(this))
{
    // Start HL part
    InvokeRequest request;
    request.setTarget("com.RogerLeblanc.phoneAbuserService");
    request.setAction("com.RogerLeblanc.phoneAbuserService.START");
    m_invokeManager->invoke(request);

    // prepare the localization
    if (!QObject::connect(m_localeHandler, SIGNAL(systemLanguageChanged()),
            this, SLOT(onSystemLanguageChanged()))) {
        // This is an abnormal situation! Something went wrong!
        // Add own code to recover here
        qWarning() << "Recovering from a failed connect()";
    }

    // initial load
    onSystemLanguageChanged();

    // This is used to communicate with UI part
    udp = new UdpModule(this);
    udp->listenOnPort(UDP_UI_LISTEN_ON_PORT);
    connect(udp, SIGNAL(receivedData(QString)), this, SLOT(onUdpDataReceived(QString)));

    setAppFontSize(settings->value("appFontSize", DEFAULT_APP_FONT_SIZE).toDouble());
    setActiveFrameFontSize(settings->value("activeFrameFontSize", DEFAULT_ACTIVE_FRAME_FONT_SIZE).toDouble());

    // Create scene document from main.qml asset, the parent is set
    // to ensure the document gets destroyed properly at shut down.
    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);

    // Make app available to the qml.
    qml->setContextProperty("_app", this);
    qml->setContextProperty("_settings", settings);
    qml->setContextProperty("_udp", udp);

    // Create root object for the UI
    AbstractPane *root = qml->createRootObject<AbstractPane>();

    // Set created root object as the application scene
    Application::instance()->setScene(root);

    // Set the Cover for the application running in minimized mode
    addApplicationCover();
}

void ApplicationUI::onSystemLanguageChanged()
{
    QCoreApplication::instance()->removeTranslator(m_translator);
    // Initiate, load and install the application translation files.
    QString locale_string = QLocale().name();
    QString file_name = QString("phoneAbuser_%1").arg(locale_string);
    if (m_translator->load(file_name, "app/native/qm")) {
    QCoreApplication::instance()->installTranslator(m_translator);
    }
}

void ApplicationUI::addApplicationCover()
{
    QmlDocument *qmlCover = QmlDocument::create("asset:///cover/AppCover.qml").parent(this);
    qmlCover->setContextProperty("_app", this);

    if (!qmlCover->hasErrors()) {
        AbstractCover* cover = qmlCover->createRootObject<MultiCover>();

        Application::instance()->setCover(cover);
    }
}

void ApplicationUI::onUdpDataReceived(QString udpData) {
//    qDebug() << "Received this from HL :" << udpData;
    QStringList allData = udpData.split("$$");
    if (allData.size() < 2)
        return;

    QString command = allData[0];
    QString data = allData[1];

    if (command == "deviceActive")
        setDeviceActive((data == "true") ? true : false);
    if (command == "timeActive")
        setTimeActive(data);
    if (command == "shutdown")
        bb::Application::instance()->quit();
}

void ApplicationUI::setDeviceActive(bool deviceActive) {
    if (m_deviceActive != deviceActive) {
        m_deviceActive = deviceActive;
        emit deviceActiveChanged();
    }
}

void ApplicationUI::setTimeActive(QString timeActive) {
    if (m_timeActive != timeActive) {
        m_timeActive = timeActive;
        emit timeActiveChanged();
    }
}

void ApplicationUI::setAppFontSize(int appFontSize) {
    if (m_appFontSize != appFontSize) {
        m_appFontSize = appFontSize;
        settings->setValue("appFontSize", appFontSize);
        emit appFontSizeChanged();
    }
}

void ApplicationUI::setActiveFrameFontSize(int activeFrameFontSize) {
    if (m_activeFrameFontSize != activeFrameFontSize) {
        m_activeFrameFontSize = activeFrameFontSize;
        settings->setValue("activeFrameFontSize", activeFrameFontSize);
        emit activeFrameFontSizeChanged();
    }
}

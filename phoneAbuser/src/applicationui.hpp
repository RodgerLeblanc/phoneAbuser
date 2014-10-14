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

#ifndef ApplicationUI_HPP_
#define ApplicationUI_HPP_

#include <QObject>

#include "UdpModule.h"
#include "Commons.h"
#include "Settings.h"

namespace bb {
    namespace cascades {
        class LocaleHandler;
    }
    namespace system {
        class InvokeManager;
    }
}

class QTranslator;
class UdpModule;

/*!
 * @brief Application UI object
 *
 * Use this object to create and init app UI, to create context objects, to register the new meta types etc.
 */
class ApplicationUI: public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool deviceActive READ getDeviceActive WRITE setDeviceActive NOTIFY deviceActiveChanged);
    Q_PROPERTY(QString timeActive READ getTimeActive WRITE setTimeActive NOTIFY timeActiveChanged);
    Q_PROPERTY(int appFontSize READ getAppFontSize WRITE setAppFontSize NOTIFY appFontSizeChanged);
    Q_PROPERTY(int activeFrameFontSize READ getActiveFrameFontSize WRITE setActiveFrameFontSize NOTIFY activeFrameFontSizeChanged);
public:
    ApplicationUI();
    virtual ~ApplicationUI() { }

public slots:
    void onSystemLanguageChanged();
    Q_INVOKABLE void onUdpDataReceived(QString udpData);

private:
    void addApplicationCover();

    bool getDeviceActive() { return m_deviceActive; }
    void setDeviceActive(bool deviceActive);
    QString getTimeActive() { return m_timeActive; }
    void setTimeActive(QString timeActive);
    int getAppFontSize() { return m_appFontSize; }
    void setAppFontSize(int appFontSize);
    int getActiveFrameFontSize() { return m_activeFrameFontSize; }
    void setActiveFrameFontSize(int activeFrameFontSize);

    QTranslator* m_translator;
    bb::cascades::LocaleHandler* m_localeHandler;
    bb::system::InvokeManager* m_invokeManager;

    Settings* settings;
    UdpModule *udp;

    bool m_deviceActive;
    QString m_timeActive;
    int m_appFontSize;
    int m_activeFrameFontSize;

signals:
    void deviceActiveChanged();
    void timeActiveChanged();
    void appFontSizeChanged();
    void activeFrameFontSizeChanged();
};

#endif /* ApplicationUI_HPP_ */

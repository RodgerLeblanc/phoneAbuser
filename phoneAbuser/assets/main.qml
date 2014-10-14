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

import bb.cascades 1.3

Page {
    property string timeActive: _app.timeActive
    property int appFontSize: _app.appFontSize
    
    ScrollView {
        Container {
            layout: DockLayout {}
            horizontalAlignment: HorizontalAlignment.Fill
            verticalAlignment: VerticalAlignment.Fill
            Container {
                horizontalAlignment: HorizontalAlignment.Center
                verticalAlignment: VerticalAlignment.Center
                Label {
                    text: timeActive
                    horizontalAlignment: HorizontalAlignment.Center
                    multiline: true
                    autoSize.maxLineCount: 7
                    textStyle.fontSize: FontSize.PointValue
                    textStyle.fontSizeValue: appFontSize
                }
            }
        }
    }


    Menu.definition: MenuDefinition {
        settingsAction: [
            SettingsActionItem {
                ActionBar.placement: ActionBarPlacement.OnBar
                onTriggered: {
                    settingsSheet.open()
                }
            }
        ]
        
        actions: [
            ActionItem {
                title: qsTr("Shutdown")
                ActionBar.placement: ActionBarPlacement.OnBar
                imageSource: "asset:///images/ic_cancel.png"
                onTriggered: {
                    _udp.sendMessage("shutdown$$")
                    _app.onUdpDataReceived("shutdown$$")
                }
            },
            ActionItem {
                title: qsTr("About")
                ActionBar.placement: ActionBarPlacement.OnBar
                imageSource: "asset:///images/ic_info.png"
                onTriggered: {
                    aboutSheet.open()
                }
            }
        ]      
    } // end of MenuDefinition

    attachedObjects: [
        AboutSheet {
            id: aboutSheet
        },
        SettingsSheet {
            id: settingsSheet
        },
        ComponentDefinition {
            id: menu
        }
    ]
}

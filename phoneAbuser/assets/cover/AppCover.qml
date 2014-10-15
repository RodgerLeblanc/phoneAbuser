/* Copyright (c) 2013 BlackBerry Limited.
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

MultiCover {
    id: multiCover
    property string timeActive: _app.timeActive
    property int activeFrameFontSize: _app.activeFrameFontSize
    property string theme2: multiCover.themeStyleToString(Application.themeSupport.theme.colorTheme.style)
    property string theme: Application.themeSupport.theme.colorTheme.style == VisualStyle.Bright ? "Bright" : "Dark"

    function themeStyleToString(style){
        switch(style) {
            case VisualStyle.Bright:    return "Bright"
            case VisualStyle.Dark:      return "Dark"
        }
        return "UNKNOWN"
    }
    
    SceneCover {
        id: bigCover
        MultiCover.level: CoverDetailLevel.High
        content: Container {
            layout: DockLayout {}
            horizontalAlignment: HorizontalAlignment.Fill
            verticalAlignment: VerticalAlignment.Fill
            background: theme == "Bright" ? Color.White : Color.Black
            Container {
                horizontalAlignment: HorizontalAlignment.Center
                verticalAlignment: VerticalAlignment.Center
                Label {
                    text: timeActive
                    textStyle.color: theme == "Bright" ? Color.Black : Color.White
                    textStyle.fontWeight: FontWeight.Bold
                    horizontalAlignment: HorizontalAlignment.Center
                    multiline: true
                    autoSize.maxLineCount: 7
                    textStyle.fontSize: FontSize.PointValue
                    textStyle.fontSizeValue: activeFrameFontSize
                }
            }
        }
    } // sceneCover HIGH
    
    SceneCover {
        id: smallCover
        MultiCover.level: CoverDetailLevel.Medium
        content: Container {
            layout: DockLayout {}
            horizontalAlignment: HorizontalAlignment.Fill
            verticalAlignment: VerticalAlignment.Fill
            background: theme == "Bright" ? Color.White : Color.Black
            Container {
                horizontalAlignment: HorizontalAlignment.Center
                verticalAlignment: VerticalAlignment.Center
                Label {
                    text: timeActive
                    textStyle.color: theme == "Bright" ? Color.Black : Color.White
                    textStyle.fontWeight: FontWeight.Bold
                    horizontalAlignment: HorizontalAlignment.Center
                    multiline: true
                    autoSize.maxLineCount: 3
                    textStyle.fontSize: FontSize.PointValue
                    textStyle.fontSizeValue: activeFrameFontSize
                }
            }
        }
    } // sceneCover MEDIUM
} //  multiCover

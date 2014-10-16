import bb.cascades 1.3
import bb.system 1.2

Sheet {
    id: aboutSheet
    Page {
        titleBar: TitleBar {
            title: qsTr("About")
            acceptAction: ActionItem {
                title: qsTr("Ok")
                onTriggered: {
                    aboutSheet.close()
                }
            }
        }
        ScrollView {
            Container {
                layout: DockLayout {}
                horizontalAlignment: HorizontalAlignment.Fill
                verticalAlignment: VerticalAlignment.Fill
                Container {
                    horizontalAlignment: HorizontalAlignment.Center
                    verticalAlignment: VerticalAlignment.Center
                    Label {
                        horizontalAlignment: HorizontalAlignment.Center
                        text: qsTr("This app tracks your phone addiction... daily")
                        multiline: true
                        textStyle.base: SystemDefaults.TextStyles.TitleText
                    }
                    Label {
                        horizontalAlignment: HorizontalAlignment.Center
                        text: Application.applicationName + " " + Application.applicationVersion
                        textStyle.base: SystemDefaults.TextStyles.BigText
                    }
                    Label {
                        horizontalAlignment: HorizontalAlignment.Center
                        text: "<html><a href=\"http://bit.ly/1w7LUfm\">" + qsTr("Donate") + "</a></html>"
                        textStyle.base: SystemDefaults.TextStyles.BodyText
                    }
                }
            }
        }
    }
}

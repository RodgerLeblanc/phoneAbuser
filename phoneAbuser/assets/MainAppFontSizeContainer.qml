import bb.cascades 1.3

Container {
    horizontalAlignment: HorizontalAlignment.Center
    DropDown {
        title: qsTr("Main App Font Size")
        Option {                        
            id: option15
            text: qsTr("15")
            value: 15
        }
        Option {                        
            id: option20
            text: qsTr("20")
            value: 20
        }
        Option {                        
            id: option25
            text: qsTr("25")
            value: 25
        }
        Option {
            id: option30
            text: qsTr("30")
            value: 30
        }
        Option {                        
            id: option35
            text: qsTr("35")
            value: 35
        }
        Option {
            id: option40
            text: qsTr("40")
            value: 40
        }
        onSelectedOptionChanged: {
            _app.appFontSize = selectedOption.value
        }
        onCreationCompleted: {
            switch (_app.appFontSize) {
                case 15: 
                    setSelectedOption(option15)
                    break
                case 20: 
                    setSelectedOption(option20)
                    break
                case 25: 
                    setSelectedOption(option25)
                    break
                case 30: 
                    setSelectedOption(option30)
                    break
                case 35: 
                    setSelectedOption(option35)
                    break
                case 40: 
                    setSelectedOption(option40)
                    break
                default:
                    setSelectedOption(option20)
                    break
            }
        }
    }
}

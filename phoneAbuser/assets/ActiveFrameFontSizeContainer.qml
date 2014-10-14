import bb.cascades 1.3

Container {
    horizontalAlignment: HorizontalAlignment.Center
    DropDown {
        title: qsTr("Active Frame Font Size")
        Option {                        
            id: option4
            text: qsTr("4")
            value: 4
        }
        Option {                        
            id: option6
            text: qsTr("6")
            value: 6
        }
        Option {                        
            id: option8
            text: qsTr("8")
            value: 8
        }
        Option {
            id: option10
            text: qsTr("10")
            value: 10
        }
        Option {                        
            id: option12
            text: qsTr("12")
            value: 12
        }
        Option {
            id: option14
            text: qsTr("14")
            value: 14
        }
        onSelectedOptionChanged: {
            _app.activeFrameFontSize = selectedOption.value
        }
        onCreationCompleted: {
            switch (_app.activeFrameFontSize) {
                case 4: 
                    setSelectedOption(option4)
                    break
                case 6: 
                    setSelectedOption(option6)
                    break
                case 8: 
                    setSelectedOption(option8)
                    break
                case 10: 
                    setSelectedOption(option10)
                    break
                case 12: 
                    setSelectedOption(option12)
                    break
                case 14: 
                    setSelectedOption(option14)
                    break
                default:
                    setSelectedOption(option8)
                    break
            }
        }
    }
}

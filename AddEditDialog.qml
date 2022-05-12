import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.5   //для версии Qt 5.6
import QtQuick.Layouts 1.2


Window {
    id: root
    modality: Qt.ApplicationModal  // окно объявляется модальным (только оно принимает ввод, а не другие окна)
    title: qsTr("Информация о игре")
    minimumWidth: 600
    maximumWidth: 600
    minimumHeight: 475
    maximumHeight: 475

    property bool isEdit: false
    property int currentIndex: -1

    GridLayout {
        anchors { left: parent.left; top: parent.top; right: parent.right; bottom: buttonCancel.top; margins: 10 }
        columns: 2

        Label {
            Layout.alignment: Qt.AlignRight  // выравнивание по правой стороне
            text: qsTr("Название игры:")
        }
        TextField {
            id: textName
            Layout.fillWidth: true
            placeholderText: qsTr("Введите название игры")
        }
        Label {
            Layout.alignment: Qt.AlignRight
            text: qsTr("Платформа:")
        }
        ComboBox {
               id: comboBoxPlatform
               width: 120
               model: ["PC", "Xbox", "PS5", "Nintendo", "Phone"]
        }
        Label {
            Layout.alignment: Qt.AlignRight
            text: qsTr("Разработчик игры:")
        }
        TextField {
            id: textCreator
            Layout.fillWidth: true
            placeholderText: qsTr("Укажите разработчика игры")
        }
        Label {
            Layout.alignment: Qt.AlignRight
            text: qsTr("Жанр:")
        }
        TextField {
            id: textGenre
            Layout.fillWidth: true
            placeholderText: qsTr("Введите жанр игры")
        }
    }

    Button {
        anchors { right: buttonCancel.left; verticalCenter: buttonCancel.verticalCenter; rightMargin: 10 }
        text: qsTr("ОК")
        width: 100
        onClicked: {
            root.hide()
            if (currentIndex<0)
            {
                add(textName.text, comboBoxPlatform.currentValue, textCreator.text, textGenre.text)
            }
            else
            {
                edit(textName.text, comboBoxPlatform.currentValue, textCreator.text, textGenre.text, root.currentIndex)
            }

        }
    }

    Button {
        id: buttonCancel
        anchors { right: parent.right; bottom: parent.bottom; rightMargin: 10; bottomMargin: 10 }
        text: qsTr("Отменить")
        width: 100
        onClicked: {
             root.hide()
        }
    }

    // изменение статуса видимости окна диалога
    onVisibleChanged: {
      if (visible && currentIndex < 0) {
          textName.text = ""
          comboBoxPlatform.currentIndex = 0
          textCreator.text = ""
          textGenre.text = ""
      }
    }

    function execute(nameGame, platformGame, creatorGame, genreGame, index){
        isEdit = true

        textName.text = nameGame
        comboBoxPlatform.currentIndex = comboBoxPlatform.model.indexOf(platformGame)
        textCreator.text = creatorGame
        textGenre.text = genreGame

        root.currentIndex = index

        root.show()
    }


 }

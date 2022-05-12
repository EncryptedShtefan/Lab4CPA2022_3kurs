import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.2

Window {
    id: root
    // Говорим, что это окно является модальным
    modality: Qt.ApplicationModal
    title: qsTr("Ответ")
    width: 220
    height: 50

    // Создаём Grid в котором будем размещать элементы
    GridLayout {
        // Задаём размещение этого Grid
        anchors { left: parent.left;
                  top: parent.top;
                  right: parent.right;
                  margins: 10 }
        // И говорим, что у этого Grid будет 2 колонки для текста и ответа
        columns: 2

        // Label для того, чтобы понять, что мы вывели
        Label {
            Layout.alignment: Qt.AlignRight
            text: qsTr("Получившийся результат:")
        }
        // Label для текста ответа
        Label {
            id: textCount
            Layout.fillWidth: true
        }

    }

    // Задаём функцию для вывода информации
    function countGames(area){
        textCount.text = count(area);
        root.show()
    }
 }

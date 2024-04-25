import QtQuick 2.5
import QtGraphicalEffects 1.0
import Sailfish.Silica 1.0
import test_module.chart 0.1

BackgroundItem {
    id: lineDiagramItem

    property alias debugBorder: itemDebugBorder.visible

    property ValueDiagram valueDiagram: ValueDiagram{
        values: [10,20]
    }

    // Легенда для получения цвета столбцов
    property list<LegendDiagram> legends: [
        //Базовая легенда, предполагается, что она будет изменена снаружи
        LegendDiagram{
            color: "black"
        }
    ]

    property real fontSize: 13

    property real maxValueDiagram: 100 //Максимальное значение во всей диаграмме (используется для расчета высоты значения
    property real widthValue: 20 // Толщина 1 толбца значения
    property real itemSpacing: 10 // расстояние между значениями

    //Базовая ширина элемента берется из расчета, что показывается только 1 значение
    width: widthValue
    onValueDiagramChanged: {
        lineDiagramItem.width = valueDiagram.count * (widthValue + itemSpacing);
        valueDiagram.updateMax();
    }

    Component.onCompleted: {
        lineDiagramItem.width = valueDiagram.count * (widthValue + itemSpacing);
        valueDiagram.updateMax();
    }

    //Максимальная высота элемента c цифрами
    height: 100
    property real itemHeight: height - fontSize * 1.7

    anchors{
        bottom: parent.bottom
    }

    Rectangle{
        id: itemDebugBorder
        visible: debugBorder
        anchors.fill: parent
        border.color: "red"
        border.width: 2
    }

    Row{
        id: valuesRow
        anchors.fill: parent

        spacing: lineDiagramItem.itemSpacing

        function getItemHeight(value){
            if(value===0){
               return 0.01;
            }
            return value / (lineDiagramItem.maxValueDiagram *0.01) * (lineDiagramItem.itemHeight*0.01);
        }

        Repeater{
            model: valueDiagram.count

            delegate: Rectangle{
                id: valueRect
                anchors.bottom: parent.bottom
                property real maxHeigh: lineDiagramItem.maxValueDiagram

                color: ( legends[ (index) % (legends.length )].color )
                width: lineDiagramItem.widthValue

                border.width: 1
                height: valuesRow.getItemHeight(valueDiagram.values[index]);
                onMaxHeighChanged: {
                    valueRect.height = valuesRow.getItemHeight(valueDiagram.values[index]);
                }

                Text{
                    id: valueText
                    width: parent.width
                    font.pointSize: fontSize
                    horizontalAlignment: Text.AlignHCenter
                    text: Number( valueDiagram.values[index] ).toFixed( 2 )
                    anchors.bottom: parent.top
                }
            }

        }
        Rectangle{
            id: separateLine
            visible: valueDiagram.count > 1
            width: 2
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            color: "#808080"
        }
    }
}

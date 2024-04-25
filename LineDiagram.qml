import QtQuick 2.5
import QtGraphicalEffects 1.0
import Sailfish.Silica 1.0
import test_module.test_cppmodule 0.1

/*** Пример использования диаграммы

LineDiagram{
    id: laborCostsDiag
    spacing: 10 // расстояние между элементами
    itemSpacing: 5 // расстояние между столбцами элемента

    textFontSize: 17    // размер текста подписи под элементом
    valueFontSize: 16   // размер текста значения над столбцами графика
    legendFontSize: 17  // размер текста легенды

    chartHeight: 200    // высота графика с столбцами, подписью и легендой (пересчитывается, зависит от параметров ниже)
    textHeight: 100     // высота подписи под графиком
    legendHeight: 70    // высота легенды
    itemWidth: 85       // ширина столбца
    legendTextHeight:50 // высота текста элемента легенды
    legendTextWidth:200 // ширина текста элемента легенды

    anchors{
        left: parent.left
        leftMargin: 10
        right: parent.right
        rightMargin: 10
    }

    legends: [ //Пример добавления легенд на график (статическое добавление)
        LegendDiagram{
            color: "black"
            text: "Плановые трудозатраты"
        },
        LegendDiagram{
            color: "red"
            text: "Фактические трудозатраты"
        }
    ]

    Component.onCompleted: {
        if(woCommonInfo.countAll > 0){ // Динамическое добавление значений
            var list = woCommonInfo.workingHoursOfTypes;
            for(var type in list){

                var listValue = [Number(list[type]["sum_plan"]), Number(list[type]["sum_labor"])];

                laborCostsDiag.addValue(list[type]["text"],
                                        listValue);
            }
            laborCostsDiag.update(); // после добавления обязательно нужно обновить элемент
        }
    }
*/

BackgroundItem {
    id: linerDiagram
    width: parent.width
    height: chartHeight + textHeight + legendHeight
    clip: false

    property bool debugBorderVisible: false //Используется для отображения границ элементов для тестирования

    property alias chartHeight: valuesListView.height
    property alias textHeight: valueTextListView.height
    property alias legendHeight: rectLegend.height

    onChartHeightChanged: linerDiagram.height=chartHeight + textHeight + legendHeight
    onTextHeightChanged: linerDiagram.height=chartHeight + textHeight + legendHeight
    onLegendHeightChanged: linerDiagram.height=chartHeight + textHeight + legendHeight

    property real spacing: 20
    ///Размер 1 элемента данных
    property real itemWidth: 20
    property real itemSpacing: 10

    property int nestedValuesCount: 1

    property int textFontSize: 11
    property int valueFontSize: 11
    property int legendFontSize: 11
    property int borderSize: 3

    property alias legendTextHeight: legendView.cellHeight
    property alias legendTextWidth: legendView.cellWidth
    function addValue(text, value){
        diagramModel.addValue(text,value);
        diagramModel.diagramValuesChanged();
    }

    function clearValue(){
        diagramModel.clearValue();
    }

    function update(){
        diagramModel.updateMaxValue();
    }

    Rectangle{
        color: "white"
        anchors.fill: parent
    }

    function removeInd(index){
        diagram.remove(index);
    }

    property alias legends: diagramModel.legends
    property alias values: diagramModel.diagramValues

    LineDiagramModel{
        id: diagramModel
    }

    Component.onCompleted: {
        diagramModel.updateMaxValue();
    }

    SilicaListView{
        id: valuesListView

        property real maxVal: 100.0

        height: parent.height / 3 * 2

        anchors{
            left: parent.left
            right: parent.right
            top: parent.top
            leftMargin: 10
            rightMargin: 10
        }

        clip: true
        spacing: linerDiagram.spacing
        HorizontalScrollDecorator{}

        orientation: ListView.Horizontal
        flickableDirection: Flickable.HorizontalFlick
        model: diagramModel.diagramValues

        onContentXChanged: {
            valueTextListView.contentX = contentX;
            imageRightArrow.visible = contentX+linerDiagram.width < contentWidth;
            imageLeftArrow.visible = contentX > itemWidth + 30;
        }

        delegate: LineDiagramItem{
            id: lineItem

            debugBorder: debugBorderVisible

            legends: diagramModel.legends
            fontSize: valueFontSize

            valueDiagram: modelData

            itemSpacing: linerDiagram.itemSpacing
            widthValue: linerDiagram.itemWidth
            height: valuesListView.height

            maxValueDiagram: diagramModel.diagramMaxValue
        }
    }
    Rectangle{
        height: 2
        border.width: 2
        anchors.leftMargin: 0
        anchors.rightMargin: 0
        anchors{
            top:valuesListView.bottom
            left: parent.left
            right: parent.right
        }
        border.color: "black"
    }

    SilicaListView {
        id: valueTextListView
        enabled: false
        HorizontalScrollDecorator{}

        height: parent.height / 3 * 0.5

        anchors{
            top:valuesListView.bottom
            topMargin: 2
            left: valuesListView.left
            right: valuesListView.right
        }

        clip: true
        spacing: linerDiagram.spacing
        orientation: ListView.Horizontal

        model: diagramModel.diagramValues

        delegate: Item {
            id: valueTextItem
            width: modelData.count * (itemWidth + itemSpacing)
            height: parent.height
            Rectangle{
                visible: debugBorderVisible
                border.width: 1
                anchors.fill: parent
                border.color: "green"
            }

            Text {
                id: valueText
                width: parent.width
                text: modelData.text
                font.bold: true
                font.pointSize: textFontSize
                wrapMode: Text.WordWrap
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                onHeightChanged: {
                    if(height > textHeight){
                        textHeight = height;
                    }
                }
            }
        }
    }

    Image {
        id: imageRightArrow
        visible: valuesListView.contentX+linerDiagram.width < valuesListView.contentWidth
        source: "image://theme/icon-m-arrow-right-green?red"
        width: 40
        height: 40
        anchors.verticalCenter: valuesListView.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: -15
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: imageLeftArrow
        visible: valuesListView.contentX > itemWidth + 30
        source: "image://theme/icon-m-arrow-left-green?red"
        width: 40
        height: 40
        anchors.verticalCenter: valuesListView.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: -15
        fillMode: Image.PreserveAspectFit
    }

    Rectangle{
        id: rectLegend
        border{
            width: debugBorderVisible ? 1 : 0
            color: "red"
        }
        anchors{
            topMargin: 5
            top:valueTextListView.bottom
            left: parent.left
            leftMargin: 20
            right: parent.right
            rightMargin: 20
        }
        SilicaGridView{
            id: legendView
            anchors.fill: parent
            model: diagramModel.legends;
            cellHeight: 30
            cellWidth: 120
            clip: true

            delegate: BackgroundItem {
                Rectangle{
                    anchors.fill: parent
                    border{
                        width: debugBorderVisible ? 1 : 0
                        color: "red"
                    }
                }
                height: legendText.height
                width: legendColorRect.width + legendText.width
                Rectangle{
                    id: legendColorRect
                    anchors{
                        verticalCenter: parent.verticalCenter
                        left: parent.left
                    }
                    height: 20
                    width: 20
                    color: modelData.color
                }
                Text{
                    id: legendText
                    anchors{
                        left: legendColorRect.right
                        leftMargin: 10
                    }

                    text: modelData.text
                    font.pointSize: legendFontSize
                    width: legendView.cellWidth - legendColorRect.width
                    wrapMode: Text.WordWrap
                }
            }
        }
    }

}



/*##^##
Designer {
    D{i:0;formeditorZoom:1.33;height:300;width:300}
}
##^##*/

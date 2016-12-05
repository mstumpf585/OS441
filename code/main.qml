import QtQuick 2.3
import QtQuick.Window 2.2

Window {
    id: window1
    visible: true
    width: 640
    height: 640

    //signal
    signal qmlRequireData(string msg)
    //slot
    function qmlUpdate0(text){
        image1.source = "toon" + String.fromCharCode(text) + ".png"
    }
    function qmlUpdate1(text){
        image2.source = "toon" + String.fromCharCode(text) + ".png"
    }
    function qmlUpdate2(text){
        image3.source = "toon" + String.fromCharCode(text) + ".png"
    }
    function qmlUpdate3(text){
        image4.source = "toon" + String.fromCharCode(text) + ".png"
    }
    function qmlUpdate4(text){
        image5.source = "toon" + String.fromCharCode(text) + ".png"
    }
    function qmlUpdate5(text){
        image6.source = "toon" + String.fromCharCode(text) + ".png"
    }
    function qmlUpdate6(text){
        image7.source = "toon" + String.fromCharCode(text) + ".png"
    }
    function qmlUpdate7(text){
        image8.source = "toon" + String.fromCharCode(text) + ".png"
    }
    function qmlUpdate8(text){
        image9.source = "toon" + String.fromCharCode(text) + ".png"
    }
    function qmlUpdate9(text){
        image10.source = "toon" + String.fromCharCode(text) + ".png"
    }
    function qmlUpdate10(text){
        image11.source = "toon" + String.fromCharCode(text) + ".png"
    }
    function qmlUpdate11(text){
        image12.source = "toon" + String.fromCharCode(text) + ".png"
    }
    function qmlUpdate12(text){
        image13.source = "toon" + String.fromCharCode(text) + ".png"
    }
    function qmlUpdate13(text){
        image14.source = "toon" + String.fromCharCode(text) + ".png"
    }
    function qmlUpdate14(text){
        image15.source = "toon" + String.fromCharCode(text) + ".png"
    }
    function qmlUpdate15(text){
        image16.source = "toon" + String.fromCharCode(text) + ".png"
    }
    function qmlUpdate16(text){
        image17.source = "toon" + String.fromCharCode(text) + ".png"
    }
    function qmlUpdate17(text){
        image18.source = "toon" + String.fromCharCode(text) + ".png"
    }
    function qmlUpdate18(text){
        image19.source = "toon" + String.fromCharCode(text) + ".png"
    }
    function qmlUpdate19(text){
        image20.source = "toon" + String.fromCharCode(text) + ".png"
    }
    function qmlUpdate20(text){
        image21.source = "toon" + String.fromCharCode(text) + ".png"
    }
    function qmlUpdate21(text){
        image22.source = "toon" + String.fromCharCode(text) + ".png"
    }
    function qmlUpdate22(text){
        image23.source = "toon" + String.fromCharCode(text) + ".png"
    }
    function qmlUpdate23(text){
        image24.source = "toon" + String.fromCharCode(text) + ".png"
    }
    function qmlUpdate24(text){
        image25.source = "toon" + String.fromCharCode(text) + ".png"
    }

    //slot for 2nd part
    function qmlUpdate25(text){
        image26.source = "toon" + String.fromCharCode(text) + ".png"
    }
    function qmlUpdate26(text){
        image27.source = "toon" + String.fromCharCode(text) + ".png"
    }
    function qmlUpdate27(text){
        image28.source = "toon" + String.fromCharCode(text) + ".png"
    }
    function qmlUpdate28(text){
        image29.source = "toon" + String.fromCharCode(text) + ".png"
    }
    function qmlUpdate29(text){
        image30.source = "toon" + String.fromCharCode(text) + ".png"
    }
    function qmlUpdate30(text){
        image31.source = "toon" + String.fromCharCode(text) + ".png"
    }
    function qmlUpdate31(text){
        image32.source = "toon" + String.fromCharCode(text) + ".png"
    }
    function qmlUpdate32(text){
        image33.source = "toon" + String.fromCharCode(text) + ".png"
    }
    function qmlUpdate33(text){
        image34.source = "toon" + String.fromCharCode(text) + ".png"
    }
    function qmlUpdate34(text){
        image35.source = "toon" + String.fromCharCode(text) + ".png"
    }
    function qmlUpdate35(text){
        image36.source = "toon" + String.fromCharCode(text) + ".png"
    }
    function qmlUpdate36(text){
        image37.source = "toon" + String.fromCharCode(text) + ".png"
    }
    function qmlUpdate37(text){
        image38.source = "toon" + String.fromCharCode(text) + ".png"
    }
    function qmlUpdate38(text){
        image39.source = "toon" + String.fromCharCode(text) + ".png"
    }
    function qmlUpdate39(text){
        image40.source = "toon" + String.fromCharCode(text) + ".png"
    }
    function qmlUpdate40(text){
        image41.source = "toon" + String.fromCharCode(text) + ".png"
    }
    function qmlUpdate41(text){
        image42.source = "toon" + String.fromCharCode(text) + ".png"
    }
    function qmlUpdate42(text){
        image43.source = "toon" + String.fromCharCode(text) + ".png"
    }
    function qmlUpdate43(text){
        image44.source = "toon" + String.fromCharCode(text) + ".png"
    }
    function qmlUpdate44(text){
        image45.source = "toon" + String.fromCharCode(text) + ".png"
    }

    //for rectangle
    function qmlUpdate45(text){
        Rectangle.visible = text;
    }





    Image {
        id: image1
        x: 18
        y: 7
        width: 100
        height: 100
        source: "toon-.png"
    }

    Image {
        id: image2
        x: 137
        y: 7
        width: 100
        height: 100
        source: "toon-.png"
    }

    Image {
        id: image3
        x: 277
        y: 7
        width: 100
        height: 100
        source: "toon-.png"
    }

    Image {
        id: image4
        x: 406
        y: 7
        width: 100
        height: 100
        source: "toon-.png"
    }

    Image {
        id: image5
        x: 523
        y: 7
        width: 100
        height: 100
        source: "toon-.png"
    }

    Image {
        id: image6
        x: 18
        y: 124
        width: 100
        height: 100
        source: "toon-.png"
    }

    Image {
        id: image7
        x: 137
        y: 124
        width: 100
        height: 100
        source: "toon-.png"
    }

    Image {
        id: image8
        x: 277
        y: 124
        width: 100
        height: 100
        source: "toon-.png"
    }

    Image {
        id: image9
        x: 406
        y: 124
        width: 100
        height: 100
        source: "toon-.png"
    }

    Image {
        id: image10
        x: 523
        y: 124
        width: 100
        height: 100
        source: "toon-.png"
    }

    Image {
        id: image11
        x: 18
        y: 245
        width: 100
        height: 100
        source: "toon-.png"
    }

    Image {
        id: image12
        x: 137
        y: 245
        width: 100
        height: 100
        source: "toon-.png"
    }

    Image {
        id: image13
        x: 277
        y: 245
        width: 100
        height: 100
        source: "toon-.png"
    }

    Image {
        id: image14
        x: 406
        y: 245
        width: 100
        height: 100
        source: "toon-.png"
    }

    Image {
        id: image15
        x: 523
        y: 245
        width: 100
        height: 100
        source: "toon-.png"
    }

    Image {
        id: image16
        x: 18
        y: 379
        width: 100
        height: 100
        source: "toon-.png"
    }

    Image {
        id: image17
        x: 137
        y: 379
        width: 100
        height: 100
        source: "toon-.png"
    }

    Image {
        id: image18
        x: 277
        y: 379
        width: 100
        height: 100
        source: "toon-.png"
    }

    Image {
        id: image19
        x: 406
        y: 379
        width: 100
        height: 100
        source: "toon-.png"
    }

    Image {
        id: image20
        x: 523
        y: 379
        width: 100
        height: 100
        source: "toon-.png"
    }

    Image {
        id: image21
        x: 18
        y: 500
        width: 100
        height: 100
        source: "toon-.png"
    }

    Image {
        id: image22
        x: 137
        y: 505
        width: 100
        height: 100
        source: "toon-.png"
    }

    Image {
        id: image23
        x: 277
        y: 500
        width: 100
        height: 100
        source: "toon-.png"
    }

    Image {
        id: image24
        x: 406
        y: 505
        width: 100
        height: 100
        source: "toon-.png"
    }

    Image {
        id: image25
        x: 523
        y: 505
        width: 100
        height: 100
        source: "toon-.png"
    }

    Rectangle {
        id: rectangle1
        width: 640
        height: 640
        color: "#ffffff"
        visible: false

        Image {
            id: image26
            x: 23
            y: 230
            width: 50
            height: 50
            source: "toon-.png"
        }

        Image {
            id: image27
            x: 87
            y: 230
            width: 50
            height: 50
            source: "toon-.png"
        }

        Image {
            id: image28
            x: 152
            y: 230
            width: 50
            height: 50
            source: "toon-.png"
        }

        Image {
            id: image29
            x: 216
            y: 230
            width: 50
            height: 50
            source: "toon-.png"
        }

        Image {
            id: image30
            x: 275
            y: 230
            width: 50
            height: 50
            source: "toon-.png"
        }

        Image {
            id: image31
            x: 336
            y: 230
            width: 50
            height: 50
            source: "toon-.png"
        }

        Image {
            id: image32
            x: 399
            y: 230
            width: 50
            height: 50
            source: "toon-.png"
        }

        Image {
            id: image33
            x: 455
            y: 230
            width: 50
            height: 50
            source: "toon-.png"
        }

        Image {
            id: image34
            x: 511
            y: 230
            width: 50
            height: 50
            source: "toon-.png"
        }

        Image {
            id: image35
            x: 574
            y: 230
            width: 50
            height: 50
            source: "toon-.png"
        }

        Image {
            id: image36
            x: 23
            y: 322
            width: 50
            height: 50
            source: "toon-.png"
        }

        Image {
            id: image37
            x: 87
            y: 322
            width: 50
            height: 50
            source: "toon-.png"
        }

        Image {
            id: image38
            x: 152
            y: 322
            width: 50
            height: 50
            source: "toon-.png"
        }

        Image {
            id: image39
            x: 216
            y: 322
            width: 50
            height: 50
            source: "toon-.png"
        }

        Image {
            id: image40
            x: 275
            y: 322
            width: 50
            height: 50
            source: "toon-.png"
        }

        Image {
            id: image41
            x: 336
            y: 322
            width: 50
            height: 50
            source: "toon-.png"
        }

        Image {
            id: image42
            x: 399
            y: 322
            width: 50
            height: 50
            source: "toon-.png"
        }

        Image {
            id: image43
            x: 455
            y: 322
            width: 50
            height: 50
            source: "toon-.png"
        }

        Image {
            id: image44
            x: 511
            y: 322
            width: 50
            height: 50
            source: "toon-.png"
        }

        Image {
            id: image45
            x: 574
            y: 322
            width: 50
            height: 50
            source: "toon-.png"
        }
    }
}

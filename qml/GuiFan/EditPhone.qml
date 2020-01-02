import QtQuick 2.0

//TextEdit {
//    width: 200
//    text: "input"
//    font.pointSize: 10
//    focus: true

//}

TextInput {
    width: 200
        text:"1"
        validator: RegExpValidator{regExp: /[1][3,4,5,8][0-9]{9}/}
//        QRegExp regExp("[1][3,4,5,8][0-9]{9}");
//        phoneNumberLineEdit = new QMyLineEdit;
//        phoneNumberLineEdit->setPlaceholderText("请输入手机号码");
//        phoneNumberLineEdit->setValidator(new QRegExpValidator(regExp,this ));
    }


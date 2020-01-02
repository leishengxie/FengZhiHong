/******************************************************************************
**
** @file
** main.qml
** @brief
** 界面框架定义
** @author
** wenn
** @date
** 2017-3-29
**
******************************************************************************/
import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.2
import QtQuick.Window 2.2
import QtQml 2.2

Item {
	width: 1300
	height: 600

	RowLayout {
		visible: false
		anchors.centerIn: parent
	}

	Rectangle {
		id: rectangleBackground
		x: 0
		y: 0
		width: 1300
		height: 600
		color: "#7399be"

		Rectangle { // 搜索框
			id: rectangleSearch
			x: 22
			y: 71
			width: 360
			height: 500
			color: "#419af1"
			radius: 10
			border.color: "#ffffff"
			border.width: 2

			Rectangle { // 按钮集合（清空、回删、搜索）
				Button {  // 按钮：清除清空
					id: buttonClear
					x: 23
					y: 443
					width: 90
					height: 40
					//text: qsTr("清空")
					opacity: 0.8
					style: ButtonStyle { // 按钮显示风格定义
						background: Rectangle {
							color: control.pressed ? "gray" : "#7fb7ed"
							radius: 25
							border.color: "#ffffff"
							border.width: 1
						}
						label: Label { // 按键标签为"清空"
							text: qsTr("清空")
							color: "#ffffff"
							font.pixelSize: 20
							horizontalAlignment: Text.AlignHCenter
							verticalAlignment: Text.AlignVCenter
						}
					}
				}

				Button { // 按钮：向回删除
					id: buttonDelete
					x: 140
					y: 443
					width: 90
					height: 40
					//text: qsTr("回删")
					opacity: 0.8
					style: ButtonStyle { // 按钮显示风格定义
						background: Rectangle { // 背景颜色
							color: control.pressed ? "gray" : "#7fb7ed"
							radius: 25
							border.color: "#ffffff"
							border.width: 1
						}
						label: Label { // 按键标签为"回删"
							text: qsTr("回删")
							color: "#ffffff"
							font.pixelSize: 20
							horizontalAlignment: Text.AlignHCenter
							verticalAlignment: Text.AlignVCenter
						}
					}
				}

				Button { // 按钮：搜索
					id: buttonSearch
					x: 257
					y: 443
					width: 90
					height: 40
					text: qsTr("搜索")
					opacity: 0.8
					style: ButtonStyle { // 按钮显示风格定义
						background: Rectangle {
							color: control.pressed ? "gray" : "#7fb7ed"
							radius: 25
							border.color: "#ffffff"

							border.width: 1
						}
						label: Label { // 按键标签为"搜索"
							text: qsTr("搜索")
							color: "#ffffff"
							font.pixelSize: 20
							horizontalAlignment: Text.AlignHCenter
							verticalAlignment: Text.AlignVCenter
						}
					}
				}
			}

			Rectangle { // 类别选择设置（歌曲、串烧、电影）
				CheckBox { // 复选框：歌曲
					id: checkBoxSong
					x: 75
					y: 392
					width: 35
					height: 35
					//text: qsTr("歌曲")
					checked: true // 默认选择"歌曲"

					style:CheckBoxStyle {
						label: Label { // 按键标签为"选择"
							text: qsTr("歌曲")
							color: "#ffffff"
							font.pixelSize: 20
							horizontalAlignment: Text.AlignLeft
							verticalAlignment: Text.AlignBottom
						}
						indicator: Rectangle { // 指示样式
							implicitWidth: 35
							implicitHeight: 35
							border.width: 1
							border.color: "#ffffff"
							color:"#419af1"
							Image { // 选中时为红色小钩
								x: 2
								y: 2
								width: 30
								height: 30
								source: "images/g.png"
								visible: checkBoxSong.checked;
							}
						}
						background: Rectangle { // 复选框背景
							border.color: "#ffffff"
							border.width: 1
							color: "#419af1"
						}
					}
				}

				CheckBox { // 复选框：串烧
					id: checkBoxSpun
					x: 169
					y: 392
					width: 35
					height: 35
					//text: qsTr("串烧")
					checked: false

					style:CheckBoxStyle {
						label: Label { // 按键标签为"选择"
							text: qsTr("串烧")
							color: "#ffffff"
							font.pixelSize: 20
							horizontalAlignment: Text.AlignLeft
							verticalAlignment: Text.AlignBottom
						}
						indicator: Rectangle { // 指示样式
							implicitWidth: 35
							implicitHeight: 35
							border.width: 1
							border.color: "#ffffff"
							color:"#419af1"
							Image { // 选中时为红色小钩
								x: 2
								y: 2
								width: 30
								height: 30
								source: "images/g.png"
								visible: checkBoxSpun.checked;
							}
						}
						background: Rectangle { // 复选框背景
							border.color: "#ffffff"
							border.width: 1
							color: "#419af1"
						}
					}
				}

				CheckBox { // 复选框：电影
					id: checkBoxMovie
					x: 263
					y: 392
					width: 35
					height: 35
					//text: qsTr("电影")
					checked: false

					style:CheckBoxStyle {
						label: Label { // 按键标签为"选择"
							text: qsTr("电影")
							color: "#ffffff"
							font.pixelSize: 20
							horizontalAlignment: Text.AlignLeft
							verticalAlignment: Text.AlignBottom
						}
						indicator: Rectangle { // 指示样式
							implicitWidth: 35
							implicitHeight: 35
							border.width: 1
							border.color: "#ffffff"
							color:"#419af1"
							Image { // 选中时为红色小钩
								x: 2
								y: 2
								width: 30
								height: 30
								source: "images/g.png"
								visible: checkBoxMovie.checked;
							}
						}
						background: Rectangle { // 复选框背景
							border.color: "#ffffff"
							border.width: 1
							color: "#419af1"
						}
					}
				}
			}

			Rectangle { // 搜索类别设置：可按歌曲、歌手、其他方式搜索
				TextField { // "歌曲"文本输入
					id: textFieldSong
					x: 74
					y: 28
					width: 260
					height: 45
					text: qsTr("爱你一万年")
					activeFocusOnPress: true
					font.pixelSize: 20
					horizontalAlignment: Text.AlignHCenter  // 水平中心对齐
					verticalAlignment: Text.AlignVCenter     // 垂直中心对齐

					style: TextFieldStyle { // 文本框背景样式定义
						textColor: "#ffffff"
						background: Rectangle {
							radius: 10
							border.color: "#ffffff"
							border.width: 1
							color: "#419af1"
						}
					}

					Label { // 标签"歌曲"
						id: labelSong
						x: -65
						y: 0
						width: 60
						height: 45
						color: "#ffffff"
						text: qsTr("歌曲:")
						styleColor: "#ffffff"
						textFormat: Text.AutoText
						font.pixelSize: 20
						horizontalAlignment: Text.AlignRight
						verticalAlignment: Text.AlignVCenter
					}

					Button { // 清除按键"X"
						id: buttonSongDelete
						x: 227
						y: 12
						width: 25
						height: 25
						text: qsTr("")
						onClicked: textFieldSong.text = " "  // 点击"x"删除输入框内容
						visible: textFieldSong.text != " "

						Image { // 图片"X"背景
							x: 2
							y: 2
							width: 20
							height: 20
							source: "images/x.png"
							visible: !(buttonSongDelete.pressed) // 按键点击的时候不显示"X"符号
						}
						style: ButtonStyle { // 按钮显示风格定义
							background: Rectangle {
								color: "#6997c6"
								radius: 25
							}
						}
					}
				}

				TextField { // "歌手"文本输入
					id: textFieldSinger
					x: 75
					y: 102
					width: 260
					height: 45
					text: qsTr("卓依婷")
					font.pixelSize: 20
					horizontalAlignment: TextInput.AlignHCenter  // 水平中心对齐
					verticalAlignment:TextInput.AlignVCenter     // 垂直中心对齐

					style: TextFieldStyle { // 文本框背景样式定义
						textColor: "#ffffff"
						background: Rectangle {
							radius: 10
							border.color: "#ffffff"
							border.width: 1
							color: "#419af1"
						}
					}

					Label { // 标签"歌手"
						id: labelSonger
						x: -66
						y: 0
						width: 60
						height: 45
						color: "#ffffff"
						text: qsTr("歌手:")
						textFormat: Text.AutoText
						font.pixelSize: 20
						verticalAlignment: Text.AlignVCenter
						horizontalAlignment: Text.AlignRight
					}

					Button { // 清除按键"X"
						id: buttonSingerDelete
						x: 227
						y: 12
						width: 25
						height: 25
						text: qsTr("")
						onClicked: textFieldSinger.text = " "  // 点击"x"删除输入框内容
						visible: textFieldSinger.text != " "

						Image { // 图片"X"背景
							x: 2
							y: 2
							width: 20
							height: 20
							source: "images/x.png"
							visible: !(buttonSingerDelete.pressed) // 按键点击的时候不显示"X"符号
						}
						style: ButtonStyle { // 按钮显示风格定义
							background: Rectangle {
								color: "#6997c6"
								radius: 25
							}
						}
					}
				}

				TextField { // "其他"文本输入
					id: textFieldOthers
					x: 75
					y: 178
					width: 260
					height: 45
					text: qsTr("语种 版本 风格")
					font.pixelSize: 20
					horizontalAlignment: TextInput.AlignHCenter  // 水平中心对齐
					verticalAlignment:TextInput.AlignVCenter     // 垂直中心对齐

					style: TextFieldStyle { // 文本框背景样式定义
						textColor: "#ffffff"
						background: Rectangle {
							radius: 10
							border.color: "#ffffff"
							border.width: 1
							color: "#419af1"
						}

					}

					Label { // 标签"其他"
						id: labelOthers
						x: -66
						y: 0
						width: 60
						height: 45
						color: "#ffffff"
						text: qsTr("其他:")
						textFormat: Text.AutoText
						verticalAlignment: Text.AlignVCenter
						horizontalAlignment: Text.AlignRight
						styleColor: "#ffffff"
						font.pixelSize: 20
					}

					Button { // 清除按键"X"
						id: buttonOthersDelete
						x: 227
						y: 12
						width: 25
						height: 25
						text: qsTr("")
						onClicked: textFieldOthers.text = " "  // 点击"x"删除输入框内容
						visible: textFieldOthers.text != " "

						Image { // 图片"X"背景
							x: 2
							y: 2
							width: 20
							height: 20
							source: "images/x.png"
							visible: !(buttonOthersDelete.pressed) // 按键点击的时候不显示"X"符号
						}
						style: ButtonStyle { // 按钮显示风格定义
							background: Rectangle {
								color: "#6997c6"
								radius: 25
							}
						}
					}

					Button { // "选择"确认按钮
						id: buttonChoice
						x: 170
						y: 52
						width: 90
						height: 40
						text: qsTr("选择")
						opacity: 0.8
						style: ButtonStyle { // 按钮显示风格定义
							background: Rectangle {
								color: control.pressed ? "gray" : "#7fb7ed"
								radius: 25
								border.color: "#ffffff"
								border.width: 1
							}
							label: Label { // 按键标签为"选择"
								text: qsTr("选择")
								color: "#ffffff"
								font.pixelSize: 20
								horizontalAlignment: Text.AlignHCenter
								verticalAlignment: Text.AlignVCenter
							}
						}
					}
				}

				Label { // 标签类别
					id: labelClass
					x: 8
					y: 388
					width: 60
					height: 45
					color: "#ffffff"
					text: qsTr("类别:")
					styleColor: "#ffffff"
					textFormat: Text.AutoText
					verticalAlignment: Text.AlignVCenter
					horizontalAlignment: Text.AlignRight
					font.pixelSize: 20
				}
			}

			Rectangle { // 点击量设置
				TextField { // 点击量输入
					id: textFieldClick
					x: 75
					y: 283
					width: 260
					height: 45
					text: qsTr("1000")
					font.pixelSize: 20
					horizontalAlignment: Text.AlignHCenter  // 水平中心对齐
					verticalAlignment:Text.AlignVCenter     // 垂直中心对齐

					style: TextFieldStyle { // 文本框背景样式定义
						textColor: "#ffffff"
						background: Rectangle {
							radius: 10
							border.color: "#ffffff"
							border.width: 1
							color: "#419af1"
						}
					}

					Label { // 标签"点击"
						id: labelClick
						x: -66
						y: 0
						width: 60
						height: 45
						color: "#ffffff"
						text: qsTr("点击:")
						textFormat: Text.AutoText
						verticalAlignment: Text.AlignVCenter
						horizontalAlignment: Text.AlignRight
						styleColor: "#ffffff"
						font.pixelSize: 20
					}

					Button { // 清除按键"X"
						id: buttonClickDelete
						x: 227
						y: 12
						width: 25
						height: 25
						text: qsTr("")
						onClicked: textFieldClick.text = " "  // 点击"x"删除输入框内容
						visible: textFieldClick.text != " "

						Image { // 图片"X"背景
							x: 2
							y: 2
							width: 20
							height: 20
							source: "images/x.png"
							visible: !(buttonClickDelete.pressed) // 按键点击的时候不显示"X"符号
						}
						style: ButtonStyle { // 按钮显示风格定义
							background: Rectangle {
								color: "#6997c6"
								radius: 25
							}
						}
					}

					CheckBox { // 复选框点击量"大于"
						id: checkBoxGreater
						x: 94
						y: 56
						width: 35
						height: 35
						checked: true // 默认选择"大于"
						onClicked: checkBoxLess.checked = !(checkBoxGreater.checked) // 保证"大于"和"小于"只选一个

						style:CheckBoxStyle {
							label: Label { // 按键标签为"选择"
								text: qsTr("大于")
								color: "#ffffff"
								font.pixelSize: 20
								horizontalAlignment: Text.AlignLeft
								verticalAlignment: Text.AlignBottom
							}
							indicator: Rectangle { // 指示样式
								implicitWidth: 35
								implicitHeight: 35
								border.width: 1
								border.color: "#ffffff"
								color:"#419af1"
								Image { // 选中时为红色小钩
									x: 2
									y: 2
									width: 30
									height: 30
									source: "images/g.png"
									visible: checkBoxGreater.checked;
								}
							}
							background: Rectangle { // 复选框背景
								border.color: "#ffffff"
								border.width: 1
								color: "#419af1"
							}
						}
					}

					CheckBox { // 复选框点击量"小于"
						id: checkBoxLess
						x: 187
						y: 56
						width: 35
						height: 35
						checked: false
						onClicked: checkBoxGreater.checked  = !(checkBoxLess.checked) // 保证"大于"和"小于"只选一个

						style:CheckBoxStyle {
							label: Label { // 按键标签为"选择"
								text: qsTr("小于")
								color: "#ffffff"
								font.pixelSize: 20
								horizontalAlignment: Text.AlignLeft
								verticalAlignment: Text.AlignBottom
							}
							indicator: Rectangle { // 指示样式
								implicitWidth: 35
								implicitHeight: 35
								border.width: 1
								border.color: "#ffffff"
								color:"#419af1"
								Image { // 选中时为红色小钩
									x: 2
									y: 2
									width: 30
									height: 30
									source: "images/g.png"
									visible: checkBoxLess.checked;
								}
							}
							background: Rectangle { // 复选框背景
								border.color: "#ffffff"
								border.width: 1
								color: "#419af1"
							}
						}
					}
				}
			}
		}

		Rectangle { // 显示列表
			id: rectangleDisplayList
			x: 396
			y: 71
			width: 860
			height: 500
			color: "#419af1"
			radius: 10
			border.color: "#ffffff"
			border.width: 2
			property int page: 1  //页码

			Button { // 上一页按钮
				id: buttonUp
				x: 20
				y: 443
				width: 90
				height: 40
				//text: qsTr("上页")
				opacity: 1
				onClicked: { // 上翻页
					if (rectangleDisplayList.page > 1) {
						rectangleDisplayList.page--;
						listViewTable.positionViewAtIndex(8*(rectangleDisplayList.page - 1),ListView.Beginning);
					} else {
						listViewTable.positionViewAtIndex(8*(rectangleDisplayList.page - 1),ListView.Beginning);  // 8*(rectangleDisplayList.page)
					}
				}

				Image { // 图片背景
					x: 0
					y: 0
					width: 90
					height: 40
					source: buttonUp.pressed ? "images/p1.png" : "images/p.png"
				}
			}

			Button { // 下一页
				id: buttonDown
				x: 195
				y: 443
				width: 90
				height: 40
				//text: qsTr("下页")
				opacity: 1
				onClicked: { // 下翻页
					if (rectangleDisplayList.page < (listViewTable.count / 8)) {
						rectangleDisplayList.page++;
					}
					listViewTable.positionViewAtIndex(8*(rectangleDisplayList.page - 1),ListView.Beginning); // listViewTable.currentIndex + 8
				}

				Image { // 图片背景
					x: 0
					y: 0
					width: 90
					height: 40
					source: buttonDown.pressed ? "images/w1.png" : "images/w.png"
				}
			}

			Text { // 页号编码
				id: textTurnPage
				x: 124
				y: 448
				width: 60
				height: 30
				color: "#ffffff"
				text:  String(rectangleDisplayList.page) + "/" + String(rectangleDisplayList.integerGet(listViewTable.count / 8)) // 页码显示
				styleColor: "#000000"
				font.bold: false
				horizontalAlignment: Text.AlignHCenter
				verticalAlignment: Text.AlignVCenter
				font.pixelSize: 18
			}

			function integerGet(pt) { // 小数转为整数，用于页码显示
				var temp = 0;

				temp = pt % 1;
				if (temp > 0 ) {
					pt = (pt - temp) + 1;
				}
				return pt;
			}

			Button { // 反选按钮
				id: buttonInverse
				x: 425
				y: 443
				width: 90
				height: 40
				text: qsTr("反选")
				onClicked: {
					for (var i = 0 ; i < listModelsong.count ; ++i) { // 反选标记，true 和 false反转
						if (listModelsong.get(i).songSelected == "true") {
							listModelsong.get(i).songSelected = "false";
						} else {
							listModelsong.get(i).songSelected = "true";
						}
					}
				}

				Image { //  图片背景
					x: 0
					y: 0
					width: 90
					height: 40
					source: buttonInverse.pressed ? "images/s1.png" : "images/s.png"
				}
			}

			Button { // 全选按钮
				id: buttonCheckAll
				x: 575
				y: 443
				width: 90
				height: 40
				text: qsTr("全选")
				onClicked: {
					for (var i = 0 ; i < listModelsong.count ; ++i) {
						listModelsong.get(i).songSelected = "true";
					}
				}

				Image { // 图片背景
					x: 0
					y: 0
					width: 90
					height: 40
					source: buttonCheckAll.pressed ? "images/f1.png" : "images/f.png"
				}
			}

			Button { // 删除按钮
				id: buttonCancel
				x: 725
				y: 443
				width: 90
				height: 40
				onClicked: {
					for (var i = 0 ; i < listModelsong.count ; ++i) { // 循环删除选中的项目
						if (listModelsong.get(i).songSelected == "true") { // 判断是否选中
							listModelsong.remove(i,1); // 选中则删除
							i-- ;					   // 由于项目删除后index会变小1个，因此i-1保证索引位置正确
						}
					}
				}

				Image { // 图片背景
					x: 0
					y: 0
					width: 90
					height: 40
					source: buttonCancel.pressed ? "images/d1.png" : "images/d.png"
				}
			}

			GridView { // 数据显示及浏览框
				id: listViewTable
				x: 20
				y: 40
				width: 795
				height: 380
				clip: true
				cellHeight: 50
				cellWidth: 800
				//contentY: 50
				//interactive: true
				flow: GridView.FlowTopToBottom
				layoutDirection:Qt.LeftToRight
				//verticalLayoutDirection: ListView.BottomToTop

				model: listModelsong
				delegate: Item { // 显示格式定义
					id: displayFormat
					width: 800
					height: 50

					MouseArea { // 鼠标区域，点击切换选中状态
						id: mouseAreaClick
						anchors.fill: parent
						onClicked: {
							if (listModelsong.get(index).songSelected == "true") {  // 选中与否标记，true表示选中
								listModelsong.get(index).songSelected = "false";
								//checkBoxSelected.checked = false ;   !!!!信号处理器关联信号后，不可以对属性直接赋值，这样会导致信号和槽断连，可以通过bind重新连接
							} else {  // 选中与否标记，false表示不选中
								listModelsong.get(index).songSelected = "true";
								//checkBoxSelected.checked = true ;
							}
						}
					}

					Image { // 图片背景
						x: 0
						y: 0
						width: 800
						height: 50
						source: "images/l.png"
					}

					CheckBox { // 复选框选择
						id: checkBoxSelected
						x: 2
						y: 10
						width: 35
						height: 35
						checked: listModelsong.get(index).songSelected == "true"  //model 定义是否选中
						onCheckedChanged: {
							console.log("$$$",index,checkBoxSelected.checked);
						}

						onClicked: {
							if (listModelsong.get(index).songSelected == "true") {  // 选中与否标记，true表示选中
								listModelsong.get(index).songSelected = "false";
								//checkBoxSelected.checked = false ;   !!!!信号处理器关联信号后，不可以对属性直接赋值，这样会导致信号和槽断连，可以通过bind重新连接
							} else {  // 选中与否标记，false表示不选中
								listModelsong.get(index).songSelected = "true";
								//checkBoxSelected.checked = true ;
							}
						}

						style:CheckBoxStyle { // 复选框样式
							indicator: Rectangle { // 指示器显示的样式
								implicitWidth: 35
								implicitHeight: 35
								border.width: 1
								border.color: "#ffffff"
								color:"#419af1"
								Image { // 选中时为红色小钩
									id:imageCheck
									x: 2
									y: 2
									width: 30
									height: 30
									source: "images/g.png"
									visible: checkBoxSelected.checked
									//listModelsong.get(index).selected == "true" ? true : false
									//checkBoxSelected.checked
								}
							}
							background: Rectangle { // 复选框背景
								border.color: "#ffffff"
								border.width: 1
								color: "#419af1"
							}
						}
					}

					Item { // 字体显示格式
						Text {  // 歌曲名字
							id: textSongName
							x: 100
							y: 25
							font.pixelSize: 20
							color: checkBoxSelected.checked ? "red" : "#ffffff"
							text: songName
							font.bold: false
							horizontalAlignment: Text.AlignHCenter
							verticalAlignment: Text.AlignBottom
						}
						Text {  // 歌手名字
							id: textSingerName
							x: 300
							y: 25
							font.pixelSize: 20
							color: checkBoxSelected.checked ? "red" : "yellow"
							text: singerName
							font.bold: false
							horizontalAlignment: Text.AlignHCenter
							verticalAlignment: Text.AlignBottom
						}
						Text {  // 语种名字
							id: textLanguageName
							x: 500
							y: 25
							font.pixelSize: 20
							color: checkBoxSelected.checked ? "red" :"#ffffff"
							text: language
							font.bold: false
							horizontalAlignment: Text.AlignHCenter
							verticalAlignment: Text.AlignBottom
						}
					}
				}
			}

			ListModel  { // 显示内容model
				id: listModelsong

				ListElement {
					songName: "爱你一万年1"
					singerName: "卓依婷"
					language: "国语"
					songSelected: "false"
				}
				ListElement {
					songName: "爱你一万年2"
					singerName: "卓依婷"
					language: "国语"
					songSelected: "false"
				}
				ListElement {
					songName: "爱你一万年3"
					singerName: "卓依婷"
					language: "国语"
					songSelected: "false"
				}
				ListElement {
					songName: "爱你一万年4"
					singerName: "卓依婷"
					language: "国语"
					songSelected: "false"
				}
				ListElement {
					songName: "爱你一万年5"
					singerName: "卓依婷"
					language: "国语"
					songSelected: "false"
				}
				ListElement {
					songName: "爱你一万年6"
					singerName: "卓依婷"
					language: "国语"
					songSelected: "false"
				}
				ListElement {
					songName: "爱你一万年7"
					singerName: "卓依婷"
					language: "国语"
					songSelected: "false"
				}
				ListElement {
					songName: "爱你一万年8"
					singerName: "卓依婷"
					language: "国语"
					songSelected: "false"
				}
				ListElement {
					songName: "爱你一万年9"
					singerName: "卓依婷"
					language: "国语"
					songSelected: "false"
				}
				ListElement {
					songName: "爱你一万年10"
					singerName: "卓依婷"
					language: "国语"
					songSelected: "false"
				}
				ListElement {
					songName: "爱你一万年11"
					singerName: "卓依婷"
					language: "国语"
					songSelected: "false"
				}
				ListElement {
					songName: "爱你一万年12"
					singerName: "卓依婷"
					language: "国语"
					songSelected: "false"
				}
				ListElement {
					songName: "爱你一万年13"
					singerName: "卓依婷"
					language: "国语"
					songSelected: "false"
				}
				ListElement {
					songName: "爱你一万年14"
					singerName: "卓依婷"
					language: "国语"
					songSelected: "false"
				}
				ListElement {
					songName: "爱你一万年15"
					singerName: "卓依婷"
					language: "国语"
					songSelected: "false"
				}
				ListElement {
					songName: "爱你一万年16"
					singerName: "卓依婷"
					language: "国语"
					songSelected: "false"
				}
				ListElement {
					songName: "爱你一万年17"
					singerName: "卓依婷"
					language: "国语"
					songSelected: "false"
				}

			}

		}
	}
}


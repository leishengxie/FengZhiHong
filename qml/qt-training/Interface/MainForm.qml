/******************************************************************************
**
** @file
** main.qml
** @brief
** 迅歌主界面
** @author
** wangrm
** @date
** 2017-3-28
**
******************************************************************************/
import QtQuick 2.5
import QtQuick 2.7
import QtQuick.Window 2.2
import QtQml.Models 2.2
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQml.Models 2.2
import QtQml 2.2
import QtQuick.Controls.styles 1.4
//import com.test.QObject 1.0

Rectangle { // 点歌界面设置
//    property alias mouseArea: mouseArea
//    property alias textEdit: textEdit

    MouseArea {
        id: mouseArea
        anchors.fill: parent
    }

	Image { // 主背景图片
		id: imgBackground
		source: "/3.jpg"
		width: 1280
		height: 720
	}

	Rectangle { // 歌曲框样式设置
		id: rectSearch
		color: "#419af1"
		width: 360
		height: 480
		border.color: "#dcedf4" // 边框颜色
		border.width: 2 // 边框的宽度
		anchors.left: parent.left
		anchors.leftMargin: 15
		anchors.top: parent.top
		anchors.topMargin: 100
		radius: 15
		clip: true

		RowLayout { // 歌曲并排
			id: rowLayout
			anchors.top: parent.top
			anchors.topMargin: 19
			anchors.left: parent.left
			anchors.leftMargin: 10
			spacing: 1

			Text { // id 名
				text: "歌曲:"
				font.pixelSize: 20
				color: "#dfe8f9"
				font.bold: true
				anchors.top: parent.top
				anchors.topMargin: 8
			}

			TextField { // 歌曲输入框
				id: textFind
				width: 280
				height: 44
				font.pixelSize: 20
				color: "#ccdef8"
				maximumLength: 12
				horizontalAlignment: parent.AlignHCenter
				verticalAlignment:  parent.AlignVCenter

				background : Rectangle { // 输入框样式
					id: rectSong
					width: 280
					height: 44
					radius: 5
					color: "#419af1"
					border.color: "#ccdef8"
					border.width: 1
					anchors.top: parent.top
					anchors.topMargin: -5

					MouseArea {
						anchors.fill: parent
						onClicked: textFind.focus = true
					}
				}
			}
		}

		RowLayout { // 歌星列并排
			id: rowLayoutStar
			anchors.top: parent.top
			anchors.topMargin: 80
			anchors.left: parent.left
			anchors.leftMargin: 10
			spacing: 1　// 左右间距

			Text { // id名
				text: "歌星:"
				font.pixelSize: 20
				color: "#dfe8f9"
				font.bold: true
				anchors.top: parent.top
				anchors.topMargin: 8
			}

			TextField { // 歌星列输入框
				id:textStar
				font.pixelSize: 20
				color: "#b3c7de"
				maximumLength: 11
				activeFocusOnPress: true

				background: Rectangle { // 输入框样式
					width: 280
					height: 44
					radius: 5
					color: "#419af1"
					border.color: "#ccdef8"
					border.width: 1
					anchors.top: parent.top
					anchors.topMargin: -5

					MouseArea {
						anchors.fill: parent
						onClicked: textStar.focus = true
					}
				}
			}
		}

		RowLayout { // 其它列横向排放
			id: rowLayoutOther
			anchors.top: parent.top
			anchors.topMargin: 143
			anchors.left: parent.left
			anchors.leftMargin: 10
			spacing: 1 // 左右间距

			Text { // id名
				text: "其它:"
				font.pixelSize: 20
				color: "#dfe8f9"
				font.bold: true // 加粗
				anchors.top: parent.top
				anchors.topMargin: 8
			}

			TextField { // 其它输入框
				id:textOther
				text: "  语种  版本  风格" // 默认内容
				font.pixelSize: 20
				color: "#b3c7de"
				maximumLength: 13

				background : Rectangle { // 背景样式
					width: 280
					height: 44
					radius: 5 // 圆角
					color: "#419af1"
					border.color: "#ccdef8"
					border.width: 1
					anchors.top: parent.top
					anchors.topMargin: -5

					MouseArea {
						anchors.fill: parent
						onClicked: textOther.focus = true
					}
				}
			}
		}

		Rectangle { // 选择按钮样式
			id: btnSelect
			width: 91
			height: 40
			color: "#419af1"
			visible: true
			anchors.top: parent.top
			anchors.topMargin: 188
			anchors.right: parent.right
			anchors.rightMargin: 19

			Image { // 选择按钮背景图片
				id: imgSelectFirst
				width: 91
				height: 40
				source: "/select.png"
				anchors.centerIn: parent
			}

			MouseArea { // 设置点击效果
				anchors.fill: parent
				onContainsMouseChanged: btnSelect.state == 'clicked' ? btnSelect.state = "" : btnSelect.state = 'clicked' //　点击变灰色
			}

			states: [
				State {　// 设置点击效果
					name: "clicked"

					PropertyChanges { // 点击变灰色
						target: imgSelectFirst
						width: 87
						height: 37
					}
				}
			]
		}

		RowLayout { // 点击横向排放
			id: rowLayoutClick
			anchors.top: parent.top
			anchors.topMargin: 237
			anchors.left: parent.left
			anchors.leftMargin: 10
			spacing: 1 // 左右间距

			Text { // id名
				text: "点击:"
				font.pixelSize: 20
				color: "#dfe8f9"
				font.bold: true // 加粗
				anchors.top: parent.top
				anchors.topMargin: 8 // 左右间距
			}

			TextField { // 点击输入框
				id:textClick
				font.pixelSize: 20 // 字体大小
				color: "#b3c7de"
				maximumLength: 11

				background : Rectangle { // 点击输入框背景图片设置
					width: 280
					height: 44
					radius: 5
					color: "#419af1"
					border.color: "#ccdef8"
					border.width: 1
					anchors.top: parent.top
					anchors.topMargin: -5

					MouseArea {
						anchors.fill: parent
						onClicked: textClick.focus = true
					}
				}
			}
		}

		RowLayout { // 大于/小于横向排放
			anchors.right: parent.right
			anchors.rightMargin: 21
			anchors.top: parent.top
			anchors.topMargin: 298
			spacing: 13

			Rectangle { // 大于复选框
				width: 25
				height: 25
				color: "#419aF1"
				border.width: 1
				border.color: "#bcdcfa"

				Image { // 大于复选框对号
					id: imgSelectBig
					anchors.top: parent.top
					anchors.topMargin: 3
					anchors.left: parent.left
					anchors.leftMargin: 1
					source: "/dui.png"
					sourceSize.width: 25
					sourceSize.height: 24
				}

				MouseArea { // 是否对号
					anchors.fill: parent

					onClicked: {

						imgSelectBig.source  == "" ? imgSelectBig.source = "/dui.png" : imgSelectBig.source = ""
						imgSelectSmall.source = ""
					}
				}
			}

			Text { // 复选框名
				text: "大于"
				font.pixelSize: 20
				color: "#e4effd"
				font.bold: true
				anchors.left: parent.left
				anchors.leftMargin: 30
			}

			Rectangle { // 小于复选框
				width: 25
				height: 25
				color: "#419aF1"
				border.width: 1
				border.color: "#bcdcfa"
				anchors.right: parent.right
				anchors.rightMargin: 45

				Image {　// 小于复选框对号
					id: imgSelectSmall
					anchors.top: parent.top
					anchors.topMargin: 3
					anchors.left: parent.left
					anchors.leftMargin: 1
					source: ""
					sourceSize.width: 25
					sourceSize.height: 24
				}

				MouseArea { // 是否对号
					anchors.fill: parent

					onClicked: {

						imgSelectSmall.source == "" ? imgSelectSmall.source = "/dui.png" : imgSelectSmall.source = ""
						imgSelectBig.source = ""
					}
				}
			}

			Text { // 复选框名
				text: "小于"
				font.pixelSize: 20
				color: "#e4effd"
				font.bold: true
			}
		}

		Text { // id名
			text: "类别:"
			font.pixelSize: 20
			color: "#dfe8f9"
			font.bold: true // 加粗
			anchors.top: parent.top
			anchors.topMargin: 347
			anchors.left: parent.left
			anchors.leftMargin: 10
		}

		RowLayout { // 复选框横向排放
			id: rowLayoutSong
			anchors.top: parent.top
			anchors.topMargin: 345
			anchors.left: parent.left
			anchors.leftMargin: 71
			spacing: 17

			Rectangle { // 歌曲类型复选框
				width: 25
				height: 25
				color: "#419aF1"
				border.width: 1
				border.color: "#bcdcfa"

				Image { // 类别复选框
					id: imgSelectSkewer
					anchors.top: parent.top
					anchors.topMargin: 3
					anchors.left: parent.left
					anchors.leftMargin: 1
					source: "/dui.png"
					sourceSize.width: 25
					sourceSize.height: 24
				}

				MouseArea { // 是否对号
					anchors.fill: parent

					onClicked: imgSelectSkewer.source == "" ? imgSelectSkewer.source = "/dui.png" : imgSelectSkewer.source = ""
				}
			}

			Text { // 复习框名
				text: "歌曲"
				font.pixelSize: 20
				color: "#e4effd"
				font.bold: true
				anchors.left: parent.left
				anchors.leftMargin: 30
			}

			Rectangle { // 串烧复选框
				id: rectSkewer
				width: 25
				height: 25
				color: "#419aF1"
				border.width: 1
				border.color: "#bcdcfa"

				Image { // 串烧复选框对号
					id: imgSelect
					anchors.top: parent.top
					anchors.topMargin: 3
					anchors.left: parent.left
					anchors.leftMargin: 1
					source: ""
					sourceSize.width: 25
					sourceSize.height: 24
				}

				MouseArea { // 是否对号
					anchors.fill: parent

					onClicked: imgSelect.source == "" ? imgSelect.source = "/dui.png" : imgSelect.source = ""
				}
			}

			Text { // 复选框名
				text: "串烧"
				font.pixelSize: 20
				color: "#e4effd"
				font.bold: true
				anchors.left: parent.left
				anchors.leftMargin: 126
			}

			Rectangle { // 电影复选框
				id: rctFilm
				width: 25
				height: 25
				color: "#419aF1"
				border.width: 1
				border.color: "#bcdcfa"

				Image { // 电影复选框对号
					id: imgSelectFilm
					anchors.top: parent.top
					anchors.topMargin: 3
					anchors.left: parent.left
					anchors.leftMargin: 1
					source: ""
					sourceSize.width: 25
					sourceSize.height: 24
				}

				MouseArea { // 是否对号
					anchors.fill: parent

					onClicked: imgSelectFilm.source == "" ? imgSelectFilm.source = "/dui.png" : imgSelectFilm.source = ""
				}
			}

			Text { // 复选框名
				text: "电影"
				font.pixelSize: 20
				color: "#e4effd"
				font.bold: true
				anchors.left: parent.left
				anchors.leftMargin: 224
			}
		}

		RowLayout { // 按钮横向排放
			anchors.left: parent.left
			anchors.leftMargin: 10 // 左边距
			anchors.bottom: parent.bottom
			anchors.bottomMargin: 10 // 上边距
			spacing: 31

			Rectangle { // 清空按钮样式
				id: btnClear
				width: 91
				height: 40
				color: "#419af1"
				visible: true

				Image { // 清空按钮背景图片
					id: imgClear
					width: 91
					height: 40
					source: "/delete.png"
					anchors.centerIn: parent
				}

				MouseArea { // 设置点击效果
					anchors.fill: parent
					onContainsMouseChanged: btnClear.state == 'clicked' ? btnClear.state = "" : btnClear.state = 'clicked' //　点击变灰色

					onClicked: {
						textFind.text = ""
						textStar.text = ""
						textOther.text = ""
						textClick.text = ""
						imgSelectBig.source  = ""
						imgSelectSmall.source = ""
						imgSelectSkewer.source = ""
						imgSelect.source = ""
						imgSelectFilm.source = ""
					}
				}

				states: [
					State {　// 设置点击效果
						name: "clicked"

						PropertyChanges { // 点击变灰色
							target: imgClear
							width: 87
							height: 37
						}
					}
				]
			}

			Rectangle { // 回删按钮样式
				id: btnDelete
				width: 91
				height: 40
				color: "#419af1"
				visible: true

				Image { // 回删按钮背景图片
					id: imgDelete
					width: 91
					height: 40
					source: "/delete1.png"
					anchors.centerIn: parent
				}

				MouseArea { // 设置点击效果
					anchors.fill: parent
					onContainsMouseChanged: btnDelete.state == 'clicked' ? btnDelete.state = "" : btnDelete.state = 'clicked' //　点击变灰色
					onClicked: {
						var strText = textFind.text;
						strText = strText.substring(0, strText.length - 1);
						textFind.text = strText
					}
				}

				states: [
					State {　// 设置点击效果
						name: "clicked"

						PropertyChanges { // 点击变灰色
							target: imgDelete
							width: 87
							height: 37
						}
					}
				]
			}

			Rectangle { // 搜索按钮样式
				id: btnSearch
				width: 91
				height: 40
				color: "#419af1"
				visible: true

				Image { // 搜索按钮背景图片
					id: imgSearch
					width: 91
					height: 40
					source: "/search.png"
					anchors.centerIn: parent
				}

				MouseArea { // 设置点击效果
					anchors.fill: parent
					onContainsMouseChanged: btnSearch.state == 'clicked' ? btnSearch.state = "" : btnSearch.state = 'clicked' //　点击变灰色
					onClicked: textFind.text.search();
				}

				states: [
					State {　// 设置点击效果
						name: "clicked"

						PropertyChanges { // 点击变灰色
							target: imgSearch
							width: 87
							height: 37
						}
					}
				]
			}
		}
	}

	Rectangle { // 类型选择框
		id: type
		width: 860
		height: 480
		color: "#419af1"
		border.color: "#dcedf4" // 边框颜色
		border.width: 2
		anchors.left: parent.left
		anchors.leftMargin: 387
		anchors.top: parent.top
		anchors.topMargin: 100
		radius: 15 // 圆角

		Image { // 插入分割线
			id: imgSplitVision
			width: 5
			height: 460
			source: "/fenge.png"
			anchors.left: parent.left
			anchors.leftMargin: 220
			anchors.top: parent.top
			anchors.topMargin: 3
		}

		Image { // 插入分割线
			id: imgSplitLanguage
			width: 5
			height: 460
			source: "/fenge.png"
			anchors.left: parent.left
			anchors.leftMargin: 443
			anchors.top: parent.top
			anchors.topMargin: 3
		}

		Image { // 插入分割线
			id: imgSplitStyle
			width: 5
			height: 460
			source: "/fenge.png"
			anchors.left: parent.left
			anchors.leftMargin: 667
			anchors.top: parent.top
			anchors.topMargin: 3
		}

		RowLayout { // 设置类型种类横向排放
			anchors.left: parent.left
			anchors.leftMargin: 85
			anchors.top: parent.top
			anchors.topMargin: 20
			spacing:  170

			Text { // "版本"字体设置
				id: labelEdition
				text: "版本"
				font.pixelSize: 25
				font.bold: true // 加粗
				color: "#f7f430"
			}

			Text { // '语种'字体设置
				id: textLanguage
				text: "语种"
				font.pixelSize: 25
				font.bold: true
				color: "#f7f430"
			}

			Text { // “风格”字体设置
				id: textMystyle
				text: "风格"
				font.pixelSize: 25
				font.bold: true
				color: "#f7f430"
			}
		}

		Rectangle { // 版本内容
			id: rectFirst
			width: 178
			height: 356
			anchors.left: parent.left
			anchors.leftMargin: 25
			anchors.top: parent.top
			anchors.topMargin: 60
			color: "#419af1"
			clip: true

			Image { // 列表背景图片
				id:imgListBackground
				width: 178
				height: 356
				source: "/background.png"
			}

			ListView { // 版本列表
				id: listPage
				model: modelTest
				width: 178
				height: 356
				spacing: 25
				anchors.top: parent.top
				anchors.topMargin: 10
				highlight: highlight
				keyNavigationWraps: true

				delegate: Rectangle { // 点击列表变色
					id: wrapper
					height: 20
					width: parent.width
					color: "transparent"

					Text { // 定义列表内容
						id: contactInfo
						font.pixelSize: 20
						font.bold: true
						text: name
						color: wrapper.ListView.isCurrentItem ? "#c8446c" : "#f2f6f9" // 当前颜色
						anchors.centerIn:  parent
					}

					MouseArea { // 点击效果
						anchors.fill: parent

						onClicked: wrapper.ListView.view.currentIndex = index // 点击变色
					}
				}
			}
		}

		Rectangle { // 语种内容
			id: rectSecond
			width: 178
			height: 356
			anchors.left: parent.left
			anchors.leftMargin: 244
			anchors.top: parent.top
			anchors.topMargin: 60
			color: "#419af1"
			clip: true

			Image { // 列表背景图片
				id:imgLanguageBackground
				width: 178
				height: 356
				source: "/background.png"
			}

			ListView { // 语种列表
				id: listLanguage
				model: modelTest
				width: 178
				height: 356
				spacing: 25
				highlight: highlight
				anchors.top: parent.top
				anchors.topMargin: 10

				delegate: Rectangle { // 点击列表变色
					id: wrapperLanguage
					height: 20
					width: parent.width
					color: "transparent"
					clip: true

					Text { // 定义列表内容
						id: contactInfoLanguage
						font.pixelSize: 20
						font.bold: true
						text: test
						color: wrapperLanguage.ListView.isCurrentItem ? "#c8446c" : "#f2f6f9" // 当前颜色
						anchors.centerIn:  parent
					}

					MouseArea { // 点击效果
						anchors.fill: parent

						onClicked: {
							wrapperLanguage.ListView.view.currentIndex = index // 点击变色
						}
					}
				}
			}
		}

		Rectangle { // 风格内容
			id: rctThird
			width: 178
			height: 356
			anchors.left: parent.left
			anchors.leftMargin: 467
			anchors.top: parent.top
			anchors.topMargin: 60
			color: "#419af1"
			clip: true

			Image { // 列表背景图片
				id:imgStyleBackground
				width: 178
				height: 356
				source: "/background.png"
			}

			ListView { // 语种列表
				id: listMystyle
				model: modelTest
				width: 178
				height: 356
				spacing: 25
				anchors.top: parent.top
				anchors.topMargin: 10

				delegate: Rectangle { // 点击列表变色
					id: wrapperStyle
					height: 20
					width: parent.width
					color: "transparent"

					Text { // 定义列表内容
						id: contactInfoStyle
						font.pixelSize: 20
						font.bold: true
						text: myStyle
						color: wrapperStyle.ListView.isCurrentItem ? "#c8446c" : "#f2f6f9" // 当前颜色
						anchors.centerIn:  parent
					}

					MouseArea { // 点击效果
						anchors.fill: parent
						onClicked:  wrapperStyle.ListView.view.currentIndex = index // 点击变色
					}
				}
			}
		}

		RowLayout { // 第一个上/下翻页按钮
			anchors.left: parent.left
			anchors.leftMargin: 19
			anchors.bottom: parent.bottom
			anchors.bottomMargin: 10
			spacing: 0

			Rectangle { // 选择按钮样式
				id: btnFirst
				width: 91
				height: 40
				color: "#419af1"

				Image { // 上一页按钮背景图片
					id: imgFirst
					width: 91
					height: 40
					source: "qrc:/prev.png"
					anchors.centerIn: parent
				}

				MouseArea { // 设置点击效果
					anchors.fill: parent
					onContainsMouseChanged: btnFirst.state == 'clicked' ? btnFirst.state = "" : btnFirst.state = 'clicked' //　点击变灰色

					onClicked: {
						listPage.positionViewAtIndex(listPage.count-5,ListView.End )
					}
				}

				states: [ // 点击样式
					State {　// 设置点击效果
						name: "clicked"

						PropertyChanges { // 点击变灰色
							target: imgFirst
							width: 87
							height: 37
						}
					}
				]
			}

			Rectangle { // 第一个下一页按钮
				id: btnNext
				width: 91
				height: 40
				color: "#419af1"
				anchors.bottom: parent.bottom
				anchors.bottomMargin: -1

				Image { // 下一页按钮背景图片
					id: imgNext
					width: 91
					height: 39
					source: "qrc:/next.png"
					anchors.centerIn: parent
				}

				MouseArea { // 设置点击效果
					anchors.fill: parent
					onContainsMouseChanged: btnNext.state == 'clicked' ? btnNext.state = "" : btnNext.state = 'clicked' //　点击变灰色

					onClicked: {
						listPage.positionViewAtIndex(listPage.count-1,ListView.Beginning)
					}
				}

				states: [ // 点击样式
					State {　// 设置点击效果
						name: "clicked"

						PropertyChanges { // 点击变灰色
							target: imgNext
							width:87
							height: 37
						}
					}
				]
			}

		}

		RowLayout { // 第二个上/下翻页按钮
			anchors.left: parent.left
			anchors.leftMargin: 240
			anchors.bottom: parent.bottom
			anchors.bottomMargin: 10
			spacing: 0

			Rectangle { // 选择按钮样式
				id: btnPrevFirst
				width: 91
				height: 40
				color: "#419af1"

				Image { // 上一页按钮背景图片
					id: imgPrevFirst
					width: 91
					height: 40
					source: "qrc:/prev.png"
					anchors.centerIn: parent
				}

				MouseArea { // 设置点击效果
					anchors.fill: parent
					onContainsMouseChanged: btnPrevFirst.state == 'clicked' ? btnPrevFirst.state = "" : btnPrevFirst.state = 'clicked' //　点击变灰色

					onClicked: {
						listLanguage.positionViewAtIndex(listLanguage.count-5,ListView.End)
					}
				}

				states: [ //　点击按钮样式

					State {　// 设置点击效果
						name: "clicked"

						PropertyChanges { // 点击变灰色
							target: imgPrevFirst
							width: 87
							height: 37
						}
					}
				]
			}

			Rectangle { // 选择按钮样式
				id: btnNextFirst
				width: 91
				height: 40
				color: "#419af1"
				anchors.bottom: parent.bottom
				anchors.bottomMargin: -0.5

				Image {　// 下一页按钮背景图片
					id: imgNextFirst
					width: 91
					height: 40
					source: "qrc:/next.png"
					anchors.centerIn: parent
				}

				MouseArea { // 设置点击效果
					anchors.fill: parent
					onContainsMouseChanged: btnNextFirst.state == 'clicked' ? btnNextFirst.state = "" : btnNextFirst.state = 'clicked' //　点击变灰色

					onClicked: {
						listLanguage.positionViewAtIndex(listLanguage.count-5,ListView.Beginning)
					}
				}

				states: [ // 点击效果

					State {　// 设置点击效果
						name: "clicked"

						PropertyChanges { // 点击变灰色
							target: imgNextFirst
							width: 87
							height: 37
						}
					}
				]
			}
		}

		RowLayout {　// 第三个上一页按钮
			anchors.left: parent.left
			anchors.leftMargin: 465
			anchors.bottom: parent.bottom
			anchors.bottomMargin: 10
			spacing: 0

			Rectangle { // 选择按钮样式
				id: btnPrevSecond
				width: 91
				height: 40
				color: "#419af1"

				Image { // 上一页按钮背景图片
					id: imgPrevSecond
					width: 91
					height: 40
					source: "qrc:/prev.png"
					anchors.centerIn: parent
				}

				MouseArea { // 设置点击效果
					anchors.fill: parent
					onContainsMouseChanged: btnPrevSecond.state == 'clicked' ? btnPrevSecond.state = "" : btnPrevSecond.state = 'clicked' //　点击变灰色

					onClicked: {
						listMystyle.positionViewAtIndex(listMystyle.count-5,ListView.End)
					}
				}

				states: [ // 点击效果

					State {　// 设置点击效果
						name: "clicked"

						PropertyChanges { // 点击变灰色
							target: imgPrevSecond
							width: 87
							height: 37
						}
					}
				]
			}

			Rectangle { // 第三个下一页按钮样式
				id: btnNextSecond
				width: 91
				height: 40
				color: "#419af1"
				anchors.bottom: parent.bottom
				anchors.bottomMargin: -0.5

				Image { //下一页按钮背景图片
					id: imgNextSecond
					width: 91
					height: 40
					source: "/next.png"
					anchors.centerIn: parent
				}

				MouseArea { // 设置点击效果
					anchors.fill: parent
					onContainsMouseChanged: btnNextSecond.state == 'clicked' ? btnNextSecond.state = "" : btnNextSecond.state = 'clicked' //　点击变灰色

					onClicked: {
						listMystyle.positionViewAtIndex(listMystyle.count-1,ListView.Beginning)
					}
				}

				states: [　// 点击效果

					State {　// 设置点击效果
						name: "clicked"

						PropertyChanges { // 点击变灰色
							target: imgNextSecond
							width: 87
							height: 37
						}
					}
				]
			}
		}


		ColumnLayout { // 最右排按钮排列
			anchors.right: parent.right
			anchors.rightMargin: 45
			anchors.top: parent.top
			anchors.topMargin: 110
			spacing:  80

			Rectangle { // 清空按钮样式
				id: btnClearRight
				width: 91
				height: 40
				color: "#419af1"
				visible: true

				Image { //　清空按钮背景图片
					id: imgClearAll
					width: 91
					height: 40
					source: "/delete.png"
					anchors.centerIn: parent
				}

				MouseArea { // 点击清空所有内容
					anchors.fill: parent
					onContainsMouseChanged: btnClearRight.state == 'clicked' ? btnClearRight.state = "" : btnClearRight.state = 'clicked' //　点击变灰色

					onClicked: {
						listMystyle.wrapperStyle.listView.view.currentItem = 0
					}

				}

				states: [
					State {　// 设置点击效果
						name: "clicked"

						PropertyChanges { // 点击变灰色
							target: imgClearAll
							width: 87
							height: 37
						}
					}
				]
			}

			Rectangle { // 搜索按钮样式
				id: btnSearchRight
				width: 91
				height: 40
				color: "#419af1"
				visible: true

				Image {　// 搜索按钮背景图片
					id: imgSearchRight
					width: 91
					height: 40
					source: "/search.png"
					anchors.centerIn: parent
				}
				MouseArea { // 设置点击效果
					anchors.fill: parent
					onContainsMouseChanged: btnSearchRight.state == 'clicked' ? btnSearchRight.state = "" : btnSearchRight.state = 'clicked' //　点击变灰色
				}

				states: [

					State {　// 设置点击效果
						name: "clicked"

						PropertyChanges { // 点击变灰色
							target: imgSearchRight
							width: 87
							height: 37
						}
					}
				]
			}

			Rectangle { // 选择按钮样式
				id: btnReturn
				width: 91
				height: 40
				color: "#419af1"
				visible: true

				Image { //　返回按钮背景图片
					id: imgReturn
					width: 91
					height: 40
					source: "/return.png"
					anchors.centerIn: parent
				}

				MouseArea { // 设置点击效果
					anchors.fill: parent
					onContainsMouseChanged: btnReturn.state == 'clicked' ? btnReturn.state = "" : btnReturn.state = 'clicked' //　点击变灰色
				}

				states: [
					State {　// 设置点击效果
						name: "clicked"

						PropertyChanges { // 点击变灰色
							target: imgReturn
							width: 87
							height: 37
						}
					}
				]
			}
		}

		ListModel { // 列表内容
			id: modelTest

			ListElement { // 列表内容列出
				name: "情歌对唱"
				test: " 国语"
				myStyle: "演唱会"

			}

			ListElement { // 列表内容列出
				name: "情歌对唱"
				test: "闽南语"
				myStyle: " 现场"

			}

			ListElement { // 列表内容列出
				name: "情歌对唱"
				test:  " 粤语"
				myStyle: " MTV"

			}

			ListElement { // 列表内容列出
				name: "情歌对唱"
				test:  " 英语"
				myStyle: " 摇滚"

			}

			ListElement { // 列表内容列出
				name: "情歌对唱"
				test:  " 日语"
				myStyle: " 轻柔"

			}
			ListElement { // 列表内容列出
				name: "情歌对唱"
				test:  " 法语"
				myStyle: " 经典"

			}

			ListElement { // 列表内容列出
				name: "情歌对唱"
				test:  " 泰语"
				myStyle: " 温和"

			}

			ListElement { // 列表内容列出
				name: "情歌对唱"
				test:  " 韩语"
				myStyle: " 和声"

			}

			ListElement { // 列表内容列出
				name: "情歌对唱"
				test:  " 日语"
				myStyle: " 轻柔"

			}

			ListElement { // 列表内容列出
				name: "情歌对唱"
				myStyle: ""
			}

			ListElement { // 列表内容列出
				name: "情歌对唱"
				myStyle: ""
			}

			ListElement { // 列表内容列出
				name: ""
				myStyle: ""
			}
		}
	}

	Rectangle { // 其他按钮清除输入框内容
		id: rctDeleteOther
		width: 35
		height: 35
		anchors.left: parent.left
		anchors.leftMargin: 317
		anchors.top: parent.top
		anchors.topMargin: 241
		visible: textOther.text.length != 0

		Image { // 插入叉叉小圆框
			id: imgCleanSong
			source: "/x.png"
			width: 35
			height: 35
		}

		MouseArea { // 设置点击效果
			id: mouseBtn
			anchors.fill: parent
			onClicked: {
				textOther.text = "";
			}
		}
	}

	Rectangle { // 歌星按钮清除输入框内容
		id: rectDeleteStar
		width: 35
		height: 35
		anchors.left: parent.left
		anchors.leftMargin: 317
		anchors.top: parent.top
		anchors.topMargin: 180
		visible: textStar.text.length != 0

		Image { // 其它 插入叉叉小圆框
			id: imgClearSecond
			source: "/x.png"
			width: 35
			height: 35
		}

		MouseArea { // 设置点击效果
			id: mouseBtnOther
			anchors.fill: parent
			onClicked: {
				textClick.text = "";
			}
		}
	}

	Rectangle { // 歌曲按钮清除输入框内容
		id: rctDeleteName
		width: 35
		height: 35
		anchors.left: parent.left
		anchors.leftMargin: 317
		anchors.top: parent.top
		anchors.topMargin: 119
		visible: textFind.text.length != 0

		Image { // 插入小叉叉
			id: imgClean
			source: "/x.png"
			width: 35
			height: 35
		}

		MouseArea { // 设置点击效果
			id: mouseBtnSong
			anchors.fill: parent

			onClicked: {
				textFind.text = "";
			}
		}
	}

	Rectangle { // 点击按钮清空输入框
		id: rctDeleteClick
		width: 35
		height: 35
		anchors.left: parent.left
		anchors.leftMargin: 317
		anchors.top: parent.top
		anchors.topMargin: 336
		visible: textClick.text.length != 0

		Image { // 插入错号小圆框
			id: imgClearClick
			source: "/x.png"
			width: 35
			height: 35
		}

		MouseArea { // 设置点击效果
			id: mouseBtnClick
			anchors.fill: parent
			onClicked: {
				textClick.text = "";
			}
		}
	}
}

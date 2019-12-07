#pragma once

#include "ui_GBG.h"
#include <QFileDialog>

#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <QToolBar>
#include <QAction>
#include <QImage>
#include <qdebug.h>
#include <QLabel>
#include <QMessageBox>
#include <QTextStream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class GBG : public QMainWindow
{
	Q_OBJECT

public:
	GBG(QWidget *parent = Q_NULLPTR);

private:
	Ui::GBGClass ui;

	//QToolBar* toolbar_file_;
//QAction* action_open_;
	QImage pic;//保存读取的图片
	QString image_name_;//图片路径名
	bool openFlag = false;//打开图片成果的标志
	QString result;//判断结果
	bool flag1 = false;//调试用，转化成灰度图标志

	QImage cvMat2QImage(const cv::Mat);
	cv::Mat QImage2cvMat(QImage& image);


public slots:
	void OpenPic();//打开图片
	void SaveText();//保存信息
	void click_button();//按下按钮，开始识别
};

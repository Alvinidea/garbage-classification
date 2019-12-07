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
	QImage pic;//�����ȡ��ͼƬ
	QString image_name_;//ͼƬ·����
	bool openFlag = false;//��ͼƬ�ɹ��ı�־
	QString result;//�жϽ��
	bool flag1 = false;//�����ã�ת���ɻҶ�ͼ��־

	QImage cvMat2QImage(const cv::Mat);
	cv::Mat QImage2cvMat(QImage& image);


public slots:
	void OpenPic();//��ͼƬ
	void SaveText();//������Ϣ
	void click_button();//���°�ť����ʼʶ��
};

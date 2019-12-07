#include "GBG.h"
#include "Predict.h"


GBG::GBG(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	QToolBar* tbar = addToolBar(tr("Tool"));
	tbar->setMovable(false);//工具栏不可移动
	tbar->setIconSize(QSize(20, 20));//设置动作图标的尺寸
	tbar->setStyleSheet("background-color:rgb(199,237,204)");//背景色

	QAction* openAction = new QAction(tr("&Open"), this);//打开动作
	openAction->setIcon(QIcon(":/QtGuiApplication1/Resources/images/open.png"));//图标
	openAction->setShortcut(QKeySequence(tr("Ctrl+O")));//热键
	openAction->setStatusTip(tr(u8"打开一张图片"));
	tbar->addAction(openAction);//添加到工具栏

	QAction* saveAction = new QAction(tr("&Save"), this);//打开动作
	saveAction->setIcon(QIcon(":/QtGuiApplication1/Resources/images/save.png"));//图标
	saveAction->setShortcut(QKeySequence(tr("Ctrl+S")));//热键
	saveAction->setStatusTip(tr(u8"保存分类信息"));
	tbar->addAction(saveAction);//添加到工具栏


	//连接信号与槽
	connect(openAction, SIGNAL(triggered()), this, SLOT(OpenPic()));
	connect(saveAction, SIGNAL(triggered()), this, SLOT(SaveText()));
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(click_button()));

	QPalette palette;
	palette.setColor(QPalette::Background, QColor(255, 255, 255));
	ui.label_img->setAutoFillBackground(true);//背景填充
	ui.label_img->setPalette(palette);
}

//只保存当前图片的分类信息，保存到test.txt文件下
void GBG::SaveText()
{
	QFile myfile("test.txt");//创建一个输出文件的文档

	if (myfile.open(QFile::WriteOnly | QIODevice::Append))//注意WriteOnly是往文本中写入的时候用，ReadOnly是在读文本中内容的时候用
	{
		QTextStream out(&myfile);
		out << ui.textBrowser->toPlainText() << endl; //转化成纯文本
		myfile.close();
	}
	QMessageBox::information(this,
		tr(u8"保存信息"),
		tr(u8"保存信息成功!"));
}

void GBG::click_button()
{
	if (openFlag)
	{
		cv::Mat img = QImage2cvMat(pic);



		/*
		调用垃圾分类部分，返回一个string

		result = ....
		ui.textBrowser->setText(result);
		*/
		Garbage_Predict GBP;
		//vector<string>* olist =  GBP.getOutStringList(img);
		vector<string>* olist = GBP.getOutStringList(image_name_.toStdString());

		if (!flag1)
		{
			cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
			flag1 = true;
		}

		pic = cvMat2QImage(img);
		ui.label_img->setPixmap(QPixmap::fromImage(pic));
		ui.label_img->show();
		string out = (*olist)[1];
		ui.textBrowser->setText(QString::fromStdString(out));
	}
	else
		ui.textBrowser->setText(u8"请先打开一张图片！");
}

void GBG::OpenPic()
{
	image_name_ = QFileDialog::getOpenFileName(this,
		QStringLiteral("选择图片"),
		"",
		QStringLiteral("文件类型 (*.png *.jpg *.bmp)"));
	if (image_name_ != NULL)
	{
		pic.load(image_name_);
		openFlag = true;
		//pixmap.scaled(ui.label_img->size(), Qt::KeepAspectRatio);

		//ui.label_img->setPixmap(pixmap.scaledToWidth(600));
		//ui.label_img->resize(ui.widget->size());

		ui.label_img->setScaledContents(true);

		ui.label_img->setPixmap(QPixmap::fromImage(pic));
		ui.label_img->show();
	}
	else {
		QMessageBox::information(this,
			tr(u8"打开图像失败"),
			tr(u8"打开图像失败!"));
		return;
	}

}


QImage GBG::cvMat2QImage(const cv::Mat mat)
{
	// 8-bits unsigned, NO. OF CHANNELS = 1
	if (mat.type() == CV_8UC1)
	{
		QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
		// Set the color table (used to translate colour indexes to qRgb values)
		image.setColorCount(256);
		for (int i = 0; i < 256; i++)
		{
			image.setColor(i, qRgb(i, i, i));
		}
		// Copy input Mat
		uchar* pSrc = mat.data;
		for (int row = 0; row < mat.rows; row++)
		{
			uchar* pDest = image.scanLine(row);
			memcpy(pDest, pSrc, mat.cols);
			pSrc += mat.step;
		}
		return image;
	}
	// 8-bits unsigned, NO. OF CHANNELS = 3
	else if (mat.type() == CV_8UC3)
	{
		// Copy input Mat
		const uchar* pSrc = (const uchar*)mat.data;
		// Create QImage with same dimensions as input Mat
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
		return image.rgbSwapped();
	}
	else if (mat.type() == CV_8UC4)
	{

		// Copy input Mat
		const uchar* pSrc = (const uchar*)mat.data;
		// Create QImage with same dimensions as input Mat
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
		return image.copy();
	}
	else
	{
		//qDebug() << "ERROR: Mat could not be converted to QImage.";
		return QImage();
	}
	return QImage();
}
cv::Mat GBG::QImage2cvMat(QImage& image)
{
	cv::Mat mat;
	//qDebug() << image.format();
	switch (image.format())
	{
	case QImage::Format_ARGB32:
	case QImage::Format_RGB32:
	case QImage::Format_ARGB32_Premultiplied:
		mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
		break;
	case QImage::Format_RGB888:
		mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
		cv::cvtColor(mat, mat, cv::COLOR_BGR2RGB);
		break;
	case QImage::Format_Indexed8:
		mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
		break;
	default:
		qDebug() << "ERROR: QImage could not be converted to Mat.";

	}
	return mat;
}
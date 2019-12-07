#include "GBG.h"
#include "Predict.h"


GBG::GBG(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	QToolBar* tbar = addToolBar(tr("Tool"));
	tbar->setMovable(false);//�����������ƶ�
	tbar->setIconSize(QSize(20, 20));//���ö���ͼ��ĳߴ�
	tbar->setStyleSheet("background-color:rgb(199,237,204)");//����ɫ

	QAction* openAction = new QAction(tr("&Open"), this);//�򿪶���
	openAction->setIcon(QIcon(":/QtGuiApplication1/Resources/images/open.png"));//ͼ��
	openAction->setShortcut(QKeySequence(tr("Ctrl+O")));//�ȼ�
	openAction->setStatusTip(tr(u8"��һ��ͼƬ"));
	tbar->addAction(openAction);//��ӵ�������

	QAction* saveAction = new QAction(tr("&Save"), this);//�򿪶���
	saveAction->setIcon(QIcon(":/QtGuiApplication1/Resources/images/save.png"));//ͼ��
	saveAction->setShortcut(QKeySequence(tr("Ctrl+S")));//�ȼ�
	saveAction->setStatusTip(tr(u8"���������Ϣ"));
	tbar->addAction(saveAction);//��ӵ�������


	//�����ź����
	connect(openAction, SIGNAL(triggered()), this, SLOT(OpenPic()));
	connect(saveAction, SIGNAL(triggered()), this, SLOT(SaveText()));
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(click_button()));

	QPalette palette;
	palette.setColor(QPalette::Background, QColor(255, 255, 255));
	ui.label_img->setAutoFillBackground(true);//�������
	ui.label_img->setPalette(palette);
}

//ֻ���浱ǰͼƬ�ķ�����Ϣ�����浽test.txt�ļ���
void GBG::SaveText()
{
	QFile myfile("test.txt");//����һ������ļ����ĵ�

	if (myfile.open(QFile::WriteOnly | QIODevice::Append))//ע��WriteOnly�����ı���д���ʱ���ã�ReadOnly���ڶ��ı������ݵ�ʱ����
	{
		QTextStream out(&myfile);
		out << ui.textBrowser->toPlainText() << endl; //ת���ɴ��ı�
		myfile.close();
	}
	QMessageBox::information(this,
		tr(u8"������Ϣ"),
		tr(u8"������Ϣ�ɹ�!"));
}

void GBG::click_button()
{
	if (openFlag)
	{
		cv::Mat img = QImage2cvMat(pic);



		/*
		�����������ಿ�֣�����һ��string

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
		ui.textBrowser->setText(u8"���ȴ�һ��ͼƬ��");
}

void GBG::OpenPic()
{
	image_name_ = QFileDialog::getOpenFileName(this,
		QStringLiteral("ѡ��ͼƬ"),
		"",
		QStringLiteral("�ļ����� (*.png *.jpg *.bmp)"));
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
			tr(u8"��ͼ��ʧ��"),
			tr(u8"��ͼ��ʧ��!"));
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
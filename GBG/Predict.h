#pragma once
#pragma once
#include<opencv2\opencv.hpp>
#include<opencv2\dnn.hpp>
#include <io.h>
#include<opencv2/ml/ml.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/imgcodecs/imgcodecs.hpp>
#include<string>
#include <windows.h> 
#include <iostream>

using namespace std;
using namespace cv;

class Predict {

protected:
	size_t inWidth;				// ͼƬ��
	size_t inHeight;			// ͼƬ��
	string wait_predict_pic;	// ��Ԥ��ͼƬ ��ַ

	vector<string> *label;		// ��ǩ����
	int labelsize;				// ��ǩ��Ŀ

	cv::Mat img;
	cv::Mat blob;
	cv::Mat output;

	String model;				// DNNģ�ͣ�·���� // ML ģ�ʹ洢·�� 
	String pbtxt;				// DNNģ�������ļ���·����// ML ѵ��ͼƬ�洢·��
	dnn::Net net;				// ���� = cv::dnn::readNetFromTensorflow(weights, prototxt);

	float confidenceThreshold;	// ���Ŷ���ֵ
	vector<string> *outList;	// Ԥ����

public:
	Predict() {}

	Predict(size_t w, size_t h, string picloc)
	{
		inWidth = w;
		inHeight = h;
		wait_predict_pic = picloc;
	}

	// ���ôģ��
	virtual void setModel(string pb, string pbtx) = 0;

	virtual void setModel(string pb) = 0;

	// ��ȡ�ģ��
	virtual vector<string>* getModel() = 0;

	// ���ôģ�͵�����
	virtual void setNet() = 0;

	// ��ȡ�ģ�͵�����
	virtual dnn::Net * getNet() = 0;

	// ���ñ�ǩ��Ϣ
	virtual void setlabelList(vector<string> *labe) = 0;

	// ��ȡ��ǩ��Ϣ
	virtual vector<string> * getlabelList() = 0;

	// ��ȡͼƬλ��
	virtual string getPic() = 0;

	// ����ͼƬλ��
	virtual void setPic(String loc) = 0;


	virtual void preOp(string pb, Mat pic, size_t w, size_t h) = 0;

	// Ԥ�������   ͼƬ���� �Ҷȵȵ�
	virtual void preOp(size_t w, size_t h,
		string picloc,
		string pb,
		vector<string> *labe) = 0;

	// Ԥ�������   ͼƬ���� �Ҷȵȵ�
	virtual void preOp(
		size_t w, size_t h,
		string picloc,
		string pb) = 0;
	// ����ģ��Ԥ��
	virtual void predict() = 0;


	// ��ȡԤ���� ���±�
	virtual vector<string>* getOut() = 0;

	virtual Mat getMat() = 0;

	// ��ȡԤ����
	virtual vector<string>* getOutStringList(Mat pic) = 0;

	virtual vector<string>* getOutStringList(string pic)=0;
};

class Garbage_Predict : Predict {

public:
	Garbage_Predict();

	Garbage_Predict(size_t w, size_t h, string picloc);

	virtual void setModel(string pb);

	virtual void setModel(string pb, string pbtx);

	virtual vector<string>* getModel();

	virtual void setNet();

	virtual dnn::Net* getNet();

	virtual void setlabelList(vector<string> *labe);

	virtual vector<string> * getlabelList();

	virtual string getPic();

	virtual void setPic(String loc);

	virtual void preOp(string pb, Mat pic, size_t w, size_t h);


	virtual void preOp(size_t w, size_t h,
		string picloc,
		string pb,
		vector<string> *labe);

	virtual void preOp(
		size_t w, size_t h,
		string picloc,
		string pb) ;

	//����Ԥ����
	virtual void predict();

	// ��ȡԤ���� ���±�
	virtual vector<string>* getOut();

	virtual Mat getMat();

	// ��ȡԤ����
	virtual vector<string>* getOutStringList(Mat pic);

	virtual vector<string>* getOutStringList(string pic) ;
};


//// ��ȡԤ����
//Mat getOutMat(Mat pic)
//{
//	Garbage_Predict GBP;
//	// ͼ�񳤿�  Ԥ��ͼ��
//	GBP.preOp("model/model_graph_def.pb", pic, 512, 384);
//	GBP.predict();			// ����Ԥ��
//	// ��ȡԤ����ͼƬ
//	Mat out = GBP.getMat();
//	return out;
//}




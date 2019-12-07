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
	size_t inWidth;				// 图片宽
	size_t inHeight;			// 图片长
	string wait_predict_pic;	// 待预测图片 地址

	vector<string> *label;		// 标签名称
	int labelsize;				// 标签数目

	cv::Mat img;
	cv::Mat blob;
	cv::Mat output;

	String model;				// DNN模型（路径） // ML 模型存储路径 
	String pbtxt;				// DNN模型配置文件（路径）// ML 训练图片存储路径
	dnn::Net net;				// 网络 = cv::dnn::readNetFromTensorflow(weights, prototxt);

	float confidenceThreshold;	// 置信度阈值
	vector<string> *outList;	// 预测结果

public:
	Predict() {}

	Predict(size_t w, size_t h, string picloc)
	{
		inWidth = w;
		inHeight = h;
		wait_predict_pic = picloc;
	}

	// 设置搭建模型
	virtual void setModel(string pb, string pbtx) = 0;

	virtual void setModel(string pb) = 0;

	// 获取搭建模型
	virtual vector<string>* getModel() = 0;

	// 设置搭建模型到网络
	virtual void setNet() = 0;

	// 获取搭建模型到网络
	virtual dnn::Net * getNet() = 0;

	// 设置标签信息
	virtual void setlabelList(vector<string> *labe) = 0;

	// 获取标签信息
	virtual vector<string> * getlabelList() = 0;

	// 获取图片位置
	virtual string getPic() = 0;

	// 设置图片位置
	virtual void setPic(String loc) = 0;


	virtual void preOp(string pb, Mat pic, size_t w, size_t h) = 0;

	// 预处理操作   图片放缩 灰度等等
	virtual void preOp(size_t w, size_t h,
		string picloc,
		string pb,
		vector<string> *labe) = 0;

	// 预处理操作   图片放缩 灰度等等
	virtual void preOp(
		size_t w, size_t h,
		string picloc,
		string pb) = 0;
	// 进行模型预测
	virtual void predict() = 0;


	// 获取预测结果 按下标
	virtual vector<string>* getOut() = 0;

	virtual Mat getMat() = 0;

	// 获取预测结果
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

	//返回预测结果
	virtual void predict();

	// 获取预测结果 按下标
	virtual vector<string>* getOut();

	virtual Mat getMat();

	// 获取预测结果
	virtual vector<string>* getOutStringList(Mat pic);

	virtual vector<string>* getOutStringList(string pic) ;
};


//// 获取预测结果
//Mat getOutMat(Mat pic)
//{
//	Garbage_Predict GBP;
//	// 图像长宽  预测图像
//	GBP.preOp("model/model_graph_def.pb", pic, 512, 384);
//	GBP.predict();			// 进行预测
//	// 获取预测后的图片
//	Mat out = GBP.getMat();
//	return out;
//}




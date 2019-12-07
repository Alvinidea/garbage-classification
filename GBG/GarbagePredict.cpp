#include"Predict.h"

Garbage_Predict::Garbage_Predict()
{
	confidenceThreshold = 0.5;
}

Garbage_Predict::Garbage_Predict(size_t w, size_t h, string picloc) : Predict(w, h, picloc)
{
	confidenceThreshold = 0.5;
}

void Garbage_Predict::setModel(string pb, string pbtx)
{
	model = pb;
	pbtxt = pbtx;
}

void Garbage_Predict::setModel(string pb)
{
	model = pb;
}

vector<string>* Garbage_Predict::getModel()
{
	vector<string> *models = new vector<string>();
	models->push_back(model);
	models->push_back(pbtxt);
	return models;
}

void Garbage_Predict::setNet()
{
	//net = cv::dnn::readNetFromTensorflow(model, pbtxt);
	net = cv::dnn::readNetFromTensorflow(model);
}

dnn::Net* Garbage_Predict::getNet()
{
	return &net;
}

void Garbage_Predict::setlabelList(vector<string> *labe)
{
	label = labe;
}

vector<string> * Garbage_Predict::getlabelList()
{
	return label;
}

string Garbage_Predict::getPic()
{
	return wait_predict_pic;
}

void Garbage_Predict::setPic(String loc)
{
	wait_predict_pic = loc;
}


void Garbage_Predict::preOp(string pb, Mat pic,size_t w, size_t h)
{
	//	获取已经训练好的模型
	setModel(pb);
	setNet();
	// 读取图片
	img = pic;
	// 更改图片大小
	// img.resize(inWidth,inHeight);
	//	对图片进行处理,归一化 mean,subtraction
	blob = cv::dnn::blobFromImage(img, 1. / 255, Size(w, h));
	//	cout << "blob size: " << blob.size << endl;
	vector<string> * labe = new vector<string>();
	labe->push_back("cardboard");
	labe->push_back("glass");
	labe->push_back("metal");
	labe->push_back("paper");
	labe->push_back("plastic");
	setlabelList(labe);
}

void Garbage_Predict::preOp(size_t w, size_t h,
	string picloc,
	string pb,
	vector<string> *labe)
{
	//	获取已经训练好的模型
	setModel(pb, pbtxt);
	setNet();
	setPic(picloc);
	setlabelList(labe);
	// confidenceThreshold = conf;
	// 读取图片
	img = cv::imread(picloc);
	// 更改图片大小
	// img.resize(inWidth,inHeight);
	//	对图片进行处理,归一化 mean,subtraction
	blob = cv::dnn::blobFromImage(img, 1. / 255, Size(w, h));
	//	cout << "blob size: " << blob.size << endl;
}


void Garbage_Predict::preOp(
	size_t w, size_t h,
	string picloc,
	string pb)
{

	//	获取已经训练好的模型
	setModel(pb);
	setNet();
	setPic(picloc);

	// confidenceThreshold = conf;
	// 读取图片
	img = cv::imread(picloc);
	// 更改图片大小
	// img.resize(inWidth,inHeight);
	//	对图片进行处理,归一化 mean,subtraction
	blob = cv::dnn::blobFromImage(img, 1. / 255, Size(w, h));
	//	cout << "blob size: " << blob.size << endl;

	vector<string> * labe = new vector<string>();
	labe->push_back("cardboard");
	labe->push_back("glass");
	labe->push_back("metal");
	labe->push_back("paper");
	labe->push_back("plastic");
	setlabelList(labe);
}

//返回预测结果
void Garbage_Predict::predict()
{
	net.setInput(blob);
	output = net.forward();
}


// 待预测图片
// 预测类型
// 置信度
// 预测花费的时间
vector<string>* Garbage_Predict::getOut()
{
	outList = new vector<string>();
	Point classIdPoint;
	double confidence;
	// 选出最大置信度  和   对应的类别标号
	minMaxLoc(output.reshape(1, 1), 0, &confidence, 0, &classIdPoint);
	// 获取类别标号
	int classId = classIdPoint.x % 5; 
	// 获取预测时间
	double freq = getTickFrequency() / 1000;
	std::vector<double> layersTimes;
	double t = net.getPerfProfile(layersTimes) / freq;

	string timelabe = format("%.2f ms", t); // 获取预测时间
	
	string picType = label->empty() || label->size() <= classId ?
		format("Class #%d", classId).c_str() :
		(*label)[classId].c_str();

	outList->push_back(wait_predict_pic);			// 待预测图片
	outList->push_back(picType);
	// outList->push_back(picType);					// 预测类型
	outList->push_back(format("%.4f", confidence));	// 置信度
	outList->push_back(timelabe);					// 预测花费的时间
	return outList;
}


// 预测信息画在图片上
Mat Garbage_Predict::getMat()
{
	Point classIdPoint;
	double confidence;
	cout<< output.reshape(1, 1).dims << endl;
	cout << output.rows << endl << output.cols << endl;
	
	minMaxLoc(output.reshape(1, 1), 0, &confidence, 0, &classIdPoint);
	int classId = classIdPoint.x;
	cout << classIdPoint.x<< "   "<< classIdPoint.y;
	// Put efficiency information.
	std::vector<double> layersTimes;
	double freq = getTickFrequency() / 1000;
	double t = net.getPerfProfile(layersTimes) / freq;
	std::string labe = format("predict time: %.2f ms", t);
	putText(img, labe, Point(0, 15), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0));
	// Print predicted class.
	labe = format("%s: %.4f", 
		(label->empty() || label->size() <= classId ? format("Class #%d", classId).c_str() :
		(*label)[classId].c_str()),
		confidence);
	putText(img, labe, Point(0, 40), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0));
	return img;
}

vector<string>* Garbage_Predict::getOutStringList(Mat pic)
{

	// 图像长宽  预测图像
	preOp("model/model_graph_def.pb", pic, 512, 384);
	predict();			// 进行预测
	// 获取预测后信息并打印
	vector<string> *list = getOut();

	cout << "待预测图片:\t" << (*list)[0] << endl;
	cout << "预测类型：\t" << (*list)[1] << endl;
	cout << "置信度:\t\t " << (*list)[2] << endl;
	cout << "预测花费的时间:\t" << (*list)[3] << endl;
	return list;
}

vector<string>* Garbage_Predict::getOutStringList(string pic)
{

	// 图像长宽  预测图像
	preOp(512, 384, pic, "model/model_graph_def.pb");
	predict();			// 进行预测
	// 获取预测后信息并打印
	vector<string> *list = getOut();

	cout << "待预测图片:\t" << (*list)[0] << endl;
	cout << "预测类型：\t" << (*list)[1] << endl;
	cout << "置信度:\t\t " << (*list)[2] << endl;
	cout << "预测花费的时间:\t" << (*list)[3] << endl;
	return list;
}
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
	//	��ȡ�Ѿ�ѵ���õ�ģ��
	setModel(pb);
	setNet();
	// ��ȡͼƬ
	img = pic;
	// ����ͼƬ��С
	// img.resize(inWidth,inHeight);
	//	��ͼƬ���д���,��һ�� mean,subtraction
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
	//	��ȡ�Ѿ�ѵ���õ�ģ��
	setModel(pb, pbtxt);
	setNet();
	setPic(picloc);
	setlabelList(labe);
	// confidenceThreshold = conf;
	// ��ȡͼƬ
	img = cv::imread(picloc);
	// ����ͼƬ��С
	// img.resize(inWidth,inHeight);
	//	��ͼƬ���д���,��һ�� mean,subtraction
	blob = cv::dnn::blobFromImage(img, 1. / 255, Size(w, h));
	//	cout << "blob size: " << blob.size << endl;
}


void Garbage_Predict::preOp(
	size_t w, size_t h,
	string picloc,
	string pb)
{

	//	��ȡ�Ѿ�ѵ���õ�ģ��
	setModel(pb);
	setNet();
	setPic(picloc);

	// confidenceThreshold = conf;
	// ��ȡͼƬ
	img = cv::imread(picloc);
	// ����ͼƬ��С
	// img.resize(inWidth,inHeight);
	//	��ͼƬ���д���,��һ�� mean,subtraction
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

//����Ԥ����
void Garbage_Predict::predict()
{
	net.setInput(blob);
	output = net.forward();
}


// ��Ԥ��ͼƬ
// Ԥ������
// ���Ŷ�
// Ԥ�⻨�ѵ�ʱ��
vector<string>* Garbage_Predict::getOut()
{
	outList = new vector<string>();
	Point classIdPoint;
	double confidence;
	// ѡ��������Ŷ�  ��   ��Ӧ�������
	minMaxLoc(output.reshape(1, 1), 0, &confidence, 0, &classIdPoint);
	// ��ȡ�����
	int classId = classIdPoint.x % 5; 
	// ��ȡԤ��ʱ��
	double freq = getTickFrequency() / 1000;
	std::vector<double> layersTimes;
	double t = net.getPerfProfile(layersTimes) / freq;

	string timelabe = format("%.2f ms", t); // ��ȡԤ��ʱ��
	
	string picType = label->empty() || label->size() <= classId ?
		format("Class #%d", classId).c_str() :
		(*label)[classId].c_str();

	outList->push_back(wait_predict_pic);			// ��Ԥ��ͼƬ
	outList->push_back(picType);
	// outList->push_back(picType);					// Ԥ������
	outList->push_back(format("%.4f", confidence));	// ���Ŷ�
	outList->push_back(timelabe);					// Ԥ�⻨�ѵ�ʱ��
	return outList;
}


// Ԥ����Ϣ����ͼƬ��
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

	// ͼ�񳤿�  Ԥ��ͼ��
	preOp("model/model_graph_def.pb", pic, 512, 384);
	predict();			// ����Ԥ��
	// ��ȡԤ�����Ϣ����ӡ
	vector<string> *list = getOut();

	cout << "��Ԥ��ͼƬ:\t" << (*list)[0] << endl;
	cout << "Ԥ�����ͣ�\t" << (*list)[1] << endl;
	cout << "���Ŷ�:\t\t " << (*list)[2] << endl;
	cout << "Ԥ�⻨�ѵ�ʱ��:\t" << (*list)[3] << endl;
	return list;
}

vector<string>* Garbage_Predict::getOutStringList(string pic)
{

	// ͼ�񳤿�  Ԥ��ͼ��
	preOp(512, 384, pic, "model/model_graph_def.pb");
	predict();			// ����Ԥ��
	// ��ȡԤ�����Ϣ����ӡ
	vector<string> *list = getOut();

	cout << "��Ԥ��ͼƬ:\t" << (*list)[0] << endl;
	cout << "Ԥ�����ͣ�\t" << (*list)[1] << endl;
	cout << "���Ŷ�:\t\t " << (*list)[2] << endl;
	cout << "Ԥ�⻨�ѵ�ʱ��:\t" << (*list)[3] << endl;
	return list;
}
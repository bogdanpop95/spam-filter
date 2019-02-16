// OpenCVApplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "common.h"
#include <fstream>
#include <iostream>
#include <regex>
#include <algorithm>

void readDataSet1()
{

	// setup filename and ifstream csv file
	char fname[MAX_PATH];
	char outputName[MAX_PATH];
	sprintf(fname, "D:\\Facultate\\An IV\\Semestrul I\\SRF\\Proiect\\datasets\\spam2.csv");
	sprintf(outputName, "D:\\Facultate\\An IV\\Semestrul I\\SRF\\Proiect\\datasets\\test.csv");
	std::ifstream csv(fname);
	std::ofstream train(outputName);

	train << "sep=~\n";

	//reading header of spam.csv file
	std::string value;
	int iterator = 1;
	while (csv.good() && iterator < 5) {
		getline(csv, value, ',');
		//std::cout << iterator << ": " << value << std::endl;
		iterator++;
	}
	getline(csv, value, '\n');
	iterator = 1;
	// reading data
	std::map<std::string, int> wordDict;
	while (csv.good() && iterator < 5573) {
		getline(csv, value, ',');
		//std::cout << iterator << ": " << value << std::endl;
		if ((iterator >= 449 && iterator <= 747) || iterator >= 3644)
			train << value << '~';
		getline(csv, value, '\n');
		value.pop_back();
		value.pop_back();
		value.pop_back();
		if (value.at(0) == '"') {
			value.erase(0, 1);
			value.pop_back();
		}
		//std::cout << iterator << ": " << value << std::endl;
		if ((iterator >= 449 && iterator <= 747) || iterator >= 3644)
			train << value << '\n';
		iterator++;
	}

}

std::vector<std::string> stopWords = { "i", "me", "my", "myself",
"we", "our", "ours", "ourselves", "you",
"your", "yours", "yourself", "yourselves",
"he", "him", "his", "himself", "she", "her",
"hers", "herself", "it", "its", "itself", "they",
"them", "their", "theirs", "themselves", "what",
"which", "who", "whom", "this", "that", "these",
"those", "am", "is", "are", "was", "were", "be",
"been", "being", "have", "has", "had", "having",
"do", "does", "did", "doing", "a", "an", "the",
"and", "but", "if", "or", "because", "as", "until",
"while", "of", "at", "by", "for", "with", "about",
"against", "between", "into", "through", "during",
"before", "after", "above", "below", "to", "from",
"up", "down", "in", "out", "on", "off", "over",
"under", "again", "further", "then", "once",
"here", "there", "when", "where", "why", "how",
"all", "any", "both", "each", "few", "more",
"most", "other", "some", "such", "no", "nor",
"not", "only", "own", "same", "so", "than", "too",
"very", "s", "t", "can", "will", "just", "don", "should", "now" };

void readDataSet2()
{

	// setup filename and ifstream csv file
	char fname[MAX_PATH];
	char outputName[MAX_PATH];
	sprintf(fname, "D:\\Facultate\\An IV\\Semestrul I\\SRF\\Proiect\\datasets\\train.csv");
	sprintf(outputName, "D:\\Facultate\\An IV\\Semestrul I\\SRF\\Proiect\\datasets\\freqTrainNoStopWords.csv");
	std::ifstream csv(fname);
	std::ofstream freq(outputName);

	std::string value;
	std::regex e("[a-zA-Z]+");
	std::smatch sm;
	int iterator = 1;

	std::map<std::string, bool> stopDict;

	for (auto& v : stopWords) {
		stopDict.emplace(v, true);
	}

	// reading data
	std::map<std::string, int> wordDict;
	while (csv.good() && iterator <= 3345) {
		getline(csv, value, ',');
		//std::cout << iterator << ": " << value << std::endl;
		getline(csv, value, '\n');
		value.pop_back();
		if (value.at(0) == '"') {
			value.erase(0, 1);
			value.pop_back();
		}
		//std::cout << iterator << ": " << value << std::endl;
		//std::regex_match(value, sm, e, std::regex_constants::match_default);
		//std::cout << "range with " << sm.size() << " matches\n";
		//std::cout << "the matches were: \n";
		//for (unsigned i = 0; i < sm.size(); ++i) {
		//	std::cout << "[" << sm[i] << "] ";
		//}
		//std::cout << "the matches were: \n";
		//if (iterator > 448) {
		while (std::regex_search(value, sm, e)) {
			for (auto x : sm) {
				//std::cout << x << " ";
				std::string lower_x = x;
				std::transform(lower_x.begin(), lower_x.end(), lower_x.begin(), ::tolower);
				//std::cout << lower_x << " ";
				if (stopDict.find(lower_x) == stopDict.end())
				{
					if (wordDict.find(x) == wordDict.end())
						wordDict.emplace(x, 1);
					else
						wordDict.at(x)++;
				}
			}
			value = sm.suffix().str();
		}
		std::cout << std::endl;
		//}

		iterator++;
	}
	std::vector<std::string> memory;
	std::cout << "Word dict: \n";
	for (auto& entry : wordDict) {
		if (entry.second < 2)
			memory.push_back(entry.first);
	}
	for (auto& v : memory) {
		wordDict.erase(v);
	}
	for (auto& entry : wordDict) {
		//std::cout << entry.first << " , " << entry.second << std::endl;
		freq << entry.first << ",";
		freq << entry.second << "\n";
	}
}

void readDataSet3()
{

	// setup filename and ifstream csv file
	char fname[MAX_PATH];
	char outputName[MAX_PATH];
	sprintf(fname, "D:\\Facultate\\An IV\\Semestrul I\\SRF\\Proiect\\datasets\\train.csv");
	sprintf(outputName, "D:\\Facultate\\An IV\\Semestrul I\\SRF\\Proiect\\datasets\\lengthTrain.csv");
	std::ifstream csv(fname);
	std::ofstream length(outputName);
	//length << "sep=,\n";

	std::string value;
	int iterator = 1;

	// reading data
	std::map<std::string, int> wordDict;
	while (csv.good() && iterator < 3346) {
		getline(csv, value, ',');
		getline(csv, value, '\n');
		value.pop_back();
		if (value.at(0) == '"') {
			value.erase(0, 1);
			value.pop_back();
		}
		//if (iterator > 448)
			length << value.size() << "\n";
		iterator++;
	}
}

int spam_num_train = 448, ham_num_train = 2897, spam_num_test = 299, ham_num_test = 1929;
int words_in_spam = 968, words_in_ham = 2519;
int total_num_train = spam_num_train + ham_num_train;
int total_num_test = spam_num_test + ham_num_test;
int words_in_total = words_in_spam + words_in_ham;
int nr_classes = 2;
int segment = 0;

void readDataSet4(Mat &X, Mat &Y, int features_num)
{
	// setup filename and ifstream csv file
	char fname[MAX_PATH];
	char inputName[MAX_PATH];
	char outputName[MAX_PATH];
	sprintf(fname, "D:\\Facultate\\An IV\\Semestrul I\\SRF\\Proiect\\datasets\\train.csv");
	sprintf(inputName, "D:\\Facultate\\An IV\\Semestrul I\\SRF\\Proiect\\datasets\\freqTrainNoStopWords.csv");
	sprintf(outputName, "D:\\Facultate\\An IV\\Semestrul I\\SRF\\Proiect\\datasets\\wordCountTrainNoStopWords1.csv");
	std::ifstream csv(fname);
	std::ifstream freq(inputName);
	std::ofstream count(outputName);

	char fnameSpam[MAX_PATH];
	char fnameHam[MAX_PATH];
	char fnameLength[MAX_PATH];
	sprintf(fnameSpam, "D:\\Facultate\\An IV\\Semestrul I\\SRF\\Proiect\\datasets\\freqTrainSpamNoStopWords.csv");
	sprintf(fnameHam, "D:\\Facultate\\An IV\\Semestrul I\\SRF\\Proiect\\datasets\\freqTrainHamNoStopWords.csv");
	sprintf(fnameLength, "D:\\Facultate\\An IV\\Semestrul I\\SRF\\Proiect\\datasets\\lengthTrain.csv");
	std::ifstream spam(fnameSpam);
	std::ifstream ham(fnameHam);
	std::ifstream length(fnameLength);

	X = Mat(total_num_train + 1, features_num + 1, CV_32SC1);

	for (int i = 0; i < X.rows; i++) {
		for (int j = 0; j < X.cols; j++) {
			X.at<int>(i, j) = 0;
		}
	}

	int iterator = 1;
	std::map<std::string, int> features;
	std::string value;
	while (freq.good() && iterator <= features_num)
	{
		getline(freq, value, ',');
		features.emplace(value, iterator - 1);
		getline(freq, value, '\n');
		X.at<int>(0, iterator - 1) = std::stoi(value);
		iterator++;
	}

	X.at<int>(0, features_num) = -1;

	iterator = 1;
	for (auto& v : features) {
		//std::cout << iterator << ": " << v.first << " , " << v.second<< std::endl;
		count << v.first << ",";
		iterator++;
	}
	count << "\n";

	for (int i = 0; i < X.cols; i++) {
		count << X.at<int>(0, i) << ",";
	}
	count << "\n";

	std::map<std::string, int> spam_count;
	iterator = 1;
	std::string counter;
	while (spam.good() && iterator <= words_in_spam)
	{
		getline(spam, value, ',');
		getline(spam, counter, '\n');
		spam_count.emplace(value, std::stoi(counter));
		iterator++;
	}

	for (auto& v : features) {
		if (spam_count.find(v.first) != spam_count.end()) {
			count << spam_count.at(v.first) << ",";
		}
		else
			count << 0 << ",";
	}
	count << "\n";

	std::map<std::string, int> ham_count;
	iterator = 1;
	while (ham.good() && iterator <= words_in_ham)
	{
		getline(ham, value, ',');
		getline(ham, counter, '\n');
		ham_count.emplace(value, std::stoi(counter));
		iterator++;
	}

	for (auto& v : features) {
		if (ham_count.find(v.first) != ham_count.end()) {
			count << ham_count.at(v.first) << ",";
		}
		else
			count << 0 << ",";
	}
	count << "\n";

	std::regex e("[a-zA-Z]+");
	std::smatch sm;
	iterator = 1;
	while (csv.good() && iterator <= total_num_train) {
		getline(csv, value, ',');
		//std::cout << iterator << ": " << value << std::endl;
		getline(csv, value, '\n');
		value.pop_back();
		if (value.at(0) == '"') {
			value.erase(0, 1);
			value.pop_back();
		}
		//std::cout << iterator << ": " << value << std::endl;
		while (std::regex_search(value, sm, e)) {
			for (auto x : sm) {
				//std::cout << x << " ";
				if (features.find(x) != features.end())
					X.at<int>(iterator, features.at(x))++;
			}
			value = sm.suffix().str();
		}
		//for (int i = 0; i < X.cols; i++) {
		//	count << X.at<int>(iterator, i) << ",";
		//}
		//count << "\n";
		iterator++;
	}

	//TODO
	int max_global = 0;
	for (int j = 0; j < X.cols - 1; j++) {
		int max = 0;
		for (int i = 1; i <= total_num_train; i++) {
			if (X.at<int>(i, j) > max)
				max = X.at<int>(i, j);
		}
		if (max > max_global)
			max_global = max;
		count << max << ",";
	}
	count << "\n";

	count << max_global << ",";
	for (int i = 1; i < X.cols - 1; i++) {
		count << 0 << ",";
	}
	count << "\n";

	iterator = 1;
	while (length.good() && iterator <= total_num_train)
	{
		getline(length, value, '\n');
		//std::cout << iterator << " " << value << std::endl;
		X.at<int>(iterator, features_num) = std::stoi(value);
		iterator++;
	}

	iterator = 1;
	while (iterator <= total_num_train) {
		for (int i = 0; i < X.cols; i++) {
			count << X.at<int>(iterator, i) << ",";
		}
		count << "\n";
		iterator++;
	}

}

void computePriors(Mat &priors)
{
	priors = Mat(nr_classes, 1, CV_32FC1);
	priors.at<float>(0, 0) = (float)spam_num_train / (float)total_num_train;
	priors.at<float>(1, 0) = (float)ham_num_train / (float)total_num_train;
}

void computeLikelihood(Mat &likelihood, int features_num)
{
	char fname[MAX_PATH];
	sprintf(fname, "D:\\Facultate\\An IV\\Semestrul I\\SRF\\Proiect\\datasets\\wordCountTrainNoStopWords1.csv");
	std::ifstream csv(fname);

	//likelihood = Mat(nr_classes, features_num, CV_32FC1);
	int dimens[] = { nr_classes, features_num + 1, 19 };
	likelihood = Mat(3, dimens, CV_32FC1);

	for (int i = 0; i < dimens[0]; i++) {
		for (int j = 0; j < dimens[1]; j++) {
			for (int k = 0; k < dimens[2]; k++) {
				likelihood.at<float>(i, j, k) = 0;
			}
		}
	}

	int iterator = 1;
	std::string value;
	std::vector<int> spam;
	std::vector<int> ham;
	std::vector<int> total;
	std::vector<int> lengths;
	std::vector<int> lengths_copy;
	std::vector<std::string> features_name;
	while (csv.good() && iterator <= 6) {
		int counter = 1;
		while (counter <= features_num + 1) {
			if (counter == features_num + 1)
				getline(csv, value, '\n');
			else
				getline(csv, value, ',');
			//std::cout << iterator << ": " << value << std::endl;
			if (iterator == 1)
				features_name.push_back(value);
			else if (iterator == 2)
				total.push_back(std::stoi(value));
			else if (iterator == 3)
				spam.push_back(std::stoi(value));
			else if (iterator == 4)
				ham.push_back(std::stoi(value));
			counter++;
		}
		iterator++;
	}

	int occ = 0;
	iterator = 1;
	while (csv.good() && iterator <= total_num_train) {
		int counter = 0;
		while (counter < features_num + 1) {
			if (counter == features_num) {
				getline(csv, value, '\n');
				lengths.push_back(std::stoi(value));
				lengths_copy.push_back(std::stoi(value));
			}
			else
				getline(csv, value, ',');
			//std::cout << iterator << ": " << value << std::endl;
			occ = std::stoi(value);
			if (iterator <= spam_num_train && counter < features_num) {
				likelihood.at<float>(0, counter, occ)++;
			}
			else if (iterator > spam_num_train && counter < features_num){
				likelihood.at<float>(1, counter, occ)++;
			}
			counter++;
		}
		iterator++;
	}

	
	//get max length
	sort(lengths_copy.begin(), lengths_copy.end());
	int max_length = lengths_copy.at(lengths_copy.size() - 1);
	segment = max_length / 19;

	iterator = 0;
	while (iterator < total_num_train) {
		if (iterator < spam_num_train)
			likelihood.at<float>(0, features_num, (float)lengths.at(iterator) / (float)segment)++;
		else
			likelihood.at<float>(1, features_num, (float)lengths.at(iterator) / (float)segment)++;
		iterator++;
	}

	//for (auto& entry : spam) {
	//	std::cout << entry.first << " , " << entry.second << std::endl;
	//}

	for (int feature = 0; feature < dimens[1]; feature++) {
		for (int count = 0; count < dimens[2]; count++) {
			if (likelihood.at<float>(0, feature, count) == 0)
				likelihood.at<float>(0, feature, count) = 1e-6;
			else
				likelihood.at<float>(0, feature, count) /= (float)spam_num_train;
			if (likelihood.at<float>(1, feature, count) == 0)
				likelihood.at<float>(1, feature, count) = 1e-6;
			else
				likelihood.at<float>(1, feature, count) /= (float)ham_num_train;
		}
	}
}

std::vector<int> read_one_test_line(int line, int features_num, int &length)
{
	char fname[MAX_PATH];
	char feat[MAX_PATH];
	sprintf(fname, "D:\\Facultate\\An IV\\Semestrul I\\SRF\\Proiect\\datasets\\test.csv");
	sprintf(feat, "D:\\Facultate\\An IV\\Semestrul I\\SRF\\Proiect\\datasets\\freqTrainNoStopWords.csv");
	std::ifstream csv(fname);
	std::ifstream freq(feat);

	std::vector<int> words_count;

	int iterator = 1;
	std::map<std::string, bool> features;
	std::map<std::string, bool> words;
	std::string value;
	while (freq.good() && iterator <= features_num)
	{
		getline(freq, value, ',');
		features.emplace(value, true);
		//std::cout << iterator << ": " << value << std::endl;
		getline(freq, value, '\n');
		iterator++;
	}

	std::regex e("[a-zA-Z]+");
	std::smatch sm;
	iterator = 1;
	while (csv.good() && iterator <= total_num_test) {
		getline(csv, value, ',');
		//std::cout << iterator << ": " << value << std::endl;
		getline(csv, value, '\n');
		if (value.at(0) == '"') {
			value.erase(0, 1);
			value.pop_back();
		}
		//std::cout << iterator << ": " << value << std::endl;
		if (iterator == line) {
			length = value.size();
			while (std::regex_search(value, sm, e)) {
				for (auto x : sm) {
					//std::cout << x << " ";
					if (words.find(x) == words.end())
						words.emplace(x, 1);
					else
						words.at(x)++;
				}
				value = sm.suffix().str();
			}
			break;
		}
		iterator++;
	}

	iterator = 0;
	for (auto& x : features) {
		if (words.find(x.first) != words.end())
			words_count.push_back(words.at(x.first));
		else
			words_count.push_back(0);
		//std::cout << x.first << ": " << words_count.at(iterator) << std::endl;
		iterator++;
	}
	return words_count;
}

int classifyBayes(std::vector<int> test, Mat priors, Mat likelihood, int features_num, int lengthVectorized)
{
	std::vector<std::pair<float, int>> v;
	for (int c = 0; c < 2; c++) {
		std::pair<double, int> pair;
		pair.first = 0;
		pair.second = c;
		for (int i = 0; i < features_num; i++) {
			pair.first += log(likelihood.at<float>(c, i, test.at(i)));
		}
		pair.first += log(priors.at<float>(c, 0));
		pair.first += log(likelihood.at<float>(c, features_num, lengthVectorized));
		v.push_back(pair);
	}

	sort(v.begin(), v.end());
	for (int i = 0; i < v.size(); i++)
		printf("LOG = %f, Class = %d\n", v.at(i).first, v.at(i).second);

	int c = v.at(v.size() - 1).second;
	v.clear();
	return c;
}

Mat C = Mat(2, 2, CV_32SC1);

float read_test(int features_num, Mat priors, Mat likelihood)
{
	char fname[MAX_PATH];
	char feat[MAX_PATH];
	sprintf(fname, "D:\\Facultate\\An IV\\Semestrul I\\SRF\\Proiect\\datasets\\test.csv");
	sprintf(feat, "D:\\Facultate\\An IV\\Semestrul I\\SRF\\Proiect\\datasets\\freqTrainNoStopWords.csv");
	std::ifstream csv(fname);
	std::ifstream freq(feat);

	std::vector<int> words_count;
	float accuracy = 0;

	C.setTo(0);

	int iterator = 1;
	std::map<std::string, bool> features;
	std::map<std::string, bool> words;
	std::string value;
	while (freq.good() && iterator <= features_num)
	{
		getline(freq, value, ',');
		features.emplace(value, true);
		//std::cout << iterator << ": " << value << std::endl;
		getline(freq, value, '\n');
		iterator++;
	}

	std::regex e("[a-zA-Z]+");
	std::smatch sm;
	iterator = 1;
	while (csv.good() && iterator <= total_num_test) {
		getline(csv, value, ',');
		//std::cout << iterator << ": " << value << std::endl;
		getline(csv, value, '\n');
		if (value.at(0) == '"') {
			value.erase(0, 1);
			value.pop_back();
		}
		int length = value.size();
		//std::cout << iterator << ": " << value << std::endl;
		while (std::regex_search(value, sm, e)) {
			for (auto x : sm) {
				//std::cout << x << " ";
				if (words.find(x) == words.end())
					words.emplace(x, 1);
				else
					words.at(x)++;
			}
			value = sm.suffix().str();
		}
		for (auto& x : features) {
			if (words.find(x.first) != words.end())
				words_count.push_back(words.at(x.first));
			else
				words_count.push_back(0);
		}
		int c = classifyBayes(words_count, priors, likelihood, features_num, length / segment);
		if (iterator <= spam_num_test)
			printf("SPAM_%d classified to: %d\n", iterator, c);
		if (iterator <= spam_num_test && c == 0) {
			accuracy++;
		}
		if (iterator > spam_num_test && c == 1) {
			accuracy++;
		}
		int creal = iterator > spam_num_test;
		C.at<int>(creal, c)++;

		if (iterator > spam_num_test)
			printf("HAM_%d classified to: %d\n", iterator, c);
		words_count.clear();
		words.clear();
		iterator++;
	}

	std::cout << std::endl << C << std::endl;

	return accuracy / total_num_test;
}

int main()
{
	/* number of features, here: 1 feature = a word count in message (could/not include stop words)
	we can append as a feature, the message length too */
	// this number doesn't include stop words
	int features_num = 3240;
	Mat X, Y, priors, likelihood;
	int lengthTest = 0;

	//readDataSet4(X, Y, features_num);
	//readDataSet3();
	//readDataSet2();
	computePriors(priors);
	computeLikelihood(likelihood, features_num);
	//std::vector<int> words_count = read_one_test_line(2, features_num, lengthTest);
	//std::cout << "Size: " << words_count.size() << std::endl;
	//int c = classifyBayes(words_count, priors, likelihood, features_num, lengthTest / segment);
	//std::cout << std::endl << "Classified to: " << c << std::endl;
	float acc = read_test(features_num, priors, likelihood);
	std::cout << std::endl << "Accuracy: " << acc << std::endl;

}
#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>

void NormalFixer(cv::Mat& in, cv::Mat& out) {
	out.release();
	std::vector<cv::Mat> channels_bgra;
	cv::split(in, channels_bgra);

	std::vector<cv::Mat> fix = { channels_bgra[3], channels_bgra[1], channels_bgra[0] };
	out = cv::Mat(in.size().height, in.size().width, CV_8UC3);
	cv::merge(fix, out);
}

void GetRGBpart(cv::Mat& in, cv::Mat& out) {
	out.release();
	std::vector<cv::Mat> channels_bgra;
	cv::split(in, channels_bgra);

	std::vector<cv::Mat> rgb = { channels_bgra[0], channels_bgra[1], channels_bgra[2] };
	out = cv::Mat(in.size().height, in.size().width, CV_8UC3);
	cv::merge(rgb, out);
}

void GetAlphaPart(cv::Mat& in, cv::Mat& out) {
	out.release();
	std::vector<cv::Mat> channels_bgra;
	cv::split(in, channels_bgra);

	std::vector<cv::Mat> alpha = { channels_bgra[3] };
	out = cv::Mat(in.size().height, in.size().width, CV_8UC1);
	cv::merge(alpha, out);
}
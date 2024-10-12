/*
stats_functions.cpp
Suhail Attaelmanan
July 12 2024
Function implementation file
*/

#include "stats_functions_header.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <map>

/*
name: readData
brief: Reads data from standard input and stores it in a vector
param: vector data
return: void
*/
void readData(std::vector<double>& data) {
	double number;
	while (std::cin >> number) {
		data.push_back(number);
	}
	std::cin.clear();
	std::string temp;
	std::cin >> temp;
}

/*
name: printStats
brief: Prints statistical information of the data
param: vector data
return: void
*/
void printStats(const std::vector<double>& data) {
	double mean = calculateMean(data);
	double median = calculateMedian(const_cast<std::vector<double>&>(data));
	double variance = calculateVariance(data);
	double stdDev = calculateStdDev(data);
	double meanAbsDevMean = calculateMeanAbsDeviation(data, mean);
	double meanAbsDevMedian = calculateMeanAbsDeviation(data, median);
	double slope, intercept;
	calculateRegression(data, slope, intercept);

	std::vector<double> outliers1x, outliers2x, outliers3x;
	findOutliers(data, outliers1x, outliers2x, outliers3x);

	std::vector<double> sorted_data = data;
	std::sort(sorted_data.begin(), sorted_data.end());

	std::vector<double> modes;
	int mode_count = calculateMode(sorted_data, modes);
	double meanAbsDevMode = modes.empty() ? 0 : calculateMeanAbsDeviation(data, modes[0]);

	//Printing:

	std::cout << std::fixed << std::setprecision(3);
	std::cout << "\n---------------------------------------------\n";
	std::cout << "# elements" << std::setw(35) << data.size() << "\n";
	std::cout << "minimum" << std::setw(38) << findMin(data) << "\n";
	std::cout << "maximum" << std::setw(38) << findMax(data) << "\n";
	std::cout << "mean" << std::setw(41) << mean << "\n";
	std::cout << "median" << std::setw(39) << median << "\n";
	std::cout << "variance" << std::setw(37) << variance << "\n";
	std::cout << "std. dev." << std::setw(36) << stdDev << "\n";
	std::cout << "---------------------------------------------\n";

	// Mode:

	std::cout << "# modes" << std::setw(38) << modes.size() << "\n";

	if (modes.empty()) {
		std::cout << "mode frequency" << std::setw(32) << "no mode\n";
		std::cout << "mode" << std::setw(42) << "no mode\n";
	}
	else if (modes.size() == 1) {
		std::cout << "mode frequency" << std::setw(31) << mode_count << "\n";
		std::cout << "mode" << std::setw(41) << modes[0] << "\n";
	}
	else {
		std::cout << "mode frequency" << std::setw(31) << mode_count << std::endl;
		std::cout << "modes";
		for (size_t i = 0; i < modes.size(); ++i) {
			std::cout << std::setw(40) << modes[i] << "\n     ";
		}
	}

	// mean absolute deviations
	std::cout << "\n---------------------------------------------\n";
	std::cout << "mean absolute deviations:\n";
	std::cout << "...about the mean" << std::setw(28) << meanAbsDevMean << "\n";
	std::cout << "...about the median" << std::setw(26) << meanAbsDevMedian << "\n";

	if (!modes.empty() && modes.size() == 1) // if unimodal
		std::cout << "...about the mode" << std::setw(28) << meanAbsDevMode << "\n";

	std::cout << "---------------------------------------------\n";
	std::cout << "regression slope" << std::setw(29) << slope << "\n";
	std::cout << "regression intercept" << std::setw(25) << intercept << "\n";
	std::cout << "---------------------------------------------\n";

	// Outliers:
	std::cout << "Outliers(1x)                   # outliers = " << outliers1x.size() << "\n";

	if (outliers1x.size() > 0) {
		for (double o : outliers1x) {
			std::cout << std::setw(45) << o << "\n";
		}
	}
	else {
		std::cout << "   \t\t\t\t  no outliers";
	}
	std::cout << "\nOutliers(2x)                   # outliers = " << outliers2x.size() << "\n";
	if (outliers2x.size() > 0) {
		for (double o : outliers2x) {
			std::cout << std::setw(45) << o << "\n";
		}
	}
	else {
		std::cout << "   \t\t\t\t  no outliers";
	}
	std::cout << "\nOutliers(3x)                   # outliers = " << outliers3x.size() << "\n";
	if (outliers3x.size() > 0) {
		for (double o : outliers3x) {
			std::cout << std::setw(45) << o << "\n";
		}
	}
	else {
		std::cout << "   \t\t\t\t  no outliers";
	}
	std::cout << "\n" << std::endl;;
}

/*
name: findMin
brief: Finds the minimum value in the data
param: vector data
return: double - the minimum value in the data
*/
double findMin(const std::vector<double>& data) {
	return *std::min_element(data.begin(), data.end());
}

/*
name: findMax
brief: Finds the maximum value in the data
param: vector data
return: double - the maximum value in the data
*/
double findMax(const std::vector<double>& data) {
	return *std::max_element(data.begin(), data.end());
}

/*
name: calculateMean
brief: Calculates the mean of the data
param: vector data
return: double - the mean of the data
*/
double calculateMean(const std::vector<double>& data) {
	double sum = 0.0;
	for (double num : data) {
		sum += num;
	}
	return sum / data.size();
}

/*
name: calculateMedian
brief: Calculates the median of the data
param: vector data
return: double - the median of the data
*/
double calculateMedian(std::vector<double>& data) {
	std::sort(data.begin(), data.end());
	size_t size = data.size();
	if (size % 2 == 0) {
		return (data[size / 2 - 1] + data[size / 2]) / 2;
	}
	else {
		return data[size / 2];
	}
}

/*
name: calculateVariance
brief: Calculates the variance of the data
param: vector data
return: double - the variance of the data
*/
double calculateVariance(const std::vector<double>& data) {
	double mean = calculateMean(data);
	double sum = 0.0;
	for (double num : data) {
		sum += (num - mean) * (num - mean);
	}
	return sum / data.size();
}

/*
name: calculateStdDev
brief: Calculates the standard deviation of the data
param: vector data
return: double - the standard deviation of the data
*/
double calculateStdDev(const std::vector<double>& data) {
	return std::sqrt(calculateVariance(data));
}

/*
name: calculateMode
brief: Finds the mode(s) and their frequency in a sorted dataset
param: vector data
param: modes - a vector of doubles to store the mode(s)
return: size_t - the frequency of the mode(s)
*/
int calculateMode(const std::vector<double>& v, std::vector<double>& modes) {
	int match{ 1 };  // holds a count of numbers
	int mode_count{ 1 };  // holds matched number sets count

	for (size_t i = 0; i < v.size() - 1; ++i) {
		if (v[i] == v[i + 1]) {
			match++;
		}
		else {
			if (match > mode_count) {
				modes.clear();
				modes.push_back(v[i]);
				mode_count = match;
			}
			else if (match == mode_count) {
				modes.push_back(v[i]);
			}
			match = 1; // reset count
		}
	}

	// Handle the last set of matches
	if (match > mode_count) {
		modes.clear();
		modes.push_back(v[v.size() - 1]);
		mode_count = match;
	}
	else if (match == mode_count) {
		modes.push_back(v[v.size() - 1]);
	}

	// check for no mode, if then mode_count = 0
	if (mode_count == 1) {
		modes.clear();
		mode_count = 0;
	}

	return mode_count;
}
/*
name: calculateMeanAbsDeviation
brief: Calculates the mean absolute deviation of the data about a given measure
param: vector data
param: double measure - the measure (mean/median/mode) about which the deviation is calculated
return: double - the mean absolute deviation of the data
*/
double calculateMeanAbsDeviation(const std::vector<double>& data, double measure) {
	double sum = 0.0;
	for (double num : data) {
		sum += std::abs(num - measure);
	}
	return sum / data.size();
}

/*
name: calculateRegression
brief: Calculates the slope and intercept of the regression line for the data
param: vector data
param: double slope
param: double intercept
return: void
*/
void calculateRegression(const std::vector<double>& data, double& slope, double& intercept) {
	size_t n = data.size();
	double sumX = 0.0, sumY = 0.0, sumXY = 0.0, sumX2 = 0.0;

	// Calculate sums of x (indices) and y (data values)
	for (int i = 0; i < n; ++i) {
		double x = i + 1;
		double y = data[i];
		sumX += x;
		sumY += y;
		sumXY += x * y;
		sumX2 += x * x;
	}

	// Calculate slope and intercept
	slope = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);
	intercept = (sumY - slope * sumX) / n;
}

/*
name:  findOutliers
brief: Identifies outliers in the data based on standard deviations from the mean
param: vector data
param: vector outliers1x
param: vector outliers2x
param: vector outliers3x
return: void
*/
void findOutliers(const std::vector<double>& data, std::vector<double>& outliers1x, std::vector<double>& outliers2x, std::vector<double>& outliers3x) {
	double mean = calculateMean(data);
	double stdDev = calculateStdDev(data);

	for (double num : data) {
		double deviation = std::abs(num - mean);
		if (deviation > 3 * stdDev) {
			outliers3x.push_back(num);
		}
		else if (deviation > 2 * stdDev) {
			outliers2x.push_back(num);
		}
		else if (deviation > stdDev) {
			outliers1x.push_back(num);
		}
	}
}

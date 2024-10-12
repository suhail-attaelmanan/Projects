#pragma once
/*
stats_functions_header.hpp
Suhail Attaelmanan
July 12 2024
Function definition file
*/

#include <vector>

// Function declarations:

/*
name: readData
brief: Reads data from standard input and stores it in a vector
param: vector data
return: void
*/
void readData(std::vector<double>& data);

/*
name: printStats
brief: Prints statistical information of the data
param: vector data
return: void
*/
void printStats(const std::vector<double>& data);

/*
name: findMin
brief: Finds the minimum value in the data
param: vector data
return: double - the minimum value in the data
*/
double findMin(const std::vector<double>& data);

/*
name: findMax
brief: Finds the maximum value in the data
param: vector data
return: double - the maximum value in the data
*/
double findMax(const std::vector<double>& data);

/*
name: calculateMean
brief: Calculates the mean of the data
param: vector data
return: double - the mean of the data
*/
double calculateMean(const std::vector<double>& data);

/*
name: calculateMedian
brief: Calculates the median of the data
param: vector data
return: double - the median of the data
*/
double calculateMedian(std::vector<double>& data);

/*
name: calculateVariance
brief: Calculates the variance of the data
param: vector data
return: double - the variance of the data
*/
double calculateVariance(const std::vector<double>& data);

/*
name: calculateStdDev
brief: Calculates the standard deviation of the data
param: vector data
return: double - the standard deviation of the data
*/
double calculateStdDev(const std::vector<double>& data);

/*
name: calculateMode
brief: Finds the mode(s) and their frequency in a sorted dataset
param: vector data
param: modes - a vector of doubles to store the mode(s)
return: size_t - the frequency of the mode(s)
*/
int calculateMode(const std::vector<double>& v, std::vector<double>& modes);

/*
name: calculateMeanAbsDeviation
brief: Calculates the mean absolute deviation of the data about a given measure
param: vector data
param: double measure - the measure (mean/median/mode) about which the deviation is calculated
return: double - the mean absolute deviation of the data
*/
double calculateMeanAbsDeviation(const std::vector<double>& data, double measure);

/*
name: calculateRegression
brief: Calculates the slope and intercept of the regression line for the data
param: vector data
param: double slope
param: double intercept
return: void
*/
void calculateRegression(const std::vector<double>& data, double& slope, double& intercept);

/*
name:  findOutliers
brief: Identifies outliers in the data based on standard deviations from the mean
param: vector data
param: vector outliers1x
param: vector outliers2x
param: vector outliers3x
return: void
*/
void findOutliers(const std::vector<double>& data, std::vector<double>& outliers1x, std::vector<double>& outliers2x, std::vector<double>& outliers3x);
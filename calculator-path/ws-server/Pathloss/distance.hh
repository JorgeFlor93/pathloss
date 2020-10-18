#pragma once
#include "coordinate.hpp"
#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include "Eigen/Core"
#include "Eigen/Dense"
#include <memory>
#include "common.h"
#include "Pathloss.hpp"

std::vector<Eigen::Matrix<double, 1, 2>> get_line(double line_start_lat , double line_start_lng, double line_end_lat, double line_end_lng);

std::vector<double> get_arealoss(double top_lat , double top_lng, double bot_lat, double bot_lng, 
                                struct site tx, float frequency, 
                                std::string pm, 
                                std::string pmenv);

int get_dimension_lng(double line_start_lng, double line_end_lng);

int get_dimension_lat(double line_start_lat, double line_end_lat);

void set_res(std::string resolution);


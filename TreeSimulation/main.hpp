//
//  main.hpp
//  TreeSimulation
//
//  Created by Steven Liao on 4/2/16.
//  Copyright © 2016 Steven Liao. All rights reserved.
//

#ifndef main_h
#define main_h

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glut.h>
#endif

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <unistd.h>
#include "Point.hpp"
#include "lodepng.h"

using namespace std;

// Stores the x,y coordinates of the branching structure
vector<vector<vector<int>>> attractorGraphs;

// Holds the RGBA values of each input image
vector<vector<vector<vector<unsigned char>>>> images;
vector<vector<unsigned>> imagesDimensions;
vector<vector<vector<vector<unsigned char>>>> imagesDensityValues;
vector<vector<vector<int>>> imagesDensityCoordinates;

float _angle = 0.0f;
int winWidth = 600, winHeight = 600;

void display();

// Fill a voxel grid with density values
void fillVoxel();
bool isRed(unsigned char r, unsigned char g, unsigned char b);
void loadImagesFromPath(char** imageFilePaths, int numImages);
void initAttractorGraphs();
void initDensityCoordinates();
void displayAttractorGraphs();
void displayDensityCoordinates();
void computeDensityValues();

void update(int value);






#endif /* main_h */

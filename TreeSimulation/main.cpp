

#include "main.hpp"

void keypress(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27: //Escape key
            exit(0);
        case 'x':
            update(0);
    }
}

void initRendering()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
}

void update(int value)
{
    _angle += 2.0f;
    if (_angle > 360)
        _angle -= 360;
    
    glutPostRedisplay();
//    glutTimerFunc(25, update, 0);
}

void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-1.0f, 2.75f, -7.0f);
    
    GLfloat ambientColor[] = {0.4f, 0.4f, 0.4f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
    GLfloat lightColor0[] = {0.6f, 0.6f, 0.6f, 1.0f};
    GLfloat lightPos0[] = {-0.5f, 0.8f, 0.1f, 0.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
    
    glTranslatef(1.5f, 0.0f, 0.0f);
    glRotatef(0.0f, 0.0f, 0.0f, 0.0f);
    glRotatef(-_angle, 0.0f, 1.0f, 0.0f);
    glTranslatef(-1.5f, 0.0f, 0.0f);
    
    
    float scale = 5.0f / max(imagesDimensions[0][0] - 1, imagesDimensions[0][1] - 1);
    glScalef(scale, scale, scale);
    glTranslatef(0.0f, 0.0f, 0.0f);
    
    
    
    displayDensityCoordinates();
    
    displayAttractorGraphs();
    
//    vector<vector<vector<unsigned char>>> currentImageDensityValues;
//    vector<vector<unsigned char>> rowDensityValues;
//    glBegin(GL_POINTS);
//    float r, g, b;
//    for (int i = 0; i < imagesDensityValues.size(); i++)
//    {
//        currentImageDensityValues = imagesDensityValues[i];
//        for (int j = 0; j < currentImageDensityValues.size(); j++)
//        {
//            rowDensityValues = currentImageDensityValues[i];
//            for (int k = 0; k < rowDensityValues.size(); k++)
//            {
//                r = (float) rowDensityValues[k][0] / 255;
////                g = (float) rowDensityValues[k][1] / 255;
////                b = (float) rowDensityValues[k][2] / 255;
////                if (r > 0)
//                    glColor3f((float) r, (float) r, (float) r);
//                glVertex2f(k, j);
//            }
//        }
//    }
//    glEnd();
    
//    glBegin(GL_POINTS);
//    for (int i = 0; i < winWidth; i++)
//    {
//        for (int j = 0; j < winHeight; j++)
//        {
//            glColor3f(0.0, 1.0, 1.0);
//            glVertex2f(i, j);
//        }
//    }
//    glEnd();
    

    glutSwapBuffers();
}

void displayAttractorGraphs()
{
    glColor3f(1.0, 0.0, 0.0);

    vector<vector<int>> currentAttractorGraph;
    glBegin(GL_POINTS);
    for (int i = 0; i < attractorGraphs.size(); i++)
    {
        currentAttractorGraph = attractorGraphs[i];
        for (int z = 0; z < currentAttractorGraph.size(); z++)
        {
            glVertex2f(currentAttractorGraph[z][0], -currentAttractorGraph[z][1]);
        }
    }
    glEnd();
}

void displayDensityCoordinates()
{
    vector<vector<int>> currentDensityCoordinates;
    float density;
    glBegin(GL_POINTS);
    for (int i = 0; i < imagesDensityCoordinates.size(); i++)
    {
        currentDensityCoordinates = imagesDensityCoordinates[i];
        for (int z = 0; z < currentDensityCoordinates.size(); z++)
        {
            // Display the density as a gray-to-white color
            density = ((float) currentDensityCoordinates[z][2]) / 100;
            glColor3f(density, density, density);
            glVertex2f(currentDensityCoordinates[z][0], -currentDensityCoordinates[z][1]);
        }
    }
    glEnd();
}

bool isRed(unsigned char r, unsigned char g, unsigned char b)
{
    if (r >= 220 && r <= 255 &&
        g >= 28  && g <= 60  &&
        b >= 0   && b <= 54)
        return true;
    return false;
}

bool isWhite(unsigned char r, unsigned char g, unsigned char b)
{
    if (r == 255 && b == 255 && g == 255)
        return true;
    return false;
}

bool isGray(unsigned char r, unsigned char g, unsigned char b)
{
    if (r >= 156 && b >= 156 && g >= 156)
        return true;
    return false;
}

void initAttractorGraphs()
{
    vector<vector<unsigned char>> row;
    vector<int> coordinates;
    vector<vector<int>> currentAttractorGraph;
    vector<vector<vector<unsigned char>>> image;
    
    for (int i = 0; i < images.size(); i++)
    {
        image = images[i];
        for (int j = 0; j < image.size(); j++)
        {
            row = image[j];
            for (int k = 0; k < row.size(); k+=4)
            {
                if (isRed(row[k][0], row[k][1], row[k][2]))
                {
                    coordinates = {k, j};
                    currentAttractorGraph.push_back(coordinates);
                }
            }
        }
        attractorGraphs.push_back(currentAttractorGraph);
    }
}

void initDensityCoordinates()
{
    
    vector<vector<unsigned char>> row;
    vector<int> coordinates;
    vector<vector<int>> currentDensityCoordinates;
    vector<vector<vector<unsigned char>>> image;
    int density;
    
    for (int i = 0; i < images.size(); i++)
    {
        image = images[i];
        for (int j = 0; j < image.size(); j++)
        {
            row = image[j];
            for (int k = 0; k < row.size(); k+=4)
            {
                if (!isWhite(row[k][0], row[k][1], row[k][2]) &&
                    !isGray(row[k][0], row[k][1], row[k][2])
                /*&& !isRed(row[k][0], row[k][1], row[k][2])*/)
                {
//                    density = rand() % 100;
                    if (row[k][3] != 255)
                        cout << "a: " << (int) row[k][3] << endl;
                    density = row[k][3] * 0.4;
                    coordinates = {k, j, density};
                    currentDensityCoordinates.push_back(coordinates);
                }
            }
        }
        imagesDensityCoordinates.push_back(currentDensityCoordinates);
    }
//    vector<vector<vector<unsigned char>>> image;
//    vector<vector<vector<unsigned char>>> currentImageDensityValues;
//    vector<vector<unsigned char>> rowDensityValues;
//    vector<unsigned char> densityValue;
//    vector<vector<unsigned char>> row;
//    unsigned char a;
//
//    for (int i = 0; i < images.size(); i++)
//    {
//        image = images[i];
//        for (int j = 0; j < image.size(); j++)
//        {
//            row = image[j];
//            for (int k = 0; k < row.size(); k++)
//            {
//                if (row[k][0] == 255 && row[k][1] == 255 && row[k][2] == 255)
//                    a = 0;
//                else
//                {
//                    a = rand() % (255 - 1 + 1) + 1;;
////                    cout << "a: " << (int) a << endl;
//                }
//                densityValue = {a};
//                rowDensityValues.push_back(densityValue);
//            }
//            currentImageDensityValues.push_back(rowDensityValues);
//            rowDensityValues.clear();
//        }
//        imagesDensityValues.push_back(currentImageDensityValues);
//    }
}

void loadImagesFromPath(char** imageFilePaths, int numImages)
{
    vector<unsigned char> image;
    unsigned width, height;
    for (int i = 0; i < numImages; i++)
    {
        unsigned error = lodepng::decode(image, width, height, imageFilePaths[i]);
        
        // If there's an error, display it.
        if(error != 0)
        {
            std::cout << "error " << error << ": " << lodepng_error_text(error) << std::endl;
            exit(1);
        }
        
        vector<unsigned> imageDimension = {width, height};
        imagesDimensions.push_back(imageDimension);
    
    
        vector<vector<vector<unsigned char>>> image2D;
        vector<vector<vector<unsigned char>>> imageDensityValues;
        vector<vector<unsigned char>> tempRow;
        vector<vector<unsigned char>> tempRowDensityValue;
        vector<unsigned char> tempPixel;
        unsigned char r, g, b, a; int c = 0;
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width * 4; x+=4)
            {
                r = image[c]; g = image[c+1]; b = image[c+2]; a = image[c+3];
                
                tempPixel = {r, g, b, a};
                tempRow.push_back(tempPixel);
//                if (a != 255)
//                    cout << "a: " << (int) a << endl;
//                tempPixel = {a};
//                tempRowDensityValue.push_back(tempPixel);
    //            if (isRed(r, g, b))
    //            {
    //                cout << "r: " << (int) r << " g: " << (int) g << " b: " << (int) b << endl;
    //            }
                c+=4;
            }
            image2D.push_back(tempRow);
            
            tempRow.clear();
        }
        
        images.push_back(image2D);
    }
}

int main(int argc, char** argv)
{
    char** filePath = (char*[])
    {
        "/Users/stevenliao/Documents/School/Spring 2016/CSE 328/CSE328_Project/TreeSimulation/TreeSimulation/tree4red.png",
    };
    
    char* file;
    
    
    
    // This will load each image into the 4D vector: images
    loadImagesFromPath(filePath, 1);
    
    // This will put the attractor graphs of each image into 3D vector: attractorGraphs
    initAttractorGraphs();
    
    // This will put the density values of each image into
    initDensityCoordinates();
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(winWidth, winHeight);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("Tree Modeling");
    initRendering();
    
    glutDisplayFunc(display);
    glutKeyboardFunc(keypress);
    glutReshapeFunc(resize);
    glutTimerFunc(25, update, 0);
    
    glutMainLoop();
    
    return 0;
}

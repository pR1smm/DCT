#define _USE_MATH_DEFINES
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;
std::vector<float> IDCT(std::vector<float> transformedVector)
{
    std::vector<float> outVector;
    for (int i = 0; i < 8; i++)
    {
        float result = 0;
        for (int m = 0; m < 8; m++)
        {
            float functionCoefficient = m == 0 ? (float)sqrt(2) / 2 / 2 : (float)1 / 2;
            result += functionCoefficient * cos(((2 * i + 1) * m * M_PI) / 16) * transformedVector.at(m);
        }
        
        outVector.push_back(result);
    }
    
    return outVector;
}

std::vector<float> DCT(std::vector<float> signalVector)
{
    std::vector<float> outVector;
    for (int i = 0; i < signalVector.size(); i++)
    {
        //std::cout << signalVector.at(i) << ", ";
    }
    //std::cout << std::endl;
    
    for (int n = 0; n < 8; n++)
    {
        float functionCoefficient = n == 0 ? (float)sqrt(2) / 2 / 2 :(float) 1 / 2;
        float result = 0;
        
        for (int m = 0; m < 8; m++)
        {
            result += cos(((2 * m + 1) * n * M_PI) / 16) * signalVector.at(m);
            
        }
        // std::cout << "Result for F(" << n << ") ist " << result << std::endl;
        result *= functionCoefficient;
        outVector.push_back(result);
        // std::cout << result << std::endl;
    }
    
    return outVector;
}



std::vector<std::vector<float>> DCT2(std::vector<std::vector<float>> InputMatrix)
{
    std::vector<std::vector<float>> outMatrix(8, std::vector<float>(8));
    float result;
    for(int u = 0; u < 8; u++)
    {
        for(int v = 0; v < 8; v++)
        {
            float functionCoefficientU = u == 0 ? (float)(1 / sqrt(2)):(float) 1;
            float functionCoefficientV = v == 0 ? (float)(1 / sqrt(2)):(float) 1;
            result = 0.0f;

            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    result += cos((2 * i + 1) * u * M_PI / 16) * cos(((2 * j + 1) * v * M_PI) / 16) * InputMatrix.at(i).at(j);
                }
            }
            outMatrix.at(u).at(v) = (functionCoefficientU * functionCoefficientV) / 4 * result;
        }
    }
    return outMatrix;
}


int main()
{
    std::vector<std::vector<float>> matrixRAW(8, std::vector<float>(8));
    matrixRAW = {
        {241, 58, 154, 123, 226, 193, 115, 4},
        {208, 112, 156, 201, 234, 187, 44, 102},
        {238, 233, 104, 227, 14, 89, 206, 2},
        {34, 51, 50, 153, 68, 50, 3, 189},
        {112, 237, 118, 106, 215, 133, 51, 170},
        {213, 4, 173, 96, 211, 127, 180, 108},
        {77, 47, 48, 173, 76, 137, 37, 177},
        {95, 218, 217, 150, 126, 228, 209, 163},
    };
    std::vector<std::vector<float>> quantisierungsMatrix(8, std::vector<float>(8));
    quantisierungsMatrix = {
        {16, 11, 10, 16, 24, 40, 51, 61},
        {12, 12, 14, 19, 26, 58, 60, 55},
        {14, 13, 16, 24, 40, 57, 69, 56},
        {14, 17, 22, 29, 51, 87, 80, 62},
        {18, 22, 37, 56, 68, 109, 103, 77},
        {24, 35, 55, 64, 81, 104, 113, 92},
        {49, 64, 78, 87, 103, 121, 120, 101},
        {72, 92, 95, 98, 112, 100, 103, 99},
    };
    
    std::vector<std::vector<float>> tempMatrix(8, std::vector<float>(8));
    std::vector<std::vector<float>> tempColMatrix(8, std::vector<float>(8));
    std::vector<std::vector<float>> matrixQuantisiert(8, std::vector<float>(8));
    
    // Aufgabe 2: Substract
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            matrixRAW.at(i).at(j) -= 128.0f;
        }
    }
    // Aufgabe 2
    std::vector<std::vector<float>> dct2TransformedMatrix = DCT2(matrixRAW);

    // Aufgabe 2: Quantisieren
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            matrixQuantisiert.at(i).at(j) = round(dct2TransformedMatrix.at(i).at(j) / quantisierungsMatrix.at(i).at(j));
        }
    }
    // Aufgabe 2
    
    cout << "DCT2 Function Matrix" << endl;
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            //cout << dct2TransformedMatrix.at(i).at(j) << ", ";
            cout << matrixQuantisiert.at(i).at(j) << ", ";
        }
        cout << endl;
    }
    
    
    
    cout << "2*DCT Function Matrix" << endl;
    for(int i = 0; i < 8; i++)
    {
        tempMatrix.at(i) = DCT(matrixRAW.at(i));
    }
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            tempColMatrix.at(i).at(j) = tempMatrix.at(j).at(i);
        }
    }
    for(int i = 0; i < 8; i++)
    {
        tempMatrix.at(i) = DCT(tempColMatrix.at(i));
    }
    
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cout << tempMatrix.at(j).at(i) << ", ";
        }
        cout << endl;
    }
    return 0;
}
